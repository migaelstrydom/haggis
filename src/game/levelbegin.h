/************************************************************************
 *
 * levelbegin.h
 * Level begin window class
 *
  ************************************************************************/

#ifndef LEVELBEGIN_H
#define LEVELBEGIN_H

#include "window.h"
#include "button.h"
#include "staticimage.h"

/**
 * The level begin window is displayed before the maze begins.
 */
class LevelBegin : public Window
{
public:
    /**
     * Constructor.
     */
    LevelBegin();

    /**
     * Destructor.
     */
    virtual ~LevelBegin();

    /**
     * Set the window size.
     */
    virtual void setSize(vector4 size);

    /**
     * Returns true if the user has requested the maze to start.
     */
    bool shouldStart();

    /**
     * Returns true if the user has requested the game to exit.
     */
    bool shouldExit();

private:
    /**
     * The image to display.
     */
    StaticImage *img;

    /**
     * The start level button.
     */
    Button *btnstart;

    /**
     * The exit game button.
     */
    Button *btnexit;
};

#endif //LEVELBEGIN_H

