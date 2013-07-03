/************************************************************************
 *
 * levelbegin.cpp
 * Level begin window class implementation
 *
 ************************************************************************/

#include "levelbegin.h"
#include "vector4.h"
#include "button.h"
#include "level.h"
#include "texture.h"

#include <GL/gl.h>

#include <iostream>

/**
 * Constructor.
 */
LevelBegin::LevelBegin()
{
    //load images
    img = new StaticImage(Texture::load("images/lbegin/msg.png"));
    btnstart = new Button(Texture::load("images/lbegin/start.png"));
    btnexit = new Button(Texture::load("images/lbegin/exit.png"));

    //add children
    addChild(img);
    addChild(btnstart);
    addChild(btnexit);

    setSize(getSize());
}
/**
 * Destructor.
 */
LevelBegin::~LevelBegin()
{
    delete img;
    delete btnstart;
    delete btnexit;
}

/**
 * Set the window size.
 */
void LevelBegin::setSize(vector4 size)
{
    //call superclass
    Window::setSize(size);

    float h = 0.1 * getSize().y;
    float w = btnstart->getTexture()->getAspectRatio() * h;

    //choose positions that will look pretty
    vector4 pos = getSize()/4;
    pos.y += h;

    //set the size & position
    img->setSize(getSize()/2);
    img->setPosition(pos);

    //etc.
    pos = img->getPosition();
    pos.y -= h;
    btnstart->setPosition(pos);
    btnstart->setSize(vector4(w, h));

    pos.y -= h;
    btnexit->setPosition(pos);
    btnexit->setSize(vector4(w, h));
}

/**
 * Returns true if the user has requested the maze to start.
 */
bool LevelBegin::shouldStart()
{
    return btnstart->isPressed();
}

/**
 * Returns true if the user has requested the game to exit.
 */
bool LevelBegin::shouldExit()
{
    return btnexit->isPressed();
}
