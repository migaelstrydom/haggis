/************************************************************************
 *
 * texture.cpp
 * Texture class implementation
 *
 ************************************************************************/

#include "texture.h"
#include "application.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>

#include <iostream>

/**
 * Load a texture from the file. An app_error is thrown if the texture
 * cannot be loaded. If SDL is not initialised it returns NULL.
 */
Texture* Texture::load(std::string path) throw(app_error)
{
    //make sure that SDL was initialised
    if(!SDL_WasInit(0))
	return NULL;   //no texture can be loaded if SDL not initialised

    //load the image onto an SDL surface
    SDL_Surface *s = IMG_Load(path.c_str());

    //if there was an error, report it and exit
    if (!s) 
    {
        std::string s = "Error loading texture " + path + ": ";
        throw app_error(s + IMG_GetError());
    }

    return new Texture(s);
}

/**
 * Load the texture into OpenGL.
 */
void Texture::initialise()
{
    if (!surf)  //check that the surf has been initialised
    {
        return;
    }

    //enable texture mapping
    glEnable(GL_TEXTURE_2D);
    //create a new texture id
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    //set pixel packing
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //get format of data
    GLenum fmt;
    switch(surf->format->BytesPerPixel) {
    case 3:
        fmt = GL_RGB;
        break;
    case 4:
        fmt = GL_RGBA;
        break;
    default:
        assert(false);
    }

    //build mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, fmt, surf->w, surf->h, fmt,
                      GL_UNSIGNED_BYTE, surf->pixels);
}
/**
 * Returns the aspect ratio of the texture. This is the width divided by
 * the height.
 */
float Texture::getAspectRatio()
{
    return (float) surf->w / (float) surf->h;
}

/**
 * Constructor. The texture will be in charge of the surface from now on.
 */
Texture::Texture(SDL_Surface *s)
    : surf(s)
{
    initialise();
}

/**
 * Destructor.
 */
Texture::~Texture()
{
    if (surf)
    {
        SDL_FreeSurface(surf);
        glDeleteTextures(1, &id);
    }
}

/**
 * Tell OpenGL this is the texture to be used next.
 */
void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}
