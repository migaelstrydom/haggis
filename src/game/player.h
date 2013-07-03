/************************************************************************
 *
 * player.h
 * Player class
 *
 ************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "vector4.h"
#include "entity.h"

/**
 * The Player represents either the user or the haggis. It stores the
 * player attributes like health, energy and ammunition. Each attribute is
 * an integer in the range [0, maxstat] where maxstat is the number returned
 * by getMaxStat().
 */
class Player : public Entity {
public:

    /**
     * Constructor.
     * Initially, all attributes are set to their maximum.
     */
    Player();

    /**
     * Destructor.
     */
    virtual ~Player();

    /**
     * Returns the player's health.
     */
    int getHealth();

    /**
     * Sets the player's health. The value is clamped into the allowed range.
     */
    void setHealth(int health);

    /**
     * Returns the player's energy.
     */
    int getEnergy();

    /**
     * Sets the player's energy. The value is clamped into the allowed range.
     */
    void setEnergy(int energy);

    /**
     * Returns the number of grenades the player has.
     */
    int getAmmo();

    /**
     * Sets the number of grenades the player has. The value is clamped into
     * the allowed range.
     */
    void setAmmo(int ammo);

    /**
     * Returns the maximum value of a player attribute.
     */
    int getMaxStat();

    /**
     * Return true if the player is dead. A player is dead if either their
     * energy or their health are 0.
     */
    bool isDead();

private:
    /**
     * The player's health.
     */
    int health;

    /**
     * The player's energy.
     */
    int energy;

    /**
     * The number of grenade the player has.
     */
    int ammo;
};

#endif //PLAYER_H
