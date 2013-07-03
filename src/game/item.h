/************************************************************************
 *
 * item.h
 * Item class - Represents an item on a cell that the hero can pick up.
 *
 ************************************************************************/

#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "texture.h"
#include "level.h"
#include "billboard.h"

#define NUM_ITEMS 4  //number of different item types

class Item : public Entity
{
public:
    /**
     * The different types of item this could be.
     */
    enum ItemType {HEALTH = 0, ENERGY = 1, GRENADE, TRAP};

    /**
     * Default constructor.
     */
    Item(Level *);

    /**
     * Destructor.
     */
    ~Item();

    /**
     * Render the cell.
     */
    void render(float dt);

    /**
     * Sets the item type.
     */
    void setType(ItemType);

    /**
     * Returns the item type.
     */
    ItemType getType();

    /**
     * Create a billboard object with the item texture. The billboard entity
     * initially has the same cell and position as the item. It is the caller's
     * responsibility to destroy the billboard.
     */
    BillBoard *makeBillBoard();

 private:
    /**
     * The type of this item.
     */
    ItemType itemType;

    /**
     * A pointer to the level, so that it can know where the hero is
     * and register actions, such as when the hero grabs the item.
     */
    Level *level;

    /**
     * A flag to indicate whether the item has been activated or not.
     */
    bool spent;
};

#endif
