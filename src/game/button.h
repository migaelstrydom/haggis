/************************************************************************
 *
 * button.h
 * Button class
 *
 ************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include "texture.h"

/**
 * A Button is a widget that the user can click.
 */
class Button : public Widget
{
public:
    /**
     * Constructor. The button takes ownership of the texture. If the texture
     * is NULL, no texture will be drawn on the button.
     */
    Button(Texture *tex);

    /**
     * Destructor.
     */
    virtual ~Button();

    /**
     * Returns true if the button is pressed.
     */
    bool isPressed();

    /**
     * Reset the button inot its unpressed state.
     */
    void reset();

    /**
     * Returns the button's texture. This may be NULL.
     */
    Texture *getTexture();

    /**
     * Set the toggle state of the button. If tog is true, the button
     * will be rendered as if it is pushed in.
     */
    void setToggle(bool tog);

    /**
     * Returns the toggle state of the button.
     */
    bool getToggle();

    /**
     * Set the enabled state of the button. If enable is false, the button
     * is disabled and cannot be pressed. The button is reset if the new
     * enabled state is different from the last.
     */
    void setEnabled(bool enable);

    /**
     * Returns the enabled state of the button.
     */
    bool getEnabled();

protected:
    /**
     * Draw the button.
     */
    virtual void draw(float dt);

    /**
     * Handles a mouse button click.
     */
    virtual bool onHandleButtonEvent(ButtonEvent event);

private:
    /**
     * The texture drawn on the button. This may be NULL.
     */
    Texture *tex;

    /**
     * The pressed state of the button.
     */
    bool pressed;

    /**
     * The toggle state of the button.
     */
    bool toggle;

    /**
     * The enabled state of the button.
     */
    bool enabled;
};

#endif //BUTTON_H
