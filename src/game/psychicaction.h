/************************************************************************
 *
 * psychicaction.h
 * PsychicAction class
 *
 ************************************************************************/

#ifndef PSYCHICACTION_H
#define PSYCHICACTION_H

#include "action.h"
#include "player.h"
#include "cell.h"
#include "maze.h"

/**
 * The PsychicAction class reveals the hidden items on an adjacent cell.
 */
class PsychicAction : public Action {
public:

    /**
     * Returns true if the player can perform a psychic action. This checks
     * that the player has enough energy.
     */
    static bool canPsychic(Player *player);

    /**
     * Mark all the cells that can by psychiced selectable.
     */
    static void markSelectable(Player *player, Maze *maze);

    /**
     * Constructor.
     *   - player is the player that must be moved
     *   - target is the target cell of the psychicization
     */
    PsychicAction(Player *player, Cell *target);

    /**
     * Destructor.
     */
    virtual ~PsychicAction();

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
     * The cell that the player wants revealed.
     */
    Cell *target;
};

#endif // PSYCHICACTION_H
