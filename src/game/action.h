/************************************************************************
 *
 * action.h
 * Action class
 *
 ************************************************************************/

#ifndef ACTION_H
#define ACTION_H

/**
 * The Action classes perform actions like moving a player from one cell to
 * another at the request of the user.
 */
class Action {
public:

    /**
     * Destructor.
     */
    virtual ~Action();

    /**
     * Update the game state. False is returned if the action is complete.
     */
    virtual bool update(float dt);
};

#endif //ACTION_H
