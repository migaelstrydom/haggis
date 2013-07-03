/************************************************************************
 *
 * buttonevent.cpp
 * ButtonEvent class implementation
 *
  ************************************************************************/

#include "buttonevent.h"

/**
 * Constructor.
 *   - b is the button that was pressed or released
 *   - state is the current state of the button
 *   - pos is the position of the pointer when the button was pressed
 *     or released relative to the window
 */
ButtonEvent::ButtonEvent(ButtonEvent::button b, ButtonEvent::bstate state,
                         vector4 pos)
    : b(b), state(state), pos(pos)
{
}

/**
 * Copy constructor. The offset is subtracted from the position.
 */
ButtonEvent::ButtonEvent(ButtonEvent event, vector4 offset)
{
    b = event.b;
    state = event.state;
    pos = event.pos - offset;
}

/**
 * Return the button that was pressed or released.
 */
ButtonEvent::button ButtonEvent::getButton()
{
    return b;
}

/**
 * Return the current state of the button.
 */
ButtonEvent::bstate ButtonEvent::getState()
{
    return state;
}

/**
 * Return the position of the pointer relative to the window.
 */
vector4 ButtonEvent::getPosition()
{
    return pos;
}
