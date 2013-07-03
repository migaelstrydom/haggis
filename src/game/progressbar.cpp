/************************************************************************
 *
 * progressbar.cpp
 * Progress bar class implementation
 *
 ************************************************************************/

#include "progressbar.h"

#include <GL/gl.h>
#include <cassert>

/**
 * Constructor. Initially, the progress is set to zero.
 */
ProgressBar::ProgressBar()
{
    progress = 0.0;
}

/**
 * Destructor.
 */
ProgressBar::~ProgressBar()
{
    //nothing to destruct
}

/**
 * Set the progress. p should be in the range [0, 1].
 */
void ProgressBar::setProgress(float p)
{
    assert((p >= 0) && (p <= 1));
    progress = p;
}

/**
 * Draw the bar.
 */
void ProgressBar::draw(float dt)
{
    //disable textures
    glDisable(GL_TEXTURE_2D);

    float w = getSize().x;

    // fill

    glColor3f(0, 1, 0);

    glBegin(GL_QUADS); //begin drawing
    glVertex2f(0, 0);
    glVertex2f(w*progress, 0);
    glVertex2f(w*progress, getSize().y);
    glVertex2f(0, getSize().y);
    glEnd(); //end drawing

    // outline

    glPolygonMode(GL_FRONT, GL_LINE);
    glColor3f(0, 0, 0);

    glBegin(GL_QUADS);  //being drawing
    glVertex2f(0, 0);
    glVertex2f(w, 0);
    glVertex2f(w, getSize().y);
    glVertex2f(0, getSize().y);
    glEnd(); //end drawing

    glPolygonMode(GL_FRONT, GL_FILL);  //reset
}
