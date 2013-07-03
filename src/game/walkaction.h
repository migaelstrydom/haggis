/************************************************************************
 *
 * walkaction.h
 * WalkAction class
 *
 ************************************************************************/

#ifndef WALKACTION_H
#define WALKACTION_H

#include "action.h"
#include "player.h"
#include "cell.h"
#include "maze.h"

/**
 * The WalkAction class moves a player from one cell to another.
 */
class WalkAction : public Action {
public:

    /**
     * Returns true if the player can perform a walk action. This checks
     * that the player has enough energy.
     */
    static bool canWalk(Player *player);

    /**
     * Mark all the cells reachable by walking selectable.
     */
    static void markSelectable(Player *player, Maze *maze);

    /**
     * Constructor.
     *   - player is the player that must be moved
     *   - dest is the destination cell
     */
    WalkAction(Player *player, Cell *dest);

    /**
     * Destructor.
     */
    virtual ~WalkAction();

    /**
     * Update the animation.
     */
    virtual bool update(float dt);

private:
    /**
     * The player that is being moved.
     */
    Player *player;

    /**
     * The cell that the player is being moved to.
     */
    Cell *dest;

    /**
     * The initial position of the player.
     */
    vector4 initial;

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

#endif //WALKACTION_H
