/************************************************************************
 *
 * overlay.cpp
 * Overlay class implementation
 *
 ************************************************************************/

#include "overlay.h"
#include "level.h"
#include "waitaction.h"
#include "walkaction.h"
#include "grenadeaction.h"
#include "jumpaction.h"
#include "psychicaction.h"

#include <iostream>

/**
 * Constructor.
 */
Overlay::Overlay()
{
    // Create action buttons

    actions.push_back(new Button(Texture::load("images/overlay/waitaction.png")));
    actions.push_back(new Button(Texture::load("images/overlay/stepaction.png")));
    actions.push_back(new Button(Texture::load("images/overlay/jumpaction.png")));
    actions.push_back(new Button(Texture::load("images/overlay/grenadeaction.png")));
    actions.push_back(new Button(Texture::load("images/overlay/psychicaction.png")));

    for (std::vector<Button*>::iterator i=actions.begin(); i != actions.end();
         i++)
    {
        addChild(*i);
    }

    // Create the exit button

    btnexit = new Button(Texture::load("images/overlay/exitaction.png"));
    addChild(btnexit);

    // Create turn status labels

    heroturn = new StaticImage(Texture::load("images/overlay/playerturn.png"));
    addChild(heroturn);

    haggisturn = new StaticImage(Texture::load("images/overlay/haggisturn.png"));
    addChild(haggisturn);

    actionturn = new StaticImage(Texture::load("images/overlay/actionturn.png"));
    addChild(actionturn);

    // Create attribute labels

    labels.push_back(new StaticImage(Texture::load("images/overlay/health.png")));
    labels.push_back(new StaticImage(Texture::load("images/overlay/energy.png")));
    labels.push_back(new StaticImage(Texture::load("images/overlay/ammo.png")));

    for (std::vector<StaticImage*>::iterator i=labels.begin(); i!=labels.end();
         i++) {
        addChild(*i);
    }

    // Create progress bars

    for (int i=0; i<3; i++) {
        bars.push_back(new ProgressBar());
        addChild(bars[i]);
    }

    // initialize

    level = NULL;
    maze = NULL;
    state = NORMAL;
}

/**
 * Destructor.
 */
Overlay::~Overlay()
{
    // destroy actions buttons
    for (std::vector<Button*>::iterator i=actions.begin(); i != actions.end();
         i++)
    {
        delete *i;
    }

    // destroy attribute labels
    for (int i=0; i<(int)labels.size(); i++) {
        delete labels[i];
    }

    // destroy progress bars
    for (int i=0; i<(int)bars.size(); i++) {
        delete bars[i];
    }

    // destroy turn status labels
    delete heroturn;
    delete haggisturn;
    delete actionturn;

    // destroy the exit button
    delete btnexit;
}

/**
 * Set the level to pass actions to.
 */
void Overlay::setLevel(Level *level)
{
    this->level = level;
}

/**
 * Set the maze.
 */
void Overlay::setMaze(Maze *maze)
{
    this->maze = maze;
}

/**
 * Set the size of the window. This resizes and repositions all the
 * user interface elements.
 */
void Overlay::setSize(vector4 size)
{
    Window::setSize(size);

    float w, h, x, pad;

    // pad is a padding value for spacing between elements and other elements
    // or edges of the screen
    pad = 0.01 * getSize().y;

    // position the action buttons along the bottom-left of the screen

    w = 0.1 * getSize().y;
    x = pad;
    for (std::vector<Button*>::iterator i=actions.begin(); i != actions.end();
         i++)
    {
        Button *b = *i;
        b->setSize(vector4(w, w));
        b->setPosition(vector4(x, pad));
        x += w;
    }

    // position the exit button in the bottom-right corner

    btnexit->setSize(vector4(w, w));
    btnexit->setPosition(vector4(getSize().x-w-pad, pad));

    // position the turn labels in the top-left

    h = 0.05 * getSize().y;
    w = heroturn->getTexture()->getAspectRatio() * h;
    heroturn->setSize(vector4(w, h));
    w = haggisturn->getTexture()->getAspectRatio() * h;
    haggisturn->setSize(vector4(w, h));
    w = actionturn->getTexture()->getAspectRatio() * h;
    actionturn->setSize(vector4(w, h));

    heroturn->setPosition(vector4(pad, getSize().y-h-pad));
    haggisturn->setPosition(heroturn->getPosition());
    actionturn->setPosition(heroturn->getPosition());

    // setup the attribute labels and progress bars along the top

    // first psoition the labels
    vector4 pos = heroturn->getPosition();
    pos.x += heroturn->getSize().x;
    vector4 lsize = vector4(2*h, h);
    w = 2*lsize.x + 4*pad;

    for (int i=0; i<(int)labels.size(); i++) {
        labels[i]->setPosition(pos);
        labels[i]->setSize(lsize);
        pos.x += w;
    }

    // then the progress bars
    pos = labels[0]->getPosition();
    pos.x += labels[0]->getSize().x + pad;
    pos.y += h/4;
    lsize = vector4(2*h, h/2);

    for (int i=0; i<(int)bars.size(); i++) {
        bars[i]->setPosition(pos);
        bars[i]->setSize(lsize);
        pos.x += w;
    }
}

/**
 * Returns true if the user has pressed the exit button.
 */
bool Overlay::shouldExit()
{
    return btnexit->isPressed();
}

/**
 * Draw the overlay and processes button events.
 */
void Overlay::draw(float dt)
{
    // update the current turn label

    Level::turn t = level->getCurrentTurn();

    bool herot = (t == Level::HERO_TURN);
    bool haggist = (t == Level::HAGGIS_TURN);
    bool actiont = (t == Level::ACTION_TURN);

    heroturn->setEnabled(herot);
    haggisturn->setEnabled(haggist);
    actionturn->setEnabled(actiont);

    // update the progress bars

    Hero *h = level->getHero();
    bars[0]->setProgress((float) h->getHealth() / (float) h->getMaxStat());
    bars[1]->setProgress((float) h->getEnergy() / (float) h->getMaxStat());
    bars[2]->setProgress((float) h->getAmmo() / (float) h->getMaxStat());

    // update the action buttons

    actions[0]->setEnabled(WaitAction::canWait(h));
    actions[1]->setEnabled(WalkAction::canWalk(h));
    actions[2]->setEnabled(JumpAction::canJump(h));
    actions[3]->setEnabled(GrenadeAction::canThrow(h));
    actions[4]->setEnabled(PsychicAction::canPsychic(h));

    // do something depending on the state
    // check for action button presses
    // if it is the haggis' turn, do nothing
    if(!haggist)
    {
        for (int i=0; i<(int)actions.size(); i++)
        {
            if (actions[i]->isPressed())
            {
                actions[i]->reset();  //set pressed = false
                //only handle button if in right state
                if(state == NORMAL)
                {
                    handleButton(i);
                }
                else if(action == i)
                {
                    action = -1;
                    handleCellSelection(); //to return state to normal
                }
            }
        }
    }

    if ((state == WAITING_FOR_CELL) && maze)
    {
        // check if a cell has been selected
        if (maze->getSelection())
        {
            handleCellSelection();
        }
    }
}

/**
 * Looks at which button has been pressed and determines what
 * needs to be done next. Called from draw.
 */
void Overlay::handleButton(int n)
{
    assert(state == NORMAL);
    action = n;
    switch(n)
    {
    case 0:
        {
            WaitAction *a = new WaitAction(level->getHero());
            level->notifyHeroAction(a);
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        getCellSelection(n);
        break;
    };
}

/**
 * Setup the maze to allow the user to select a cell. The state is
 * changed to WAITING_FOR_CELL. The current action is changed to act.
 */
void Overlay::getCellSelection(int act)
{
    if (!maze)
    {
        return;
    }

    if (act == 1)
    {
        WalkAction::markSelectable(level->getHero(), maze);
    }
    else if(act == 2)
    {
        JumpAction::markSelectable(level->getHero(), maze);
    }
    else if(act == 3)
    {
        GrenadeAction::markSelectable(level->getHero(), maze);
    }
    else if(act == 4) {
        PsychicAction::markSelectable(level->getHero(), maze);
    }

    maze->setCellSelectionEnable(true);
    state = WAITING_FOR_CELL;
    actions[act]->setToggle(true);
}

/**
 * Handle the selection of a maze cell.
 */
void Overlay::handleCellSelection()
{
    if (action == 1) //walk
    {
        WalkAction *a = new WalkAction(level->getHero(), maze->getSelection());
        level->notifyHeroAction(a);
    }
    else if(action == 2) // jump
    {
        JumpAction *a = new JumpAction(level->getHero(),
                maze->getSelection());
        level->notifyHeroAction(a);
    }
    else if(action == 3) //grenade
    {
        GrenadeAction *a = new GrenadeAction(level->getHero(),
                                             level->getHaggis(),
                                             level->getHero()->getCell(),
                                             maze->getSelection());
        level->notifyHeroAction(a);
    }
    else if(action == 4)
    { // psychic
        PsychicAction *a = new PsychicAction(level->getHero(),
                                             maze->getSelection());
        level->notifyHeroAction(a);
    }

    state = NORMAL;
    maze->setCellSelectionEnable(false);

    for (int i=0; i<(int)actions.size(); i++)
    {
        actions[i]->setToggle(false);
    }
}
