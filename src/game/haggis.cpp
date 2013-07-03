/************************************************************************
 *
 * haggis.cpp
 * Haggis class implementation
 *
 ************************************************************************/

#include "haggis.h"
#include "walkaction.h"
#include "waitaction.h"
#include "jumpaction.h"
#include "grenadeaction.h"
#include "level.h"

#include <GL/gl.h>

#include <cmath>

#include <queue>

#include <iostream>

#define GRENADE_RADIUS_SQ 25.0

/**
 * Constructor. Takes maze and hero because these are necessary for AI.
 */
Haggis::Haggis(Maze *m, Hero* h)
    : bTurn(false), maze(m), hero(h)
{
    setMesh(Mesh::makeCube(0.5));
    t = 0;
}

/**
 * Destructor.
 */
Haggis::~Haggis()
{
    //nothing to destruct
}

/**
 * Draw and animate the haggis.
 */
void Haggis::render(float dt)
{
    if(bTurn)
    {
        takeTurn();
        bTurn = false;
    }

    //make it hover up and down
    t += dt;
    vector4 disp = vector4(0, 0.1*cos(5*t), 0);
    vector4 rest = getPosition();
    setPosition(rest + disp);

    float lightpos[] = {rest.x+disp.x, rest.y+disp.y, rest.z+disp.z, 1};
    glLightfv(GL_LIGHT3, GL_POSITION, lightpos);
    float lightcol[] = {1.0, 1.0, 0.0, 1.0};
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightcol);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.5);
    glEnable(GL_LIGHT3);

    glColor3f(1,1,0);
    Player::render(dt);

    setPosition(rest);
}

/**
 * Sets the bTurn flag to true.
 */
void Haggis::setTurn()
{
    bTurn = true;
}

/**
 * Makes the haggis take a turn.
 */
void Haggis::takeTurn()
{
    //if the haggis can see the hero, there is a 50% chance that it will shoot him
    if (GrenadeAction::canThrow(this)) {
        if(rand() % 2) {
            vector4 diff = getCell()->getPosition() - hero->getCell()->getPosition();
            diff.y = 0;
            if(diff.squaredLength() < GRENADE_RADIUS_SQ) {
                maze->getLevel()->notifyHaggisAction(new GrenadeAction(this, hero, getCell(), hero->getCell()));
                return;
            }
        }
    }

    if (!WalkAction::canWalk(this))
    {
        maze->getLevel()->notifyHaggisAction(new WaitAction(this));
        return;
    }

    if(pathToFollow.empty())
    {
        findPath();
	if(pathToFollow.empty())
	{
	    //the haggis is stuck
	    maze->getLevel()->notifyHaggisAction(new WaitAction(this));
	    return;
	}
    }

    //go to next cell
    Cell *nextCell = pathToFollow.back();
    pathToFollow.pop_back();

    //check that the player is not on this cell
    if(nextCell->hasPlayer())
    {
	//try to jump over the player.
	if(pathToFollow.empty())
	{
	    //decide to wait
	    maze->getLevel()->notifyHaggisAction(new WaitAction(this));
	    return;
	}

	//jump over the player
	nextCell = pathToFollow.back();
	pathToFollow.pop_back();
	maze->getLevel()->notifyHaggisAction(new JumpAction(this, nextCell));
	return;
    }

    maze->getLevel()->notifyHaggisAction(new WalkAction(this, nextCell));
}

/**
 * Finds a random destination and the path to get there.
 */
void Haggis::findPath()
{
    using namespace std;

    //store every visitable cell
    vector<Cell*> visitable;

    //do a breadth-first search of the maze
    queue<Cell*> q;

    //the cell the haggis is on is the start
    q.push(this->cell);
    
    //if the parent is NULL, the cell has not yet been seen
    //in the search
    for(int i = 0; i < maze->getWidth(); i++)
    {
        for(int j = 0; j < maze->getHeight(); j++)
        {
            maze->getCell(j,i)->parent = NULL;
        }
    }

    Cell *curr;
    while(!q.empty())
    {
        //get current cell
        curr = q.front();
        q.pop();

        //push all its neighbours onto the queue
        for(unsigned i = 0; i < curr->neighbours.size(); i++)
        {
            if(curr->neighbours[i]->parent == NULL &&
               !curr->neighbours[i]->isWall && curr->neighbours[i]->isVisible())
            {
                curr->neighbours[i]->parent = curr;
                q.push(curr->neighbours[i]);
                visitable.push_back(curr->neighbours[i]);
            }
        }
    }
    
    //make sure the haggis can get somewhere
    if(visitable.size() < 2)
    {
	pathToFollow.clear();
	return;
    }

    //choose a random destination
    Cell *dest = visitable[rand()%visitable.size()];
    
    //find the path to get there
    pathToFollow.clear();
    while(dest != this->cell)
    {
        pathToFollow.push_back(dest);
        dest = dest->parent;
    }
}


