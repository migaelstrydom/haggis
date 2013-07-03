/************************************************************************
 *
 * grenadeaction.cpp
 * GrenadeAction class implementation
 *
 ************************************************************************/

#include "grenadeaction.h"
#include <GL/glu.h>
#include <iostream>

#define VEL 10.0
#define ACC -100.0
#define SELECTABLE_RADIUS_SQ 25.0
#define CELL_CHECK_RADIUS 4   //approximately selection area
#define DAMAGE 4

//for some compilers
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * Constructor.
 *   - src is the cell from which to move
 *   - dest is the destination cell
 */
GrenadeAction::GrenadeAction(Player *player, Player *opp,
                             Cell *src, Cell *dest)
    : player(player), opponent(opp), src(src), dest(dest),
      floater(NULL), texhealth(NULL)
{
    assert(canThrow(player));

    grenade = new Entity();
    grenade->setCell(src);
    t = 0;

    vector4 d = dest->getPosition() - src->getPosition();
    vel = d * (VEL / d.length());
    T = d.length() / VEL;

    //s = ut + 1/2*a*t^2
    //s/t - 1/2*a*t = u
    vel.y = d.y/T - 0.5*ACC*T;

    //create grenade mesh
    grenade->setMesh(Mesh::makeCube(0.25));
}

/**
 * Destructor.
 */
GrenadeAction::~GrenadeAction()
{
    delete grenade;

    if (floater) {
        delete floater;
    }
    if (texhealth) {
        delete texhealth;
    }
}

/**
 * Update the animation and render the grenade.
 */
bool GrenadeAction::update(float dt)
{
    t += dt;

    //if the grenade has reached its destination,
    //which it should have by this time, end the action.
    if (t >= T)
    {
        if (floater) {
            return floater->update(dt);
        } else {
            player->setAmmo(player->getAmmo() - 1);

            //in the future, this is where an explosionaction is created
            //that takes care of the damage. For now, damage is done here.

            if(dest->getWall()) {
                // we have hit a wall

                dest->hitWall();
                return false;

            } else if (dest == opponent->getCell()) {
                // we have hit the opponent

                opponent->setHealth(opponent->getHealth() - DAMAGE);

                // create a floating health loss animation

                texhealth = Texture::load("images/overlay/hit.png");

                BillBoard *bb = new BillBoard(texhealth);
                bb->setPosition(opponent->getPosition());
                bb->setCell(opponent->getCell());

                floater = new FloatAction(bb);
            }
	    else
	    {
		return false;
	    }
        }
    }

    vel.y += ACC*dt;
    position += vel * dt;

    grenade->setPosition(position);

    return true;
}

/**
 * Returns true if the player has a grenade to throw, false otherwise.
 */
bool GrenadeAction::canThrow(Player *player)
{
    return (player->getAmmo() >= 1);
}

/**
  * Mark all the cells reachable by grenade selectable.
  * Accepts the player as parameter, so that it is known around which area
  * to make cells selectable, and the maze containing the cells.
  */
void GrenadeAction::markSelectable(Player *player, Maze *maze)
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
