/************************************************************************
 *
 * floataction.cpp
 * FloatAction class implementation
 *
 ************************************************************************/

#include "floataction.h"

/**
 * Constructor. The billboard will be mananged and destroyed by the
 * FloatAction from now on.
 */
FloatAction::FloatAction(BillBoard *bb)
    : bb(bb)
{
    t = 0;
    T = 0.5;
}

/**
 * Destructor.
 */
FloatAction::~FloatAction()
{
    delete bb;
}

/**
 * Update the animation.
 */
bool FloatAction::update(float dt)
{
    t += dt;

    if (t >= T) {
        return false;
    } else {
        bb->setPosition(bb->getPosition() + vector4(0,t*0.5,0));
        return true;
    }
}
