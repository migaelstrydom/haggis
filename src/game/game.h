/************************************************************************
 *
 * game.h
 * Application class
 *
 * 2006-08-30  Timothy Stranex  Created
 *
 ************************************************************************/

#ifndef GAME_H
#define GAME_H

#include "application.h"
#include "level.h"
#include "introwindow.h"
#include "creditswindow.h"

/**
 * The Game class handles all the high-level game logic like loading the
 * levels in the correct order.
 */
class Game : public Application
{
public:

    /**
     * Constructor. The command line arguments are parsed for options.
     */
    Game(int argc, char *argv[]);

    /**
     * Destructor.
     */
    virtual ~Game();

protected:
    /**
     * Perform a single iteration of the main loop.
     */
    virtual void step(float t, float dt) throw(app_error);

private:
    /**
     * The state of the game.
     *   -1 = not started
     *    0 = intro window
     *    1 = first level
     *    2 = credits window
     */
    int state;

    /**
     * The introduction window. This may be NULL if state != 0.
     */
    IntroWindow *intro;

    /**
     * The current level. This may be NULL if state != 1.
     */
    Level *level;

    /**
     * The credits window. This may be NULL if state != 2.
     */
    CreditsWindow *credits;
};

#endif //GAME_H

