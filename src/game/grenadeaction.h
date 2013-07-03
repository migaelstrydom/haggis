/************************************************************************
 *
 * grenadeaction.h
 * GrenadeAction class
 *
 ************************************************************************/

#ifndef GRENADEACTION_H
#define GRENADEACTION_H

#include "action.h"
#include "entity.h"
#include "cell.h"
#include "maze.h"
#include "player.h"
#include "floataction.h"

/**
 * The GrenadeAction class animates a grenade being thrown.
 */
class GrenadeAction : public Action {
public:
    /**
     * Constructor.
     *   - player is the player who is throwing the grenade
     *   - opp is the opponent player in case the grenade lands on it
     *   - src is the cell from which to move
     *   - dest is the destination cell
     */
    GrenadeAction(Player *player, Player *opp, Cell *src, Cell *dest);

    /**
     * Returns true if the player has enough energy to throw a grenade.
     */
    static bool canThrow(Player *player);

    /**
     * Mark all the cells reachable by grenade selectable.
     */
    static void markSelectable(Player *player, Maze *maze);

    /**
     * Destructor.
     */
    virtual ~GrenadeAction();

    /**
     * Update the animation.
     */
    virtual bool update(float dt);

private:
    /**
     * The player who is throwing the grenade.
     */
    Player *player;

    /**
     * The player who is not throwing the grenade.
     */
    Player *opponent;

    /**
     * The src cell from which the grenade is thrown
     */
    Cell *src;

    /**
     * The cell that the player is being moved to.
     */
    Cell *dest;

    /**
     * The position of the grenade.
     */
    vector4 position;

    /**
     * The object that makes sure the grenade is rendered.
     */
    Entity *grenade;

    /**
     * The float action for notifying the opponent health loss.
     */
    FloatAction *floater;

    /**
     * The health texture for the health loss billboard.
     */
    Texture *texhealth;

    /**
     * The velocity vector.
     */
    vector4 vel;

    /**
     * The elapsed time since the action was initiated.
     */
    float t;

    /**
     * The time required for the entire action.
     */
    float T;
};

#endif //GRENADEACTION_H

