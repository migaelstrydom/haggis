/************************************************************************
 *
 * hero.cpp
 * Hero class implementation
 *
  ************************************************************************/

#include "hero.h"

#include <GL/gl.h>

#include <cmath>

#include <iostream>

/**
 * Constructor. Initialises the hero. Creates the mesh for the hero.
 */
Hero::Hero()
{
    setMesh(Mesh::makeCube(0.5));
    t = 0;
}

/**
 * Destructor.
 */
Hero::~Hero()
{
    //nothing to destruct.
}

/**
 * Renders the hero. float dt is the change in time since the last frame.
 * It is used to update the animation of the hero.
 */
void Hero::render(float dt)
{
    //update animation.
    t += dt;
    vector4 disp = vector4(0, 0.1*sin(5*t), 0);
    vector4 rest = getPosition();
    setPosition(rest + disp);

    //set up the light of the hero.
    float lightpos[] = {rest.x+disp.x, rest.y+disp.y, rest.z+disp.z, 1};
    glLightfv(GL_LIGHT2, GL_POSITION, lightpos);
    float lightcol[] = {1.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightcol);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5);
    glEnable(GL_LIGHT2);

    //draw the hero. This is done in the base class Player.
    glColor3f(1,0,0);
    Player::render(dt);

    setPosition(rest);
}
