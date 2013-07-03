/************************************************************************
 *
 * haggis.h
 * Haggis class. Controls the haggis.
 *
 ************************************************************************/

#ifndef HAGGIS_H
#define HAGGIS_H

#include "player.h"
#include "maze.h"
#include "hero.h"
#include <vector>

/**
 * The Haggis represents the computer player
 */
class Haggis : public Player {
public:

    /**
     * Constructor.
     */
    Haggis(Maze*, Hero*);

    /**
     * Destructor.
     */
    virtual ~Haggis();

    /**
     * Render the haggis.
     */
    virtual void render(float dt);

    /**
     * Let's the haggis know that it has a turn now.
     */
    void setTurn();

private:

    /**
     * The current time. Used for animation.
     */
    double t;

    /**
     * True if it is the haggis' turn.
     */
    bool bTurn;

    /**
     * The haggis needs to have know what is going on in the maze
     * to decide what to do next.
     */
    Maze *maze;

    /**
     * This is the path the haggis decides to follow.
     */
    std::vector<Cell*> pathToFollow;

    /**
     * This decides what the haggis will do, and does it. It finds a
     * random spot in the maze for the haggis to move to and moves it
     * there one step at a time, and it makes the haggis throw grenades
     * when the hero is in range. Basically, it is the haggis' AI.
     */
    void takeTurn();

    /**
     * This method searches through the maze and finds the haggis a
     * new random location to go to, and a path to follow.
     */
    void findPath();

    /**
     * The haggis needs to know where the hero is so that it can throw grenades.
     */
    Hero *hero;
};

#endif //HAGGIS_H
