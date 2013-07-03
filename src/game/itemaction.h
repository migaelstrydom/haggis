/************************************************************************
 *
 * itemaction.h
 * ItemAction class
 * Performs the action of an item being picked up by the hero.
 *
  ************************************************************************/

#ifndef ITEMACTION_H
#define ITEMACTION_H

#include "action.h"
#include "player.h"
#include "item.h"
#include "billboard.h"

/**
 * The ItemAction class animates an item being picked up by the hero.
 */
class ItemAction : public Action
{
public:

    /**
     * Constructor.
     */
    ItemAction(Item*, Player*);

    /**
     * Destructor.
     */
    virtual ~ItemAction();

    /**
     * Update the animation.
     */
    virtual bool update(float dt);

private:
    /**
     * The item that the hero has just stepped on.
     */
    Item *item;

    /**
     * The item's billboard.
     */
    BillBoard *bb;

    /**
     * The player. This is necessary so that the player's attributes can be
     * updated.
     */
    Player *player;

    /**
     * The elapsed time since the action was initiated.
     */
    float t;
};

#endif //ITEMACTION_H
