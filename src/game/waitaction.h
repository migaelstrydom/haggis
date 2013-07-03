/************************************************************************
 *
 * waitaction.h
 * WaitAction class
 *
 ************************************************************************/

#ifndef WAITACTION_H
#define WAITACTION_H

#include "action.h"
#include "player.h"
#include "cell.h"

/**
 * The WaitAction class causes the player to do nothing for a turn.
 */
class WaitAction : public Action
{
public:
    /**
     * Returns true if the player can perform a wait action. This method
     * always returns true.
     */
    static bool canWait(Player *player);

    /**
     * Constructor.
     */
    WaitAction(Player *player);

    /**
     * Destructor.
     */
    virtual ~WaitAction();

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
     * The player's initial rotation.
     */
    float initial;

    /**
     * The elapsed time since the action was initiated.
     */
    float t;

    /**
     * The time required for the entire action.
     */
    float T;
};

#endif //WAITACTION_H
