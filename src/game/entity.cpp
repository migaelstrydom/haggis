/************************************************************************
 *
 * entity.cpp
 * Entity class implementation
 *
 ************************************************************************/

#include "entity.h"
#include "vector4.h"
#include "cell.h"

#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <cmath>

/**
 * Default constructor.
 */
Entity::Entity()
    : cell(NULL), mesh(NULL), visible(true)
{
}

/**
 * Destructor.
 */
Entity::~Entity()
{
    setCell(NULL);
    if (mesh) {
        delete mesh;
        mesh = NULL;
    }
}

/**
 * Sets the cell on which the entity is currently. This function interacts
 * with the private variables in class Cell. If isPlayer is true (and it is
 * false by default), then the cell's hasPlayer flag will be set as well.
 * The cell may be set to NULL.
 */
void Entity::setCell(Cell *cell, bool isPlayer)
{
    if (this->cell) {
        // remove this from the entities list in the current cell

        for (std::list<Entity*>::iterator i=this->cell->entities.begin();
             i != this->cell->entities.end(); i++) {
            if (*i == this) {
                this->cell->entities.erase(i);
                if(isPlayer)
                    this->cell->bHasPlayer = false;  //a cell can have at most one player.
                break;
            }
        }
    }

    this->cell = cell;

    if (this->cell) {
        // add this to the entities list of the new cell
        cell->entities.push_back(this);
	if(isPlayer)
	    this->cell->bHasPlayer = true;
    }
}

/**
 * Return the cell that contains this entity. The cell may be NULL.
 */
Cell *Entity::getCell()
{
    return cell;
}

/**
 * Get the position of the entity relative to the cell.
 */
vector4 Entity::getPosition()
{
    return pos;
}

/**
 * Set the position of the entity relative to the cell.
 */
void Entity::setPosition(vector4 pos)
{
    this->pos = pos;
}

/**
 * Get the angular displacement about the y axis in radians.
 */
float Entity::getRotation()
{
    return theta;
}

/**
 * Set the angular displacement about the y axis in radians.
 */
void Entity::setRotation(float theta)
{
    this->theta = theta;
}

/**
 * Set the mesh that is rendered for this entity. The entity is responsible
 * for deleting the mesh after it has been set.
 */
void Entity::setMesh(Mesh *mesh)
{
    if (this->mesh) {
        delete this->mesh;
    }
    this->mesh = mesh;
}

/**
 * Render the cell.
 */
void Entity::render(float dt)
{
    if(!visible)
        return;

    glPushMatrix();
    glTranslatef(getPosition().x, getPosition().y, getPosition().z);
    glRotatef(getRotation()*180.0/M_PI, 0, 1, 0);

    if (mesh)
    {
        mesh->render(GL_QUADS);
    }

    glPopMatrix();
}

/**
 * Sets the "visible" flag.
 */
void Entity::setVisibility(bool v)
{
    visible = v;
}

/**
 * Returns true if the entity is visible, false if not.
 */
bool Entity::isVisible()
{
    return visible;
}
