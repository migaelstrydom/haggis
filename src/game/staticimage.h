/************************************************************************
 *
 * staticimage.h
 * StaticImage class
 *
  ************************************************************************/

#ifndef STATICIMAGE_H
#define STATICIMAGE_H

#include "widget.h"
#include "texture.h"

/**
 * A StaticImage is a widget that displays a texture.
 */
class StaticImage : public Widget
{
public:
    /**
     * Constructor. The StaticImage takes ownership of the texture. If the
     * texture is NULL, no texture will be drawn.
     */
    StaticImage(Texture *tex);

    /**
     * Destructor.
     */
    virtual ~StaticImage();

    /**
     * Returns the texture that is displayed. This may be NULL.
     */
    Texture *getTexture();

protected:
    /**
     * Draw the texture.
     */
    virtual void draw(float dt);

private:
    /**
     * The texture to draw. This may be NULL.
     */
    Texture *tex;
};

#endif //STATICIMAGE_H
