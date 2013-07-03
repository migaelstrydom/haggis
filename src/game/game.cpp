/************************************************************************
 *
 * game.cpp
 * Application class implementation
 *
 ************************************************************************/

#include "game.h"
#include "level.h"

#include <iostream>

/**
 * Constructor. The command line arguments are parsed for options.
 */
Game::Game(int argc, char *argv[])
    : Application()
{
    state = -1;
    intro = NULL;
    level = NULL;
    credits = NULL;
}

/**
 * Destructor.
 */
Game::~Game()
{
    //if something was used, delete it
    if (intro) {
        delete intro;
    }
    if (level) {
        delete level;
    }
    if (credits) {
        delete credits;
    }
}

/**
 * Perform a single iteration of the main loop.
 */
void Game::step(float t, float dt) throw(app_error)
{
    //if the game is just starting
    if (state == -1) {
        state = 0;
	//introduction
        intro = new IntroWindow();
        Application::setRootWindow(intro);

    } else if (state == 0) {
	//level start
        if (intro->shouldStart()) {
            level = new Level();
            level->load("");
            Application::setRootWindow(level);

            delete intro;
            intro = NULL;
            state = 1;
        } else if (intro->shouldExit()) { //did the user choose exit?
            quit();
        }

    } else if (state == 1) {  //main game

        if (level->shouldExit()) {
            quit();
        } else if (level->shouldRetry()) { //retry if died
            delete level;
            level = new Level();
            level->load("");
            Application::setRootWindow(level);
        } else if (level->shouldContinue()) { //continue to credits if won
            credits = new CreditsWindow();
            Application::setRootWindow(credits);

            delete level;
            level = NULL;
            state = 2;
        }

    } else if (state == 2) {   //at credits, now exit
        if (credits->shouldExit()) {
            quit();
        }
    }
    //continue with the loop
    Application::step(t, dt);
}
