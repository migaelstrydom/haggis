/************************************************************************
 *
 * mesh.cpp
 * Mesh class implementation
 *
  ************************************************************************/

#include "mesh.h"
#include <GL/gl.h>

/**
 * Constructor. Accepts the number of points.
 */
Mesh::Mesh(int nump)
    : isDispList(false), numPoints(nump)
{
    points = new vector4[nump];
    normals = new vector4[nump];
    texcoords = new vector4[nump];
}

/**
 * Destructor. Destructs things.
 */
Mesh::~Mesh()
{
    //get rid of all the points & normals & texture coordinates used.
    delete[] points;
    delete[] normals;
    delete[] texcoords;
}

/**
 * Turn into an OpenGL display list to render faster.
 */
void Mesh::makeDisplayList(int beginType)
{
    //generate new disp list
    dList = glGenLists(1);

    //start the list in compile mode
    glNewList(dList, GL_COMPILE);

    //begin drawing
    glBegin(beginType);

    //go through all points
    for(int i = 0; i < numPoints; i++)
    {
        glNormal3d(normals[i].x, normals[i].y, normals[i].z);
        glTexCoord2d(texcoords[i].x, texcoords[i].y);
        glVertex3d(points[i].x, points[i].y, points[i].z);
    }

    //end drawing
    glEnd();

    //end the list
    glEndList();

    //now its a display list
    isDispList = true;
}

/**
 * Renders the vertices of the mesh in order.
 * beginType is the argument passed to glBegin()
 */
void Mesh::render(int beginType)
{
    if(isDispList)   //if it is precompiled
    {
	glCallList(dList);
	return;
    }

    //begin drawing
    glBegin(beginType);

    //go through each point
    for(int i = 0; i < numPoints; i++)
    {
        glNormal3d(normals[i].x, normals[i].y, normals[i].z);
        glTexCoord2d(texcoords[i].x, texcoords[i].y);
        glVertex3d(points[i].x, points[i].y, points[i].z);
    }
    
    //end drawing
    glEnd();
}

/**
 * Sets the normal for a given point idx to n
 */
void Mesh::setNormal(int idx, vector4 n)
{
    assert((idx >= 0) && (idx < numPoints));
    normals[idx] = n;
}

/**
 * Sets the texture coordinate for a given point idx to n.
 */
void Mesh::setTexCoord(int idx, vector4 t)
{
    assert((idx >= 0) && (idx < numPoints));
    texcoords[idx] = t;
}

/**
 * Makes a cube-shaoed mesh of sidelength 'side'.
 */
Mesh* Mesh::makeCube(float side)
{
    float f = side;

    Mesh *mesh = new Mesh(24);

    (*mesh)(0) = vector4(-f, f, -f);
    (*mesh)(1) = vector4(-f, f, f);
    (*mesh)(2) = vector4(f, f, f);
    (*mesh)(3) = vector4(f, f, -f);
    mesh->setNormal(0, vector4(0,1,0));
    mesh->setNormal(1, vector4(0,1,0));
    mesh->setNormal(2, vector4(0,1,0));
    mesh->setNormal(3, vector4(0,1,0));

    (*mesh)(4) = vector4(f, -f, -f);
    (*mesh)(5) = vector4(f, -f, f);
    (*mesh)(6) = vector4(-f, -f, f);
    (*mesh)(7) = vector4(-f, -f, -f);
    mesh->setNormal(4, vector4(0,-1,0));
    mesh->setNormal(5, vector4(0,-1,0));
    mesh->setNormal(6, vector4(0,-1,0));
    mesh->setNormal(7, vector4(0,-1,0));

    (*mesh)(11) = vector4(f, f, f);
    (*mesh)(10) = vector4(f, f, -f);
    (*mesh)(9) = vector4(f, -f, -f);
    (*mesh)(8) = vector4(f, -f, f);
    mesh->setNormal(8, vector4(1,0,0));
    mesh->setNormal(9, vector4(1,0,0));
    mesh->setNormal(10, vector4(1,0,0));
    mesh->setNormal(11, vector4(1,0,0));

    (*mesh)(12) = vector4(-f, f, f);
    (*mesh)(13) = vector4(-f, f, -f);
    (*mesh)(14) = vector4(-f, -f, -f);
    (*mesh)(15) = vector4(-f, -f, f);
    mesh->setNormal(12, vector4(-1,0,0));
    mesh->setNormal(13, vector4(-1,0,0));
    mesh->setNormal(14, vector4(-1,0,0));
    mesh->setNormal(15, vector4(-1,0,0));

    (*mesh)(19) = vector4(-f, f, f);
    (*mesh)(18) = vector4(f, f, f);
    (*mesh)(17) = vector4(f, -f, f);
    (*mesh)(16) = vector4(-f, -f, f);
    mesh->setNormal(16, vector4(0,0,1));
    mesh->setNormal(17, vector4(0,0,1));
    mesh->setNormal(18, vector4(0,0,1));
    mesh->setNormal(19, vector4(0,0,1));

    (*mesh)(20) = vector4(-f, f, -f);
    (*mesh)(21) = vector4(f, f, -f);
    (*mesh)(22) = vector4(f, -f, -f);
    (*mesh)(23) = vector4(-f, -f, -f);
    mesh->setNormal(20, vector4(0,0,-1));
    mesh->setNormal(21, vector4(0,0,-1));
    mesh->setNormal(22, vector4(0,0,-1));
    mesh->setNormal(23, vector4(0,0,-1));

    //now return it
    return mesh;
}
