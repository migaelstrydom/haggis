/************************************************************************
 *
 * overlay.h
 * Overlay class
 *
 ************************************************************************/

#ifndef OVERLAY_H
#define OVERLAY_H

#include "window.h"
#include "button.h"
#include "staticimage.h"
#include "maze.h"
#include "progressbar.h"

#include <vector>

class Level;

/**
 * The Overlay contains the user interface for the maze.
 */
class Overlay : public Window
{
public:
    /**
     * Constructor.
     */
    Overlay();

    /**
     * Destructor.
     */
    virtual ~Overlay();

    /**
     * Set the level to pass actions to.
     */
    void setLevel(Level *level);

    /**
     * Set the maze.
     */
    void setMaze(Maze *maze);

    /**
     * Set the size of the window. This resizes and repositions all the
     * user interface elements.
     */
    virtual void setSize(vector4 size);

    /**
     * Returns true if the user has pressed the exit button.
     */
    bool shouldExit();

protected:
    /**
     * Draw the overlay and processes button events.
     */
    virtual void draw(float dt);

    /**
     * Looks at which button has been pressed and determines what
     * needs to be done next. Called from draw.
     */
    void handleButton(int n);

    /**
     * Handle the selection of a maze cell.
     */
    void handleCellSelection();

private:
    /**
     * The level to send events to.
     */
    Level *level;

    /**
     * Set the current maze.
     */
    Maze *maze;

    /**
     * The wait action button.
     */
    std::vector<Button*> actions;

    /**
     * The hero's and the haggis's turn images.
     */
    StaticImage *heroturn, *haggisturn, *actionturn;

    /**
     * The attribute labels.
     */
    std::vector<StaticImage*> labels;

    /**
     * The attribute progress bars.
     */
    std::vector<ProgressBar*> bars;

    /**
     * The exit button.
     */
    Button *btnexit;

    /**
     * The state of the machine.
     */
    enum {NORMAL, WAITING_FOR_CELL} state;

    /**
     * If WAITING_FOR_CELL, this is the selected action number.
     */
    int action;

    /**
     * Setup the maze to allow the user to select a cell. The state is
     * changed to WAITING_FOR_CELL. The current action is changed to act.
     */
    void getCellSelection(int act);
};

#endif //OVERLAY_H

