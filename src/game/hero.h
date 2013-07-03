/************************************************************************
 *
 * hero.h
 * Hero class
 *
 ************************************************************************/

#ifndef HERO_H
#define HERO_H

#include "player.h"

/**
 * The Hero represents the human player.
 */
class Hero : public Player {
public:

    /**
     * Constructor.
     */
    Hero();

    /**
     * Destructor.
     */
    virtual ~Hero();

    /**
     * Render the entity.
     */
    virtual void render(float dt);

private:

    /**
     * The current time. Used for animation.
     */
    double t;
};

#endif //HERO_H

