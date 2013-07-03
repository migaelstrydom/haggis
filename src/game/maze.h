/************************************************************************
 *
 * maze.h
 * Maze class. Is in charge of the maze and all its cells.
 *
 ************************************************************************/

#ifndef MAZE_H
#define MAZE_H

#include <string>   //for filename

//classes necessary in this class
#include "cell.h"
#include "window.h"
#include "camera.h"
#include "texture.h"

class Level;

class Maze : public Window
{
 private:
    Cell** cells;
    int width, height;

    Cell *heroCell;
    Cell *haggisCell;  //the cell the haggis initially occupies.
    bool bLoaded;   //true if maze is loaded

    //should the camera zoom in or out?
    bool zoomIn, zoomOut;

    bool bLeftClicked;   //true if the left mouse button was clicked

    bool rightDown; // true if the right mouse button is down
    vector4 rightOrigin; // the point where the button was pressed
    float rightPhi; // the camera phi when the button was pressed
    float rightTheta; // the camera theta when the button was pressed

    bool midDown; // true if the middle button is down
    vector4 midOrigin; // the point where the button was pressed
    float midZoom; // the camera zoom when the button was pressed

    //the camera in the maze
    Camera camera;

    /**
     * The level to send events to.
     */
    Level *level;

    /**
     * True if cell selection is enabled.
     */
    bool selectionEnabled;

    /**
     * The last selected cell.
     */
    Cell *selectedCell;

 public:
    Maze();
    virtual ~Maze();

    void load(std::string);  //loads maze from file
    void unload();

    /**
     * Returns the cell that the hero initially occupies. This may be NULL
     * if the hero cell was not set in the level file.
     */
    Cell *getHeroCell();
    
    /**
     * Returns the cell that the haggis initially occupies. This may be NULL
     * if the haggis cell was not set in the level file.
     */
    Cell *getHaggisCell();

    /**
     * Set the level to send events to.
     */
    void setLevel(Level *level);
    
    /**
     * Get level to send event to.
     */
    Level* getLevel();

    /**
     * Handle key events. These are used to zoom in and out.
     */
    virtual void handleKeyEvent(KeyEvent event);

    /**
     * Set whether user is allowed to select cells or not.
     */
    void setCellSelectionEnable(bool enabled);

    /**
     * Returns true if cell selection is enabled.
     */
    bool isCellSelectionEnabled();

    /**
     * Returns the last cell selected since cell selection was last enabled.
     * This may be NULL if no cell has been selected yet or if cell selection
     * is disabled.
     */
    virtual Cell *getSelection();  //virtual so that it can be overridden for unit test

    /**
     * Returns the maze width.
     */
    int getWidth();

    /**
     * Returns the maze height;
     */
    int getHeight();

    /**
     * Returns the cell at position (i, j) where i is the row and j is the
     * column.
     */
    Cell *getCell(int i, int j);
    
    /**
     * Calculates the neighbours of the cell, and stores them.
     */
    void findCellNeighbours(Cell*);

protected:
    /**
     * Draws the maze.
     */
    virtual void draw(float dt);

    /**
     * When a button is pressed, this function is called.
     */
    virtual bool onHandleButtonEvent(ButtonEvent);
};

#endif //MAZE_H
