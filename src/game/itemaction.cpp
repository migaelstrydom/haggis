/************************************************************************
 *
 * itemaction.cpp
 * ItemAction class implementation
 *
 ************************************************************************/

#include "itemaction.h"

#include <cmath>

#define MOVING_TIME 0.5    //how long the item is moving
#define FLOATING_TIME 0.5  //how long the item is stationary
#define HEALTH_INCREASE 4  //by how much the health item increases health
#define ENERGY_INCREASE 4  //by how much the energy item increases energy
#define HEALTH_DECREASE 4  //by how much the trap item decreases health

/**
 * Default constructor. Sets the item and the hero.
 */
ItemAction::ItemAction(Item* i, Player *p)
    : item(i), player(p)
{
    t = 0;

    //do something depending on the type of item
    if(item->getType() == Item::HEALTH)
    {
	player->setHealth(player->getHealth()+HEALTH_INCREASE);
    }
    else if(item->getType() == Item::GRENADE)
    {
	player->setAmmo(player->getAmmo()+1);
    }
    else if(item->getType() == Item::ENERGY)
    {
	player->setEnergy(player->getEnergy()+ENERGY_INCREASE);
    }
    else if(item->getType() == Item::TRAP)
    {
	player->setHealth(player->getHealth()-HEALTH_DECREASE);
    }

    bb = i->makeBillBoard();
}

/**
 * Destructor.
 */
ItemAction::~ItemAction()
{
    // nothing to destroy
}

/**
 * Updates the animation of this action, depending on the type of item
 * that was picked up.
 */
bool ItemAction::update(float dt)
{
    //increase time
    t += dt;

    //if the action has existed for long enough
    if (t >= MOVING_TIME + FLOATING_TIME)
    {
        delete item;
        delete bb;
        return false;
    }
    else if(t < MOVING_TIME)  //if it is still in the moving stage
    {
        bb->setPosition(bb->getPosition() + vector4(0,t*0.5,0));
    }

    return true;
}
