/************************************************************************
 *
 * levelend.h
 * LevelEnd class implementation
 *
 ************************************************************************/

#include "levelend.h"

#include <string>

/**
 * Constructor.
 */
LevelEnd::LevelEnd()
{
    //load images
    std::string prefix = "images/lend/";

    imgwon = new StaticImage(Texture::load(prefix + "win.png"));
    imglost = new StaticImage(Texture::load(prefix + "lose.png"));

    btnretry = new Button(Texture::load(prefix + "retry.png"));
    btncont = new Button(Texture::load(prefix + "continue.png"));

    exit = new Button(Texture::load(prefix + "exit.png"));

    //add children (buttons)
    addChild(imgwon);
    addChild(imglost);
    addChild(btnretry);
    addChild(btncont);
    addChild(exit);

    setWinner(true);
}

/**
 * Destructor. Free all memory used.
 */
LevelEnd::~LevelEnd()
{
    delete imgwon;
    delete imglost;
    delete btnretry;
    delete btncont;
    delete exit;
}

/**
 * Set the window size.
 */
void LevelEnd::setSize(vector4 size)
{
    //call superclass
    Window::setSize(size);

    //choose position so that layout looks good
    float h = 0.1 * getSize().y;
    float w = btnretry->getTexture()->getAspectRatio() * h;

    vector4 pos = getSize()/4;
    pos.y += h;

    //set position
    imgwon->setSize(getSize()/2);
    imgwon->setPosition(pos);
    imglost->setSize(imgwon->getSize());
    imglost->setPosition(imgwon->getPosition());

    //choose position
    pos = imgwon->getPosition();
    pos.y -= h;
    //set position
    btnretry->setPosition(pos);
    btnretry->setSize(vector4(w, h));
    btncont->setPosition(btnretry->getPosition());
    btncont->setSize(btnretry->getSize());

    //choose position
    pos.y -= h;
    //set position
    exit->setPosition(pos);
    exit->setSize(vector4(w, h));
}

/**
 * Sets the winner of the level. If won is true, the hero won. If won
 * is false, the haggis won.
 */
void LevelEnd::setWinner(bool won)
{
    this->won = won;

    // have to cast to Window so that the right setEnabled() method is called
    ((Window*) btncont)->setEnabled(won);
    ((Window*) btnretry)->setEnabled(!won);

    imgwon->setEnabled(won);
    imglost->setEnabled(!won);
}

/**
 * Returns true if the user has requested to retry the level.
 */
bool LevelEnd::shouldRetry()
{
    if (won) {
        return false;
    } else {
        return btnretry->isPressed();
    }
}

/**
 * Returns true if the user has requested to continue to the next level.
 */
bool LevelEnd::shouldContinue()
{
    if (!won) {
        return false;
    } else {
        return btncont->isPressed();
    }
}

/**
 * Returns true if the user has requested to exit the game.
 */
bool LevelEnd::shouldExit()
{
    return exit->isPressed();
}

/**
 * Draw the screen.
 */
void LevelEnd::draw(float dt)
{
    Window::draw(dt);
}
