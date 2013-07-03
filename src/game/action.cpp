/************************************************************************
 *
 * action.cpp
 * Action class implementation
 *
 ************************************************************************/

#include "action.h"

/**
 * Destructor.
 */
Action::~Action()
{
}

/**
 * General update method. It will be overridden more in each bace class.
 */
bool Action::update(float dt)
{
    return false;
}
