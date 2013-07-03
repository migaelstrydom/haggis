/************************************************************************
 *
 * cell.h
 * Cell class
 *
 ************************************************************************/

#ifndef CELL_H
#define CELL_H

#include "mesh.h"
#include "texture.h"

#include <vector>
#include <list>

class Entity;

/**
 * The cell class represents a single hexagonal cell.
 */
class Cell
{
    friend class Entity;
    friend class Haggis;

private:
    /**
     * The hexagonal cylinder mesh.
     */
    Mesh *mesh;

    /* The hexagon outline mesh. It is used for drawing the outline and for
     * intersection calculations.
     */
    Mesh *outlineMesh;

    /**
     * The position of the cell in world space.
     */
    vector4 position;

    /**
     * The RGB colour of the cell.
     */
    double color[3];

    /**
     * A list of entites that are on the cell.
     */
    std::list<Entity*> entities;

    /**
     * Indicates whether the cell can be selected by the user.
     */
    bool selectable;

    /**
     * Indicates whether to highlight the cell when rendering.
     */
    bool highlighted;

    /**
     * Indicates whether the cell is visible or not.
     */
    bool visible;

    /**
     * The maze position of this cell.
     */
    int posi, posj;

    /**
     * Indicates whether the cell has a player on it or not.
     */
    bool bHasPlayer;

    /**
     * This is only for the use of the haggis. When doing a search
     * through the maze, it needs to know the parent of this cell in
     * the search.
     */
    Cell *parent;

    /**
     * Does this cell have a wall on it?
     */
    bool isWall;

    /**
     * The height of the wall.
     */
    int wallHeight;

    /**
     * The cell texture. This may be NULL.
     */
    Texture *tex;

    /**
     * The counter-clockwise function. It is used for intersection
     * calculation. Returns true if the points p, outlineMesh(idx) and
     * outlineMesh(idx+1), in that order, are counterclockwise with respect to
     * the xz-plane.
     */
    bool isccw(int idx, vector4 p);

public:
    /**
     * The list of adjacent cells. This is used for pathfinding in the maze.
     */
    std::vector<Cell*> neighbours;

    /**
     * Constructor. Initialises the possible states of the cell.
     */
    Cell();

    /**
     * Destructor of the cell. Deletes the main mesh object and the mesh object
     * storing the cell's outline. All the entities the cell has are also
     * deleted.
     */
    virtual ~Cell();

    /**
     * Calculates and stores in a mesh object the geometry of the cell. This is
     * used for rendering and collision detection.
     */
    void calcMesh();

    /**
     * Renders the cell. float dt is the change in time during
     * the last frame and is used for animation. All the entities
     * on the cell are also rendered.
     */
    void render(float dt);

    /**
     * Checks if the ray r from point src intersects the
     * top surface of the cell.
     * dist is a value returned to the caller that stores
     * the distance from the screen.
     */
    bool intersect(vector4, vector4, vectype&);

    /**
     * Sets the position of the cell.
     */
    void setPosition(vector4 p)
    {
	   position = p;
    }

    /**
     * Returns the position of the cell.
     */
    vector4 getPosition();

    /**
     * Sets the color of the cell.
     */
    void setColor(double r, double g, double b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

    /**
     * Return true if the cell is selectable.
     */
    bool isSelectable();

    /**
     * Set the selectability of the cell.
     */
    void setSelectable(bool sel);

    /**
     * Return true if the cell is highlighted.
     */
    bool isHighlighted();

    /**
     * Set whether the cell is highlighted or not.
     */
    void setHighlighted(bool hl);

    /**
     * Return true if the cell is visible.
     */
    bool isVisible();

    /**
     * Set whether the cell is visible or not.
     */
    void setVisible(bool vis);

    /**
     * Sets (i, j) to the position of this cell in the maze.
     */
    void getMazePosition(int &i, int &j);

    /**
     * Set the maze position of this cell.
     */
    void setMazePosition(int i, int j);

    /**
     * Returns true if this cell has a player on it.
     */
    bool hasPlayer();

    /**
     * Sets the state of the cell having the player.
     */
    void setHasPlayer(bool);

    /**
     * Sets whether this cell has a wall or not.
     */
    void setWall(bool);

    /**
     * This is called if a grenade hits a wall. It decreases the size of the wall by
     * 1 unit.
     */
    void hitWall();

    /**
     * Set the texture to use for the cell.
     */
    void setTexture(Texture *tex);

    /**
     * Returns whether this cell has a wall or not.
     */
    bool getWall();

    /**
     * Returns a list of entities on the cell.
     */
    std::list<Entity*> getEntities();
};

#endif //CELL_H
