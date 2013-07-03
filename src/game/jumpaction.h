/************************************************************************
 *
 * jumpaction.h
 * JumpAction class
 *
 ************************************************************************/

#ifndef JUMPACTION_H
#define JUMPACTION_H

#include "action.h"
#include "entity.h"
#include "cell.h"
#include "maze.h"
#include "player.h"

/**
 * The JumpAction class makes the player jump.
 */
class JumpAction : public Action {
public:
    /**
     * Constructor.
     *   - player is the player that must be moved
     *   - dest is the destination cell
     */
    JumpAction(Player *player, Cell *dest);

    /**
     * Returns true if the player has enough energy to jump.
     */
    static bool canJump(Player *player);

    /**
     * Mark all the cells reachable by the player when jumping selectable.
     */
    static void markSelectable(Player *player, Maze *maze);

    /**
     * Destructor.
     */
    virtual ~JumpAction();

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
     * The velocity vector of the player.
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

#endif //JUMPACTION_H

