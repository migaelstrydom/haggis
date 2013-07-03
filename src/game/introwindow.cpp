/************************************************************************
 *
 * introwindow.cpp
 * Introduction window class implementation
 *
 ************************************************************************/

#include "introwindow.h"

/**
 * Constructor.
 */
IntroWindow::IntroWindow()
{
    //load images
    img = new StaticImage(Texture::load("images/intro/intro.png"));
    start = new Button(Texture::load("images/intro/start.png"));
    exit = new Button(Texture::load("images/intro/exit.png"));

    //add children
    addChild(img);
    addChild(start);
    addChild(exit);
}

/**
 * Destructor.
 */
IntroWindow::~IntroWindow()
{
    //delete all the objects used
    delete img;
    delete start;
    delete exit;
}

/**
 * Sets the size of the window.
 */
void IntroWindow::setSize(vector4 size)
{
    //call the superclass
    Window::setSize(size);

    //set the size of the image
    img->setSize(size);

    //these values work nicely
    float x = 0.1 * size.x;
    float y = 0.35 * size.y;
    float h = 0.1 * size.y;
    float w = start->getTexture()->getAspectRatio() * h;

    //position the buttons so they look pretty
    start->setPosition(vector4(x, y+h));
    exit->setPosition(vector4(x, y));

    start->setSize(vector4(w, h));
    exit->setSize(vector4(w, h));
}

/**
 * Returns whether the start button was pressed.
 */
bool IntroWindow::shouldStart()
{
    return start->isPressed();
}

/**
 * Returns whether the exit button was pressed.
 */
bool IntroWindow::shouldExit()
{
    return exit->isPressed();
}
