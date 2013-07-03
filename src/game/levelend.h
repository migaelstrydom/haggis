/************************************************************************
 *
 * levelend.h
 * LevelEnd class
 *
 ************************************************************************/

#ifndef LEVELEND_H
#define LEVELEND_H

#include "window.h"
#include "button.h"
#include "staticimage.h"

/**
 * The level end window is displayed after the maze ends.
 */
class LevelEnd : public Window
{
public:
    /**
     * Constructor.
     */
    LevelEnd();

    /**
     * Destructor.
     */
    virtual ~LevelEnd();

    /**
     * Set the window size.
     */
    virtual void setSize(vector4 size);

    /**
     * Sets the winner of the level. If won is true, the hero won. If won
     * is false, the haggis won.
     */
    void setWinner(bool won);

    /**
     * Returns true if the user has requested to retry the level.
     */
    bool shouldRetry();

    /**
     * Returns true if the user has requested to continue to the next level.
     */
    bool shouldContinue();

    /**
     * Returns true if the user has requested to exit the game.
     */
    bool shouldExit();

protected:
    /**
     * Draw the screen.
     */
    virtual void draw(float dt);

private:
    /**
     * True if the player won the level or false if the haggis won.
     */
    bool won;

    /**
     * The ending images.
     */
    StaticImage *imgwon, *imglost;

    /**
     * The retry and continue buttons.
     */
    Button *btnretry, *btncont;

    /**
     * The exit button.
     */
    Button *exit;
};

#endif //LEVELEND_H

