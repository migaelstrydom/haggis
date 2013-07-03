/************************************************************************
 *
 * entity.h
 * Entity class
 *
 ************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#include "vector4.h"
#include "cell.h"
#include "mesh.h"

class Entity
{
public:

    /**
     * Default constructor.
     */
    Entity();

    /**
     * Destructor.
     */
    virtual ~Entity();

    /**
     * Sets the cell on which the entity is currently. This function interacts
     * with the private variables in class Cell. If isPlayer is true (and it is
     * false by default), then the cell's hasPlayer flag will be set as well.
     * The cell may be set to NULL.
     */
    void setCell(Cell *cell, bool isPlayer = false);

    /**
     * Return the cell that contains this entity. The cell may be NULL.
     */
    Cell *getCell();

    /**
     * Get the position of the entity relative to the cell.
     */
    vector4 getPosition();

    /**
     * Set the position of the entity relative to the cell.
     */
    void setPosition(vector4 pos);

    /**
     * Get the angular displacement about the y axis in radians.
     */
    float getRotation();

    /**
     * Set the angular displacement about the y axis in radians.
     */
    void setRotation(float theta);

    /**
     * Set the mesh that is rendered for this entity. The entity is responsible
     * for deleting the mesh after it has been set.
     */
    void setMesh(Mesh *mesh);

    /**
     * Render the cell.
     */
    virtual void render(float dt);

    /**
     * Sets the "visible" flag.
     */
    void setVisibility(bool);

    /**
     * Returns true if the entity is visible, false if not.
     */
    bool isVisible();

protected:
    /**
     * The position of the entity relative to the cell.
     */
    vector4 pos;

    /**
     * The angular displacement about the y axis in radians.
     */
    float theta;

    /**
     * The cell that contains the entity.
     */
    Cell *cell;

    /**
     * The mesh to render.
     */
    Mesh *mesh;

    /**
     * Is the entity visible, or is it hiding on the cell?
     */
    bool visible;
};

#endif
