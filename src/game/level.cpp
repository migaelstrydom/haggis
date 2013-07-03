/************************************************************************
 *
 * level.cpp
 * Level class implementation
 *
 ************************************************************************/

#include "level.h"
#include "maze.h"
#include "hero.h"
#include "haggis.h"
#include "walkaction.h"
#include "grenadeaction.h"

#include <string>
#include <iostream>
#include <assert.h>

/**
 * Constructor. Initially, no level is loaded.
 */
Level::Level()
    : action(NULL), playerAction(NULL), loaded(false), state(-1)
{
}

/**
 * Destructor.
 */
Level::~Level()
{
    // delete the actions first in case they need to the maze to
    // still exist
    if (playerAction) {
        delete playerAction;
    }
    if(action) {
        delete action;
    }

    if (loaded)
    {
        delete maze;
        delete lbegin;
        delete overlay;
        delete lend;
    }
}

/**
 * Processes events from the level begin, overlay and level end screens
 * and updates actions. It also checks whether the level has been won
 * and takes the appropriate actions.
 */
void Level::draw(float dt)
{
    if (state == 0) {

        // the level begin screen is being displayed so check if should
        // start yet

        if (lbegin->shouldStart()) {
            startMaze();
        }

    } else if (state == 1) {
        // the level has started

        // first update the actions
        // "action" takes priority to "playerAction"

        if (playerAction && !action) {
            if (!playerAction->update(dt)) {

                // the playerAction has finished

                delete playerAction;
                playerAction = NULL;

                // notify the haggis that it should make its move
                if(cturn == HAGGIS_TURN) {
                    haggis->setTurn();
                }
            }
        }

        if(action) {
            if(!action->update(dt)) {

                // the action has finished

                delete action;
                action = NULL;
            }
        }

        // check whether there is a winner yet
        if (hero->isDead() || haggis->isDead()) {
            startLevelEnd();
        }
    }
}

/**
 * Notify the level that the user has initated an action. This is called
 * by Overlay. This method requires that the level has been loaded. The
 * action will be used if it is the hero's turn and no other actions are
 * running. This method requires that the level is loaded.
 */
void Level::notifyHeroAction(Action *a)
{
    assert(isLoaded());

    // only accept the action if it is the hero's turn and we are not
    // currently executing another action

    if ((getCurrentTurn() == HERO_TURN) && (!playerAction)) {
        playerAction = a;
        cturn = HAGGIS_TURN;
    }
}

/**
 * Notify the level that the haggis has initiated an action. This is
 * called by Haggis. It requires that the level is loaded.
 */
void Level::notifyHaggisAction(Action *a)
{
    assert(isLoaded());

    // only accept the action if it is the haggis's turn and we are not
    // currently executing another action

    if((getCurrentTurn() == HAGGIS_TURN) && (!playerAction)) {
        playerAction = a;
        cturn = HERO_TURN;
    }
}

/**
 * Notify the level that a general action is happening. This is an
 * action that was not initiated by the haggis or the hero, but by,
 * for example, an item. The difference is that after a general action,
 * cturn does not change. This method requires that the level is loaded.
 */
void Level::notifyGeneralAction(Action *a)
{
    assert(isLoaded());

    // only accept the action if we are not already processing another

    if(!action) {
        action = a;
    }
}

/**
 * Load the level from the file. Currently this only loads the default
 * level "level1.hag" regardless of the value of path. This method
 * requires that the level is not already loaded.
 */
void Level::load(std::string path)
{
    assert(!isLoaded());

    // create the user interface

    lbegin = new LevelBegin();
    lend = new LevelEnd();

    maze = new Maze();
    maze->setLevel(this);
    maze->load("level1.hag");

    overlay = new Overlay();
    overlay->setLevel(this);
    overlay->setMaze(maze);
    overlay->setRenderPasses(RENDER_PASS_2);

    addChild(overlay);
    addChild(maze);
    addChild(lbegin);
    addChild(lend);

    // resize ourself to recalculate the positions and sizes of the user
    // interface

    setSize(getSize());

    // create the hero and put it on its starting cell

    hero = new Hero();

    Cell *c = maze->getHeroCell();
    assert(c != NULL);
    hero->setCell(c);
    hero->setPosition(vector4(0, 1, 0));

    // create the haggis and put it on its starting cell

    haggis = new Haggis(maze, hero);
    c = maze->getHaggisCell();
    assert(c != NULL);
    haggis->setCell(c);
    haggis->setPosition(vector4(0,1,0));

    // the hero gets to take the first move

    cturn = HERO_TURN;
    loaded = true;

    // setup level begin state

    startLevelBegin();
}

/**
 * Returns true if the level has been loaded.
 */
bool Level::isLoaded()
{
    return loaded;
}

/**
 * Return the hero. This method requires that the level has been loaded.
 */
Hero *Level::getHero()
{
    return hero;
}

/**
 * Return the haggis. This method requires that the level has been loaded.
 */
Haggis *Level::getHaggis()
{
    return haggis;
}

/**
 * Return the current turn.
 */
Level::turn Level::getCurrentTurn()
{
    if (playerAction) {
        return ACTION_TURN;
    } else {
        return cturn;
    }
}

/**
 * Sets the size of the window.
 */
void Level::setSize(vector4 size)
{
    Window::setSize(size);

    // resize all the child windows to fit exactly into this window

    if (isLoaded()) {
        lbegin->setSize(getSize());
        maze->setSize(getSize());
        overlay->setSize(getSize());
        lend->setSize(getSize());
    }
}

/**
 * Returns true if the user has requested the game to exit.
 */
bool Level::shouldExit()
{
    // we need to check the exit flags of the screen currently being
    // displayed

    if (state == 0) {
        return lbegin->shouldExit();
    } else if (state == 1) {
        return overlay->shouldExit();
    } else if (state == 2) {
        return lend->shouldExit();
    } else {
        return false;
    }
}

/**
 * Returns true if the user has requested the game to continue to the
 * next level. True can only be returned if the player has won the level
 * and the level ending screen is being displayed.
 */
bool Level::shouldContinue()
{
    if (state == 2) {
        return lend->shouldContinue();
    } else {
        return false;
    }
}

/**
 * Returns true if the user has requested the game to retry this level.
 * True can only be returned if the player has lost the level and the
 * level ending screen is being displayed.
 */
bool Level::shouldRetry()
{
    if (state == 2) {
        return lend->shouldRetry();
    } else {
        return false;
    }
}

/**
 * Display the level start screen and set the state to 0.
 */
void Level::startLevelBegin()
{
    lbegin->setEnabled(true);
    maze->setEnabled(false);
    overlay->setEnabled(false);
    lend->setEnabled(false);
    state = 0;
}

/**
 * Display maze and overlay and set the state to 1.
 */
void Level::startMaze()
{
    lbegin->setEnabled(false);
    maze->setEnabled(true);
    overlay->setEnabled(true);
    lend->setEnabled(false);
    state = 1;
}

/**
 * Display the level end screen and set the state to 2.
 */
void Level::startLevelEnd()
{
    lbegin->setEnabled(false);
    maze->setEnabled(false);
    overlay->setEnabled(false);
    lend->setEnabled(true);

    lend->setWinner(haggis->isDead());

    state = 2;
}

/**
 * Returns the player action.
 */
Action* Level::getPlayerAction()
{
    return playerAction;
}

/**
 * Sets the current turn.
 */
void Level::setCurrentTurn(turn t)
{
    cturn = t;
}
