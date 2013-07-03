/************************************************************************
 *
 * camera.cpp
 * Camera class implementation
 *
 * This class controls the viewpoint from which the user views the level.
 *
 ************************************************************************/
#include "camera.h"
#include <math.h>
#include <GL/glu.h>

#define PHIVEL 1.0
#define THETAVEL 0.5
#define RVEL 10.0

/**
 * Default constructor. Start with default orientation.
 */
Camera::Camera()
    : phi(0), theta(M_PI/4), r(20)
{
}
 

/**
 * Get the value of phi
 * The rotation around the vertical axis.
 * return the value of phi
 */
vectype Camera::get_phi ( ) 
{
    return phi;
}
/**
 * Set the value of phi
 * The rotation around the vertical axis.
 * param: value the value of phi
 */
void Camera::set_phi (vectype value ) 
{
   phi = value;
}
/**
 * Get the value of theta
 * The angle of elevation from the ground plane.
 * return the value of theta
 */
vectype Camera::get_theta ( ) 
{
    return theta; 
}
/**
 * Set the value of theta
 * The angle of elevation from the ground plane.
 * param: value the value of theta
 */
void Camera::set_theta (vectype value ) 
{
    theta = std::min(std::max(value, M_PI/6), 7*M_PI/16);
}
/**
 * Get the value of r
 * The distance from the focus.
 * return the value of r
 */
vectype Camera::get_r ( ) 
{
    return r;
}
/**
 * Set the value of r
 * The distance from the focus.
 * param: value the value of r
 */
void Camera::set_r (vectype nr ) 
{
    r = std::min(std::max(nr, 2.0), 100.0);
}
/**
 * Get the value of focus
 * The camera's focus position.
 * return the value of focus
 */
vector4 Camera::get_focus ( ) 
{
    return focus;
}
/**
 * Set the value of focus
 * The camera's focus position.
 * param: value the value of focus
 */
void Camera::set_focus (vector4 value) 
{
    focus = value;
}
/**
 * Position the camera
 */
void Camera::positionCamera() 
{   
    //calculate the camera's position
    vector4 pos = focus;

    pos.y += r*sin(theta);
    pos.x += r*cos(theta)*sin(phi);
    pos.z += r*cos(theta)*cos(phi);

    gluLookAt(pos.x, pos.y, pos.z,
              focus.x, focus.y, focus.z,
              0.0, 1.0, 0.0);
}

/**
 * Update the camera's motion.
 */
void Camera::update(vectype deltaTime)
{
    if(bMoveLeft)
    {
	phi -= deltaTime*PHIVEL;
    }
    
    if(bMoveRight)
    {
	phi += deltaTime*PHIVEL;
    }

    if(bZoomIn)
    {
	r -= deltaTime*RVEL;
    }

    if(bZoomOut)
    {
	r += deltaTime*RVEL;
    }

    if (bMoveUp) {
        theta += deltaTime*THETAVEL;
    }

    if (bMoveDown) {
        theta -= deltaTime*THETAVEL;
    }

    bMoveLeft = bMoveRight = bZoomIn =  bZoomOut = false;
    bMoveUp = false;
    bMoveDown = false;
}

/*
 * Tell the camera to move left.
 */
void Camera::MoveLeft()
{
    bMoveLeft = true;
}

/*
 * Tell the camera to move right.
 */
void Camera::MoveRight()
{
    bMoveRight = true;
}

/*
 * Tell the camera to zoom in.
 */
void Camera::ZoomIn()
{
    bZoomIn = true;
}

/*
 * Tell the camera to zoom out.
 */
void Camera::ZoomOut()
{
    bZoomOut = true;
}

/**
 * Tell the camera to move up.
 */
void Camera::MoveUp()
{
    bMoveUp = true;
}

/**
 * Tell the camera to move down.
 */
void Camera::MoveDown()
{
    bMoveDown = true;
}
