/************************************************************************
 *
 * level.h
 * Level class
 *
 ************************************************************************/

#ifndef LEVEL_H
#define LEVEL_H

#include "window.h"
#include "maze.h"
#include "hero.h"
#include "haggis.h"
#include "action.h"
#include "levelbegin.h"
#include "overlay.h"
#include "levelend.h"

#include <string>

/**
 * The Level class contains the logic for a single level.
 */
class Level : public Window {
public:
    /**
     * The current turn type.
     */
    enum turn {HERO_TURN, HAGGIS_TURN, ACTION_TURN};

    /**
     * Constructor. Initially, no level is loaded.
     */
    Level();

    /**
     * Destructor.
     */
    virtual ~Level();

    /**
     * Load the level from the file. Currently this only loads the default
     * level "level1.hag" regardless of the value of path. This method
     * requires that the level is not already loaded.
     */
    void load(std::string path);

    /**
     * Returns true if the level has been loaded.
     */
    bool isLoaded();

    /**
     * Notify the level that the user has initated an action. This is called
     * by Overlay. This method requires that the level has been loaded. The
     * action will be used if it is the hero's turn and no other actions are
     * running. This method requires that the level is loaded.
     */
    virtual void notifyHeroAction(Action *a);

    /**
     * Notify the level that the haggis has initiated an action. This is
     * called by Haggis. It requires that the level is loaded.
     */
    virtual void notifyHaggisAction(Action *a);

    /**
     * Notify the level that a general action is happening. This is an
     * action that was not initiated by the haggis or the hero, but by,
     * for example, an item. The difference is that after a general action,
     * cturn does not change. This method requires that the level is loaded.
     */
    virtual void notifyGeneralAction(Action *a);

    /**
     * Return the hero. This method requires that the level has been loaded.
     */
    virtual Hero *getHero();

    /**
     * Return the haggis. This method requires that the level has been loaded.
     */
    Haggis *getHaggis();

    /**
     * Return the current turn.
     */
    turn getCurrentTurn();

    /**
     * Sets the size of the window.
     */
    virtual void setSize(vector4 size);

    /**
     * Returns true if the user has requested the game to exit.
     */
    bool shouldExit();

    /**
     * Returns true if the user has requested the game to continue to the
     * next level. True can only be returned if the player has won the level
     * and the level ending screen is being displayed.
     */
    bool shouldContinue();

    /**
     * Returns true if the user has requested the game to retry this level.
     * True can only be returned if the player has lost the level and the
     * level ending screen is being displayed.
     */
    bool shouldRetry();

protected:
    /**
     * Processes events from the level begin, overlay and level end screens
     * and updates actions. It also checks whether the level has been won
     * and takes the appropriate actions.
     */
    virtual void draw(float dt);

    /**
     * The maze for the level.
     */
    Maze *maze;

    /**
     * The hero.
     */
    Hero *hero;

    /**
     * The haggis.
     */
    Haggis *haggis;

    /**
     * Returns the player action.
     */
    Action *getPlayerAction();

    /**
     * Sets the current turn.
     */
    void setCurrentTurn(turn);

private:
    /**
     * The current action.
     */
    Action *action;

    /**
     * The current player action. There can only be one of these at a time,
     * and they have lower priority than general actions.
     */
    Action *playerAction;

    /**
     * The level begin window for this level.
     */
    LevelBegin *lbegin;

    /**
     * The user interface overlay.
     */
    Overlay *overlay;

    /**
     * The level end window for this level.
     */
    LevelEnd *lend;

    /**
     * A flag which is true if the level has been loaded.
     */
    bool loaded;

    /**
     * The current turn.
     */
    turn cturn;

    /**
     * The current level state.
     *  -1 = not loaded
     *   0 = displaying level begin screen
     *   1 = displaying maze and overlay
     *   2 = displaying level end screen
     */
    int state;

    /**
     * Display the level start screen and set the state to 0.
     */
    void startLevelBegin();

    /**
     * Display maze and overlay and set the state to 1.
     */
    void startMaze();

    /**
     * Display the level end screen and set the state to 2.
     */
    void startLevelEnd();
};

#endif //LEVEL_H

