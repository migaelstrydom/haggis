/************************************************************************
 *
 * button.cpp
 * Button class implementation
 *
 ************************************************************************/

#include "button.h"

#include <GL/gl.h>

#include <iostream>

/**
 * Constructor. The button takes ownership of the texture. If the texture
 * is NULL, no texture will be drawn on the button.
 */
Button::Button(Texture *tex)
    : tex(tex), pressed(false), toggle(false), enabled(true)
{
}

/**
 * Destructor.
 */
Button::~Button()
{
    //if tex has been used
    if (tex) {
        delete tex;
    }
}

/**
 * Return whether the button is pressed.
 */
bool Button::isPressed()
{
    return pressed;
}

/**
 * Resets the button.
 */
void Button::reset()
{
    pressed = false;
}

/**
 * Returns the texture. This may be NULL.
 */
Texture *Button::getTexture()
{
    return tex;
}

/**
 * Set the toggle state of the button. If tog is true, the button
 * will be rendered as if it is pushed in.
 */
void Button::setToggle(bool tog)
{
    toggle = tog;
}

/**
 * Returns the toggle state of the button.
 */
bool Button::getToggle()
{
    return toggle;
}

/**
 * Set the enabled state of the button. If enable is false, the button
 * is disabled and cannot be pressed. The button is reset if the new
 * enabled state is different from the last.
 */
void Button::setEnabled(bool enable)
{
    if (enable != getEnabled()) {
        reset();
    }
    enabled = enable;
}

/**
 * Returns the enabled state of the button.
 */
bool Button::getEnabled()
{
    return enabled;
}

/**
 * Draw the button.
 */
void Button::draw(float dt)
{
    //only draw it if it is enabled
    if (!getEnabled()) {
        glColor3f(0, 0, 0);
    } else if (getToggle() || isInside(getMousePosition())) {
        glColor3f(0.5, 0.5, 0.5);
    } else {
        glColor3f(1, 1, 1);
    }

    //enable texturing
    glEnable(GL_TEXTURE_2D);
    if (tex) {
        tex->bind();
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    //enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //draw the vertices
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(0, 0);
    glTexCoord2f(1, 1); glVertex2f(getSize().x, 0);
    glTexCoord2f(1, 0); glVertex2f(getSize().x, getSize().y);
    glTexCoord2f(0, 0); glVertex2f(0, getSize().y);
    glEnd();

    glDisable(GL_BLEND);
}

/**
 * Handles a mouse button click.
 */
bool Button::onHandleButtonEvent(ButtonEvent event)
{
    //check that the button is enabled
    if (getEnabled()) {
        if ((event.getButton() == ButtonEvent::LEFT) &&
            (event.getState() == ButtonEvent::RELEASED)) {
            pressed = true;
            return true;
        }
    }
    return false;
}
