/************************************************************************
 *
 * creditswindow.cpp
 * Credits window class implementation
 *
 ************************************************************************/

#include "creditswindow.h"

/**
 * Constructor.
 */
CreditsWindow::CreditsWindow()
{
    img = new StaticImage(Texture::load("images/credits/credits.png"));
    exit = new Button(Texture::load("images/credits/exit.png"));

    addChild(img);
    addChild(exit);
}

/**
 * Destructor.
 */
CreditsWindow::~CreditsWindow()
{
    delete img;
    delete exit;
}

/**
 * Sets the size of the window.
 */
void CreditsWindow::setSize(vector4 size)
{
    Window::setSize(size);

    img->setSize(size);

    // these factors were calculated by trial and error
    float x = 0.1 * size.x;
    float y = 0.45 * size.y;
    float h = 0.1 * size.y;
    float w = exit->getTexture()->getAspectRatio() * h;

    exit->setPosition(vector4(x, y));
    exit->setSize(vector4(w, h));
}

/**
 * Returns true if the user has clicked the exit button.
 */
bool CreditsWindow::shouldExit()
{
    return exit->isPressed();
}
