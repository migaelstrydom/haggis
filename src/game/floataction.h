/************************************************************************
 *
 * floataction.h
 * FloatAction class
 *
 ************************************************************************/

#ifndef FLOATACTION_H
#define FLOATACTION_H

#include "action.h"
#include "billboard.h"
#include "vector4.h"

/**
 * The FloatAction class animates a billboard to floating upwards.
 */
class FloatAction : public Action
{
public:

    /**
     * Constructor. The billboard will be mananged and destroyed by the
     * FloatAction from now on.
     */
    FloatAction(BillBoard *bb);

    /**
     * Destructor.
     */
    virtual ~FloatAction();

    /**
     * Update the animation.
     */
    virtual bool update(float dt);

private:
    /**
     * The billboard to float.
     */
    BillBoard *bb;

    /**
     * The elapsed time since the action was initiated.
     */
    float t;

    /**
     * The time required for the entire action.
     */
    float T;
};

#endif //FLOATACTION_H
