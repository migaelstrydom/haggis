/************************************************************************
 *
 * jumpaction.cpp
 * JumpAction class implementation
 *
 ************************************************************************/

#include "jumpaction.h"
#include <GL/glu.h>

#define VEL 10.0
#define ACC -100.0
#define SELECTABLE_RADIUS_SQ 25.0
#define CELL_CHECK_RADIUS 4   //approximately selection area
#define ENERGY 5

//for some stupid compilers
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * Constructor.
 *   - player is the player to move
 *   - dest is the destination cell
 */
JumpAction::JumpAction(Player *player, Cell *dest)
    : player(player), dest(dest)
{
    t = 0;

    //if the player is not on a cell
    //(should not happen but check just in case.)
    if(!player->getCell())
    {
        T = -1;
        return;
    }
    vector4 d = dest->getPosition() - player->getCell()->getPosition();
    vel = d * (VEL / d.length());
    T = d.length() / VEL;
    //some high school physics:
    //s = ut + 1/2*a*t^2
    //s/t - 1/2*a*t = u
    vel.y = d.y/T - 0.5*ACC*T;

    initial = player->getPosition();
}

/**
 * Destructor.
 */
JumpAction::~JumpAction()
{
    //nothing to destruct
}

/**
 * Update the animation and move the player.
 */
bool JumpAction::update(float dt)
{
    t += dt;

    //if the player has reached its destination,
    //which it should have by this time, end the action.
    if (t >= T)
    {
        //move player to new cell
        player->setPosition(initial);
        player->setCell(dest, true);
        player->setEnergy(player->getEnergy() - ENERGY);
        return false;
    }

    vector4 position = player->getPosition();

    vel.y += ACC*dt;
    position += vel * dt;

    player->setPosition(position);

    return true;
}

/**
 * Checks if the player has enough energy for a jump.
 */
bool JumpAction::canJump(Player *player)
{
    return (player->getEnergy() >= ENERGY);
}

/**
  * Mark all the cells reachable by a jump selectable.
  * Accepts the player, so that it is known around which area
  * to make cells selectable, and the maze containing the cells.
  */
void JumpAction::markSelectable(Player *player, Maze *maze)
{
    //if the player is not on a cell
    if (!player->getCell()) {
        return;
    }

    //get the position of the player
    int pi, pj;
    player->getCell()->getMazePosition(pi, pj);

    // check all adjacent cells
    const int mini = max(0, pi-CELL_CHECK_RADIUS);
    const int maxi = min(maze->getHeight()-1, pi+CELL_CHECK_RADIUS);
    const int minj = max(0, pj-CELL_CHECK_RADIUS);
    const int maxj = min(maze->getWidth()-1, pj+CELL_CHECK_RADIUS);
    for(int i = mini; i <= maxi; i++)
    {
        for (int j = minj; j <= maxj; j++)
        {
            if ((i == pi) && (j == pj))
            {
                // can't throw grenade on self
                continue;
            }

            //get cell under consideration
            Cell *c = maze->getCell(i, j);

            //cannot jump onto walls or other players
            if(c->getWall() || c->hasPlayer() || !c->isVisible())
                continue;

            //get relative position
            vector4 relpos = c->getPosition() - player->getCell()->getPosition();
            relpos.y = 0;
            //if the cell is in range, make it selectable
            if(relpos.squaredLength() < SELECTABLE_RADIUS_SQ)
            {
                c->setSelectable(true);
            }
        }
    }
}
