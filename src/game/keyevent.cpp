/************************************************************************
 *
 * keyevent.cpp
 * KeyEvent class implementation
 *
 ************************************************************************/

#include "keyevent.h"

/**
 * Constructor.
 *   - key is the key that was pressed or released
 *   - state is the new state of the key
 */
KeyEvent::KeyEvent(char key, kstate state)
    : key(key), state(state)
{
}

/**
 * Returns the key that was pressed or released.
 */
char KeyEvent::getKey()
{
    return key;
}

/**
 * Returns the new state of the key.
 */
KeyEvent::kstate KeyEvent::getState()
{
    return state;
}
