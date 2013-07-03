/************************************************************************
 *
 * staticimage.cpp
 * StaticImage class implementation
 *
 ************************************************************************/

#include "staticimage.h"

#include <GL/gl.h>

/**
 * Constructor. The StaticImage takes ownership of the texture. If the
 * texture is NULL, no texture will be drawn.
 */
StaticImage::StaticImage(Texture *tex)
    : tex(tex)
{
}

/**
 * Destructor.
 */
StaticImage::~StaticImage()
{
    if (tex) {  //delete it if it has been used
        delete tex;
    }
}

/**
 * Returns the texture that is displayed. This may be NULL.
 */
Texture *StaticImage::getTexture()
{
    return tex;
}

/**
 * Draw the texture. This is done by creating an OpenGL rectangle on which it is displayed.
 */
void StaticImage::draw(float dt)
{
    //enable texturing
    glEnable(GL_TEXTURE_2D);
    if (tex) {   //if the texture has been initialised
        tex->bind();
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    //enable blending to get rid of edges
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(1, 1, 1);

    //draw the rectangle
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(0, 0);
    glTexCoord2f(1, 1); glVertex2f(getSize().x, 0);
    glTexCoord2f(1, 0); glVertex2f(getSize().x, getSize().y);
    glTexCoord2f(0, 0); glVertex2f(0, getSize().y);
    glEnd();

    glDisable(GL_BLEND);  //reset
}
