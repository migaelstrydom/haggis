/************************************************************************
 *
 * waitaction.cpp
 * WaitAction class implementation
 *
 ************************************************************************/

#include "waitaction.h"

#include <cmath>

/**
 * Returns true if the player can perform a wait action. This method
 * always returns true.
 */
bool WaitAction::canWait(Player *player)
{
    return true;
}

/**
 * Constructor.
 */
WaitAction::WaitAction(Player *player)
    : player(player)
{
    initial = player->getRotation();
    t = 0;
    T = 0.5; // wait for half a second
}

/**
 * Destructor.
 */
WaitAction::~WaitAction()
{
}

/**
 * Update the animation.
 */
bool WaitAction::update(float dt)
{
    t += dt;

    if (t >= T) {
        // the animation is complete
        player->setRotation(initial);
        return false;
    } else {
        player->setRotation(initial + (t/T)*2*M_PI);
        return true;
    }
}
