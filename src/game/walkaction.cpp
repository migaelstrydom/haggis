/************************************************************************
 *
 * walkaction.cpp
 * WalkAction class implementation
 *
 ************************************************************************/

#include "walkaction.h"

#define VEL 10.0 // animation speed
#define ENERGY 1 // amount of energy needed to walk

/**
 * Returns true if the player can perform a walk action. This checks
 * that the player has enough energy.
 */
bool WalkAction::canWalk(Player *player)
{
    return (player->getEnergy() >= ENERGY);
}

/**
 * Mark all the cells reachable by walking selectable.
 */
void WalkAction::markSelectable(Player *player, Maze *maze)
{
    if (!player->getCell())
    {
        return;
    }

    for(std::vector<Cell*>::iterator i = player->getCell()->neighbours.begin();
        i != player->getCell()->neighbours.end(); i++)
    {
        //can't walk on walls or where another player is.
        if((*i)->getWall() || (*i)->hasPlayer() || !(*i)->isVisible())
            continue;
        (*i)->setSelectable(true);
    }
}

/**
 * Constructor.
 *   - player is the player that must be moved
 *   - dest is the destination cell
 */
WalkAction::WalkAction(Player *player, Cell *dest)
    : player(player), dest(dest)
{
    assert(canWalk(player));

    initial = player->getPosition();
    t = 0;

    if (player->getCell()) {
        // calculate the time it will take to get there are the speed=VEL
        vector4 d = dest->getPosition() - player->getCell()->getPosition();
        vel = d * (VEL / d.length());
        T = d.length() / VEL;
    } else {
        T = -1;
    }
}

/**
 * Destructor.
 */
WalkAction::~WalkAction()
{
}

/**
 * Update the animation.
 */
bool WalkAction::update(float dt)
{
    t += dt;

    if (t >= T)
    {
        // the animation has finished
        player->setPosition(initial);
        player->setCell(dest, true);
        player->setEnergy(player->getEnergy() - ENERGY);
        return false;
    }
    else
    {
        player->setPosition(initial + vel*t);
    }

    return true;
}
