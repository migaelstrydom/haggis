/************************************************************************
 *
 * introwindow.h
 * Introduction window class
 *
 ************************************************************************/

#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include "window.h"
#include "staticimage.h"
#include "button.h"

/**
 * The IntroWindow displays an introduction animation at the start of the
 * game.
 */
class IntroWindow : public Window
{
public:
    /**
     * Constructor.
     */
    IntroWindow();

    /**
     * Destructor.
     */
    virtual ~IntroWindow();

    /**
     * Sets the size of the window.
     */
    virtual void setSize(vector4 size);

    /**
     * Returns true if the user has clicked the start button.
     */
    bool shouldStart();

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
     * The start button.
     */
    Button *start;

    /**
     * The exit button.
     */
    Button *exit;
};

#endif //INTROWINDOW_H
