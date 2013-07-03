/************************************************************************
 *
 * player.cpp
 * Player class implementation
 *
 ************************************************************************/

#include "player.h"

#include <algorithm>

/**
 * Constructor.
 * Initially, all attributes are set to their maximum.
 */
Player::Player()
{
    health = energy = getMaxStat();
    ammo = getMaxStat();
}

/**
 * Destructor.
 */
Player::~Player()
{
}

/**
 * Returns the player's health.
 */
int Player::getHealth()
{
    return health;
}

/**
 * Sets the player's health. The value is clamped into the allowed range.
 */
void Player::setHealth(int health)
{
    this->health = std::max(std::min(health, getMaxStat()), 0);
}

/**
 * Returns the player's energy.
 */
int Player::getEnergy()
{
    return energy;
}

/**
 * Sets the player's energy. The value is clamped into the allowed range.
 */
void Player::setEnergy(int energy)
{
    this->energy = std::max(std::min(energy, getMaxStat()), 0);
}

/**
 * Returns the number of grenades the player has.
 */
int Player::getAmmo()
{
    return ammo;
}

/**
 * Sets the number of grenades the player has. The value is clamped into
 * the allowed range.
 */
void Player::setAmmo(int ammo)
{
    this->ammo = std::max(std::min(ammo, getMaxStat()), 0);
}

/**
 * Returns the maximum value of a player attribute.
 */
int Player::getMaxStat()
{
    return 16;
}

/**
 * Return true if the player is dead. A player is dead if either their
 * energy or their health are 0.
 */
bool Player::isDead()
{
    return (getEnergy() <= 0) || (getHealth() <= 0);
}
