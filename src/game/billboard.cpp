/************************************************************************
 *
 * billboard.cpp
 * BillBoard class implementation
 *
 ************************************************************************/

#include "billboard.h"

#include <GL/gl.h>

/**
 * Constructor. The texture does not belong to the billboard and must
 * be kept valid while the billboard is used. The texture may be NULL.
 */
BillBoard::BillBoard(Texture *tex)
    : tex(tex)
{
    h = 0.5;
}
/**
 * Destructor.
 */
BillBoard::~BillBoard()
{
    //nothing to destruct.
}

/**
 * Render the billboard.
 */
void BillBoard::render(float dt)
{
    if (!isVisible()) {
        return;
    }
    if (!tex) {
        return;
    }

    glPushMatrix();
    glTranslatef(getPosition().x, getPosition().y, getPosition().z);
    glRotatef(getRotation()*180.0/M_PI, 0, 1, 0);

    //get the modelview matrix
    float matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    //Get the correct vectors for billboarding
    vector4 right(matrix[0], matrix[4], matrix[8]);
    vector4 up(matrix[1], matrix[5], matrix[9]);

    //Scale the up and right vectors to the right height and aspect ratio
    up = up * h;
    right = right * h * tex->getAspectRatio();

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    //Bind the texture
    tex->bind();

    //this will only draw visible pixels
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);

    glColor4f(1,1,1,1);

    //Draw particles
    glBegin(GL_POLYGON);

    //vector4 normal = right % up;
    //glNormal3d(normal.x, normal.y, normal.z);

    vector4 calc = (right + up);
    glTexCoord2f(1.0, 0.0);
    glVertex3d(calc.x, calc.y, calc.z);

    calc = (right - up);
    glTexCoord2f(1.0, 1.0);
    glVertex3d(calc.x, calc.y, calc.z);

    calc = (-right - up);
    glTexCoord2f(0.0, 1.0);
    glVertex3d(calc.x, calc.y, calc.z);

    calc = (up - right);
    glTexCoord2f(0.0, 0.0);
    glVertex3d(calc.x, calc.y, calc.z);

    glEnd();

    //return everything to the way it was
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);

    glPopMatrix();
}
