/************************************************************************
 *
 * mesh.h
 * Mesh class
 *
 ************************************************************************/

#ifndef MESH_H
#define MESH_H

#include "vector4.h"
#include <cassert>

class Mesh
{
 private:
    int dList;        //display list id
    bool isDispList;   //is this mesh a displaylist
    vector4 *points, *normals, *texcoords;
    int numPoints;
 public:
    Mesh(int);  //number of points
    ~Mesh();

    /**
     * Renders the mesh.
     */
    void render(int);

    /**
     * Converts it into a display list to speed up rendering.
     */
    void makeDisplayList(int);

    //declared here for speed (compiled as inline)
    vector4 &operator()(int i)
    {
        assert((i >= 0) && (i < numPoints));
        return points[i];
    }

    //sets the normal for a given point
    void setNormal(int, vector4);

    //sets the texture coordinate for a given point
    void setTexCoord(int, vector4);

    /**
     * Make a cube mesh with the given side length. The mesh is returned.
     */
    static Mesh* makeCube(float side);
};

#endif //MESH_H
