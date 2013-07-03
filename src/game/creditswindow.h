/************************************************************************
 *
 * creditswindow.h
 * Credits window class
 *
 ************************************************************************/

#ifndef CREDITSWINDOW_H
#define CREDITSWINDOW_H

#include "window.h"
#include "button.h"
#include "staticimage.h"

/**
 * The CreditsWindow class displays the credits at the end of the game.
 */
class CreditsWindow : public Window
{
public:
    /**
     * Constructor.
     */
    CreditsWindow();

    /**
     * Destructor.
     */
    virtual ~CreditsWindow();

    /**
     * Sets the size of the window.
     */
    virtual void setSize(vector4 size);

    /**
     * Returns true if the user has clicked the exit button.
     */
    bool shouldExit();

private:
    /**
     * The intro image.
     */
    StaticImage *img;

    /**
     * The exit button.
     */
    Button *exit;
};

#endif //CREDITSWINDOW_H

