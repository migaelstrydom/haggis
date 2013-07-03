/************************************************************************
 *
 * cell.cpp
 * Cell class implementation
 *
 ************************************************************************/

#include "cell.h"
#include "vector4.h"
#include "entity.h"

#include <GL/gl.h>

#include <cmath>
#include <vector>
#include <iostream>

#define MAX_WALL_HEIGHT 3  //the maximum wall height

/**
 * Constructor. Initialises the possible states of the cell.
 */
Cell::Cell()
{
    color[0] = 1;
    color[1] = 1;
    color[2] = 1;
    isWall = false;
    selectable = false;
    highlighted = false;
    visible = true;
    bHasPlayer = false;
    tex = NULL;
    wallHeight = 0;
    calcMesh();
}

/**
 * Destructor of the cell. Deletes the main mesh object and the mesh object
 * storing the cell's outline. All the entities the cell has are also deleted.
 */
Cell::~Cell()
{
    delete mesh;
    delete outlineMesh;

    //free entities
    while(entities.size())
    {
        delete (entities.back());
    }
}

/**
 * Calculates and stores in a mesh object the geometry of the cell. This is for
 * rendering and collision detection.
 */
void Cell::calcMesh()
{
    // Don't even bother trying to work out what's going on here. Just be
    // reassured that it works. If there's a bug, you'll be better off
    // rewriting the function.

    outlineMesh = new Mesh(6);
    for(int i = 0; i < 6; i++)
    {
        (*outlineMesh)(5-i) = vector4(cos(i*M_PI/3.0), 0, sin(i*M_PI/3.0));
        outlineMesh->setNormal(5-i, vector4(0, 1, 0));
    }

    mesh = new Mesh(48);
    int around = 1;
    for(int i = 0; i < 12; i++)
    {
        int vertex = 0;
        if(i%3 == 1)
            vertex = around++;
        else if(i%3 == 2)
            vertex = around;
        (*mesh)(11-i) = vector4(cos(vertex*M_PI/3.0), 0, sin(vertex*M_PI/3.0));
        mesh->setNormal(11-i, vector4(0, 1, 0));
    }

    for(int i = 0; i < 6; i++)
    {
        (*mesh)(12+6*i) = vector4(cos(i*M_PI/3.0), 0, sin(i*M_PI/3.0));
        (*mesh)(12+6*i+2) = vector4(cos(i*M_PI/3.0), -5, sin(i*M_PI/3.0));
        (*mesh)(12+6*i+1) = vector4(cos((i+1)*M_PI/3.0), 0, sin((i+1)*M_PI/3.0));

        (*mesh)(12+6*i+3) = vector4(cos(i*M_PI/3.0), -5, sin(i*M_PI/3.0));
        (*mesh)(12+6*i+4) = vector4(cos((i+1)*M_PI/3.0), 0, sin((i+1)*M_PI/3.0));
        (*mesh)(12+6*i+5) = vector4(cos((i+1)*M_PI/3.0), -5, sin((i+1)*M_PI/3.0));

        mesh->setNormal(12+6*i, (*mesh)(12+6*i));
        mesh->setNormal(12+6*i+1, (*mesh)(12+6*i+4));
        mesh->setNormal(12+6*i+2, (*mesh)(12+6*i));
        mesh->setNormal(12+6*i+3, (*mesh)(12+6*i));
        mesh->setNormal(12+6*i+4, (*mesh)(12+6*i+4));
        mesh->setNormal(12+6*i+5, (*mesh)(12+6*i+4));
    }

    for (int i=0; i<48; i++) {
        vector4 p = (*mesh)(i);
        mesh->setTexCoord(i, vector4(p.x, p.z));
    }

    mesh->makeDisplayList(GL_TRIANGLES);
}

/**
 * Renders the cell. float dt is the change in time during
 * the last frame and is used for animation. All the entities
 * on the cell are also rendered.
 */
void Cell::render(float dt)
{
    if (!isVisible())
    {
        return;
    }

    if (isSelectable())
    {
        if (isHighlighted())
        {
            setColor(0, 1, 0);
        } else
        {
            setColor(0, 0.5, 0);
        }
    }
    else
    {
        if (isHighlighted())
        {
            setColor(0.5, 0, 0);
        }
        else
        {
            setColor(1, 1, 1);
        }
    }

    glPushMatrix();
    vector4 p = position;
    glTranslated(p.x, p.y, p.z);

    glPushMatrix();
    glTranslatef(0,0.005,0);
    glColor3d(0,0,0);
    outlineMesh->render(GL_LINE_LOOP);
    glPopMatrix();

    glColor3d(color[0], color[1], color[2]);
    if (tex) {
        glEnable(GL_TEXTURE_2D);
        tex->bind();
    }
    mesh->render(GL_TRIANGLES);
    if (tex) {
        glDisable(GL_TEXTURE_2D);
    }

    //render all the entities on the cell
    for (std::list<Entity*>::iterator i=entities.begin();
         i != entities.end(); i++)
    {
        (*i)->render(dt);
    }

    glPopMatrix();
}

/**
 * Checks if the ray r from point src intersects the
 * top surface of the cell.
 * dist is a value returned to the caller that stores
 * the distance from the screen.
 */
bool Cell::intersect(vector4 r, vector4 src, vectype& dist)
{
    //translate coordinates
    src.y -= position.y;
    //look for intersection between select and plane y = 0
    r = src - (src.y/r.y)*r;

    for(int i = 0; i < 6; i++)
    {
	if(!isccw(i, r))
	    return false;
    }

    dist = (r - src).length();

    return true;
}

/**
 * The counter-clockwise function. It is used for intersection
 * calculation. Returns true if the points p, outlineMesh(idx) and
 * outlineMesh(idx+1), in that order, are counterclockwise with respect to
 * the xz-plane.
 */
bool Cell::isccw(int idx, vector4 p)
{
    vector4 d2 = position + (*outlineMesh)(idx) - p;  //relative coordinates
    vector4 d1 = position + (*outlineMesh)((idx+1)%6) - p;

    return (d2.z*d1.x >= d1.z*d2.x);
}

/**
 * Returns the position of the cell.
 */
vector4 Cell::getPosition()
{
    return position;
}

/**
 * Returns the selectable state of the cell.
 */
bool Cell::isSelectable()
{
    return selectable;
}

/**
 * Sets the selectable state of the cell.
 */
void Cell::setSelectable(bool sel)
{
    selectable = sel;
}

/**
 * Returns the highlighted state of the cell.
 */
bool Cell::isHighlighted()
{
    return highlighted;
}

/**
 * Sets the highlighted state of the cell.
 */
void Cell::setHighlighted(bool hl)
{
    highlighted = hl;
}

/**
 * Returns whether the cell is visible or not.
 */
bool Cell::isVisible()
{
    return visible;
}

/**
 * Set whether the cell is visible or not.
 */
void Cell::setVisible(bool vis)
{
    visible = vis;
}

/**
 * Returns the indices of the position of the cell in the maze grid.
 */
void Cell::getMazePosition(int &i, int &j)
{
    i = posi;
    j = posj;
}

/**
 * Sets the indices of the position of the cell in the maze grid.
 */
void Cell::setMazePosition(int i, int j)
{
    posi = i;
    posj = j;
}

/**
 * Returns true if the cell has a player on it.
 */
bool Cell::hasPlayer()
{
    return bHasPlayer;
}

/**
 * Sets the state of the cell having the player.
 */
void Cell::setHasPlayer(bool b)
{
    bHasPlayer = b;
}

/**
 * Sets whether this cell has a wall or not.
 */
void Cell::setWall(bool w)
{
    if(w == isWall)
	return; //nothing to do

    if(w)
	wallHeight = rand()%MAX_WALL_HEIGHT+1;

    position.y += w ? wallHeight : -wallHeight;

    isWall = w;
}

/**
 * This is called if a grenade hits a wall. It decreases the size of the wall by
 * 1 unit.
 */
void Cell::hitWall()
{
    wallHeight--;
    position.y -= 1;
    if(wallHeight == 0)
	isWall = false;
}

/**
 * Returns whether this cell has a wall or not.
 */
bool Cell::getWall()
{
    return isWall;
}

/**
 * Set the texture to use for the cell.
 */
void Cell::setTexture(Texture *tex)
{
    this->tex = tex;
}

/**
 * Returns a list of entities on the cell.
 */
std::list<Entity*> Cell::getEntities()
{
    return entities;
}
