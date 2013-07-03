/************************************************************************
 *
 * texture.h
 * Texture class
 *
 ************************************************************************/

#ifndef TEXTURE_H
#define TEXTURE_H

#include "application.h"

#include "SDL/SDL.h"
#include <GL/gl.h>

#include <string>

/**
 * The Texture holds a texture bitmap for loading into OpenGL.
 */
class Texture {
public:
    /**
     * Destructor.
     */
    virtual ~Texture();

    /**
     * Load a texture from the file. An app_error is thrown if the texture
     * cannot be loaded.
     */
    static Texture* load(std::string path) throw(app_error);

    /**
     * Tell OpenGL this is the texture to be used next.
     */
    void bind();

    /**
     * Returns the aspect ratio of the texture. This is the width divided by
     * the height.
     */
    float getAspectRatio();

    /**
     * Load the texture into OpenGL.
     */
    void initialise();

private:
    /**
     * The texture surface.
     */
    SDL_Surface *surf;

    /**
     * Constructor. The texture will be in charge of the surface from now on.
     */
    Texture(SDL_Surface *s);

    /**
     * The OpenGL texture name.
     */
    GLuint id;
};

#endif //TEXTURE_H
