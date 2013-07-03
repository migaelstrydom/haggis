/************************************************************************
 *
 * maze.cpp
 * Maze class implementation
 *
 ************************************************************************/

#include "maze.h"
#include "level.h"
#include "item.h"
#include "application.h"  //for app_error

#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>   //for loading from file
#include <iostream>
#include <cmath>

#define PHIVEL 5.0
#define THETAVEL 5.0
#define RVEL 20.0

/**
 * Constructor. Initialises every single variable.
 */
Maze::Maze()
    : Window(), width(-1), height(-1), heroCell(NULL), 
      haggisCell(NULL), bLoaded(false), 
      bLeftClicked(false), rightDown(false), 
      midDown(false), level(NULL)
{
    setProjection(PERSPECTIVE);
    zoomIn = false;
    zoomOut = false;
    selectionEnabled = false;
    selectedCell = NULL;
}

/**
 * Destructor.
 */
Maze::~Maze()
{
    unload();
}

/**
 * Loads the maze from file.
 */
void Maze::load(std::string fn)
{
    if(bLoaded)   //if something already loaded
        unload();   //free it

    bLoaded = true;   //set loaded flag

    Texture *grass = Texture::load("images/tex/grass.png");
    Texture *dirt = Texture::load("images/tex/dirt.png");

    std::ifstream fin(fn.c_str());  //open file containing level

    if(!fin)   //make sure a valid filename was sent
        throw app_error(std::string("Unable to open file: ") + fn);

    fin >> width;  //read in width
    fin >> height;  //read in height

    //check that width and height are not too big or small
    if((width < 1) || (width > 1000) || (height < 1) || (height > 1000))
    {
	throw app_error(fn + std::string(" contains invalid data."));
    }

    //allocate memory for cells
    cells = new Cell*[height];
    for (int i=0; i<height; i++)
    {
        cells[i] = new Cell[width];
    }

    double sinp3 = sin(M_PI/3); //to avoid calculating this repeatedly

    //set cell positions
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int ctype;     //the cell type
            fin >> ctype;  //read the cell type from file

            cells[i][j].setMazePosition(i, j);
            vector4 pos = vector4(1.5*i - 0.75*width,
                                  0,
                                  (2*j+(i%2))*sinp3 - sinp3*height);

            // calculate a height offset
            float rr = pos.squaredLength();
            pos.y = 10.0*exp(-rr/100.0);
            cells[i][j].setPosition(pos);


            findCellNeighbours(&cells[i][j]);
            if (ctype == 0)
            {
                // there is no cell here
                cells[i][j].setVisible(false);
            }
            else if (ctype == 2)
            {
                //if this cell is a wall
                cells[i][j].setWall(true);
            }
            else if (ctype == 3)
            {
                // this is the starting cell of the hero
                heroCell = &cells[i][j];
                cells[i][j].setHasPlayer(true);
            }
            else if(ctype == 4)
            {
                //this is the starting cell of the haggis
                haggisCell = &cells[i][j];
                cells[i][j].setHasPlayer(true);
            }
            else if(ctype == 5)
	    {
                //this is a health item
                Item *nitem = new Item(level);
                nitem->setCell(&cells[i][j]);
                nitem->setType(Item::HEALTH);
	    }
            else if(ctype == 6)
	    {
                //this is a energy item
                Item *nitem = new Item(level);
                nitem->setCell(&cells[i][j]);
                nitem->setType(Item::ENERGY);
            }
            else if(ctype == 7)
	    {
                //this is a grenade item
                Item *nitem = new Item(level);
                nitem->setCell(&cells[i][j]);
                nitem->setType(Item::GRENADE);
            }
	    else if(ctype == 8)
	    {
		//this is a trap
		Item *nitem = new Item(level);
                nitem->setCell(&cells[i][j]);
                nitem->setType(Item::TRAP);
	    }
	    else  if(ctype != 1)//otherwise the data is invalid
	    {
		throw app_error(fn + std::string(" contains invalid data."));
	    }

	    //set the texture based on whether the cell is a wall or not
            if (cells[i][j].getWall()) {
                cells[i][j].setTexture(dirt);
            } else {
                cells[i][j].setTexture(grass);
            }
        }
    }
}

/**
 * Destructor. Frees all the memory the maze has used.
 */
void Maze::unload()
{
    if(!bLoaded)
        return;    //do not free memory if there is nothing to free

    //free each of the rows of cells
    for (int i=0; i<height; i++)
    {
        delete[] cells[i];
    }

    //free the array of pointers
    delete [] cells;

    bLoaded = false;
}

/**
 * Returns the cell the hero initially occupies.
 */
Cell *Maze::getHeroCell()
{
    return heroCell;
}

/**
 * Returns the cell the haggis initially occupies.
 */
Cell *Maze::getHaggisCell()
{
    return haggisCell;
}

void Maze::setLevel(Level *level)
{
    this->level = level;
}

/**
 * Returns the level, so that events can be sent to it.
 */
Level* Maze::getLevel()
{
    return level;
}

/**
 * Handle key events. These are used to zoom in and out.
 */
void Maze::handleKeyEvent(KeyEvent event)
{
    if (event.getKey() == '=') {
        zoomIn = (event.getState() == KeyEvent::PRESSED);
    }
    if (event.getKey() == '-') {
        zoomOut = (event.getState() == KeyEvent::PRESSED);
    }
}

/**
 * Set whether user is allowed to select cells or not.
 */
void Maze::setCellSelectionEnable(bool enabled)
{
    if (selectionEnabled != enabled) {
        selectedCell = NULL;
    }
    selectionEnabled = enabled;
}

/**
 * Returns true if cell selection is enabled.
 */
bool Maze::isCellSelectionEnabled()
{
    return selectionEnabled;
}

/**
 * Returns the last cell selected since cell selection was last enabled.
 * This may be NULL if no cell has been selected yet or if cell selection
 * is disabled.
 */
Cell *Maze::getSelection()
{
    return selectedCell;
}
/**
 * Returns the maze width.
 */
int Maze::getWidth()
{
    return width;
}

/**
 * Returns the maze height.
 */
int Maze::getHeight()
{
    return height;
}

/**
 * Returns the cell at position (i, j) where i is the row and j is the
 * column.
 */
Cell *Maze::getCell(int i, int j)
{
    assert((i >= 0) && (i < height));
    assert((j >= 0) && (j < width));
    return &cells[i][j];
}

/**
 * Renders the maze, including everything it contains. It animates and
 * positions the camera (point of view), depending on what keys have been pressed.
 * The cell over which the cursor is hovering is calculated and highlighted if necessary.
 */
void Maze::draw(float dt)
{
    //variables needed to store information for the upcoming projections
    double mvmat[16], projmat[16];
    int viewport[4];
    vector4 front, select;

    glDisable(GL_TEXTURE_2D);

    glGetIntegerv(GL_VIEWPORT, viewport);

    //check if the camera should be rotated
    if (rightDown) {
        vector4 d = rightOrigin - getMousePosition();
        camera.set_phi(rightPhi + PHIVEL*d.x);
        camera.set_theta(rightTheta + THETAVEL*d.y);

        rightPhi = camera.get_phi();
        rightTheta = camera.get_theta();
        rightOrigin = getMousePosition();
    }

    //zoom camera if necessary
    if (zoomIn) {
        camera.ZoomIn();
    }
    if (zoomOut) {
        camera.ZoomOut();
    }
    if (midDown) {
        float z = getMousePosition().y - midOrigin.y;
        camera.set_r(midZoom + RVEL*z);
    }

    //update the camera
    camera.update(dt);

    //set the light at the camera's position
    float lightpos[] = {0, 1, 0, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
    float lightcol[] = {0.5, 0.5, 0.5, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightcol);
    //this is the global light
    glEnable(GL_LIGHT1);

    vector4 focus = level->getHero()->getPosition() +
        level->getHero()->getCell()->getPosition();
    camera.set_focus(focus);
    camera.positionCamera();

    glColor3f(1,1,1);
 
    //get the necessary matrices to perform an unproject
    glGetDoublev(GL_PROJECTION_MATRIX, projmat);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmat);

    vector4 mp = (getMousePosition() + getAbsolutePosition()) * viewport[3];

    //unproject a position close to the screen
    gluUnProject(mp.x, mp.y, 0, mvmat, projmat, viewport,
                 &front.x, &front.y, &front.z);

    //unproject a position far from the screen
    gluUnProject(mp.x, mp.y, 1, mvmat, projmat, viewport,
                 &select.x, &select.y, &select.z);

    //make select a directed ray from the screen to the back of the
    //geometry space.
    select -= front;


    Cell *intersectedCell = NULL;

    if (isCellSelectionEnabled()) {

        // test all cells for intersection
        vectype closestCell = 600;      //the max viewing distance
        for(int i = 0; i < height; i++) {
            for (int j=0; j < width; j++) {
                vectype dist;
                if(cells[i][j].intersect(select, front, dist)) {
                    if(dist < closestCell) {
                        closestCell = dist;
                        intersectedCell = &cells[i][j];
                    }
                }
            }
        }

        // if the mouse has been clicked, possibly select the cell
        if ((intersectedCell != NULL) && bLeftClicked) {
            if (intersectedCell->isSelectable()) {
                selectedCell = intersectedCell;
                bLeftClicked = false;
            }
        }
    }

    glEnable(GL_LIGHTING);

    //render cells
    for(int i = 0; i < height; i++) {
        for (int j=0; j < width; j++) {
            //if the mouse is over the cell, change its color.
            cells[i][j].setHighlighted(intersectedCell == &cells[i][j]);

            //if selection is not enabled, make all cells unselectable
            if (!isCellSelectionEnabled()) {
                cells[i][j].setSelectable(false);
            }

            //render the cell
            cells[i][j].render(dt);
        }
    }

    glDisable(GL_LIGHTING);
    bLeftClicked = false;
}

/**
 * This is called when a button is pressed. It checks to see which one
 * was pressed and does something about it.
 */
bool Maze::onHandleButtonEvent(ButtonEvent event)
{
    //was the left button clicked?
    bLeftClicked = bLeftClicked ||
        ((event.getState() == ButtonEvent::RELEASED) &&
         (event.getButton() == ButtonEvent::LEFT));

    //check if the right button was clicked
    if (event.getButton() == ButtonEvent::RIGHT) {
        if (event.getState() == ButtonEvent::PRESSED) {
            rightOrigin = event.getPosition();
            rightPhi = camera.get_phi();
            rightTheta = camera.get_theta();
            rightDown = true;
        } else {
            rightDown = false;
        }
    }

    //check if the middle button was clicked
    if (event.getButton() == ButtonEvent::MIDDLE) {
        if (event.getState() == ButtonEvent::PRESSED) {
            midOrigin = event.getPosition();
            midZoom = camera.get_r();
            midDown = true;
        } else {
            midDown = false;
        }
    }

    return true;
}

/**
 * On initialization of the maze, each cell knows what its neighbours
 * are, to make path-finding in the maze easier.
 */
void Maze::findCellNeighbours(Cell* cell)
{
    int pi, pj;
    cell->getMazePosition(pi, pj);

    // check all adjacent cells
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if ((i == 1) && (j == 1))
            {
                // the current cell is not its own neighbour
                continue;
            }

            // adjacent cell coordinates
            int ni = pi + i-1;
            int nj = pj + j-1;

            if ((ni < 0) || (ni >= getHeight()) ||
                (nj < 0) || (nj >= getWidth()))
            {
                // this goes off the edge of the maze
                continue;
            }

            if (pi % 2 == 0)
            {
                // even row
                if ((i != 1) && (j == 2))
                {
                    continue;
                }
            }
            else
            {
                // odd row
                if ((i != 1) && (j == 0))
                {
                    continue;
                }
            }

            //ni, nj is a neighbour
            cell->neighbours.push_back(getCell(ni, nj));
        }
    }
}
