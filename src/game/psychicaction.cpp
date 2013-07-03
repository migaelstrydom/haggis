/************************************************************************
 *
 * psychicaction.h
 * PsychicAction class implementation
 *
 ************************************************************************/

#include "psychicaction.h"

#define ENERGY 1

/**
 * Returns true if the player can perform a psychic action. This checks
 * that the player has enough energy.
 */
bool PsychicAction::canPsychic(Player *player)
{
    return (player->getEnergy() >= ENERGY);
}

/**
 * Mark all the cells that can by psychiced selectable.
 */
void PsychicAction::markSelectable(Player *player, Maze *maze)
{
    if (player->getCell()) {  //if cell is initialised
        std::vector<Cell*> neigh = player->getCell()->neighbours; 
        std::vector<Cell*>::iterator i;
        for (i=neigh.begin(); i != neigh.end(); i++) { //go through all the neighbours
            Cell *c = *i;
	    //if it is allowed to, make it selectable
            if (!c->getWall() && c->isVisible() && !c->hasPlayer()) {
                c->setSelectable(true);
            }
        }
    }
}

/**
 * Constructor.
 *   - player is the player that must be moved
 *   - target is the target cell of the psychicization
 */
PsychicAction::PsychicAction(Player *player, Cell *target)
    : player(player), target(target)
{
    assert(canPsychic(player));
}

/**
 * Destructor.
 */
PsychicAction::~PsychicAction()
{
    //nothing to destruct
}

/**
 * Update the animation.
 */
bool PsychicAction::update(float dt)
{
    std::list<Entity*> ent = target->getEntities();
    std::list<Entity*>::iterator i;
    for (i=ent.begin(); i != ent.end(); i++) {
        Entity *e = *i;

        // we don't bother checking if the entity is an item since
        // everything else should be visible anyway
        e->setVisibility(true);
    }

    return false;
}
