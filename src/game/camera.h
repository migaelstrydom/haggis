/************************************************************************
 *
 * camera.h
 * Camera class
 *
 * This class controls the viewpoint from which the user views the level.
 *
 ************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H
#include "vector4.h"

/**
 * Class Camera
 * A camera for setting the OpenGL projection and modelview matrices.
 */
class Camera 
{

public:
    /**
     * Empty Constructor
     */
    Camera ();
    /**
     * Accessor Methods
     */
    /**
     * Get the value of phi
     * The rotation around the vertical axis.
     * return the value of phi
     */
    vectype get_phi ( );
        
    
    /**
     * Set the value of phi
     * The rotation around the vertical axis.
     * param value the value of phi
     */
    void set_phi (vectype value );
        
    
    /**
     * Get the value of theta
     * The angle of elevation from the ground plane.
     * return the value of theta
     */
    vectype get_theta ( );
        
    
    /**
     * Set the value of theta
     * The angle of elevation from the ground plane.
     * param value the value of theta
     */
    void set_theta (vectype value );
        
    
    /**
     * Get the value of r
     * The distance from the focus.
     * @return the value of r
     */
    vectype get_r ( );
        
    
    /**
     * Set the value of r
     * The distance from the focus.
     * param value the value of r
     */
    void set_r (vectype value );
        
    
    /**
     * Get the value of focus
     * The camera's focus position.
     * return the value of focus
     */
    vector4 get_focus ( );
        
    
    /**
     * Set the value of focus
     * The camera's focus position.
     * param value the value of focus
     */
    void set_focus (vector4 value );
    
    /**
     * Operations
     */

    /**
     * These methods tell the camera to adjust its position.
     */
    void MoveLeft();
    void MoveRight();
    void ZoomIn();
    void ZoomOut();
    void MoveUp();
    void MoveDown();

    /**
     * Position the camera
     */
    void positionCamera();

    /**
     * Update the camera's position, orientation, and focus. Change in time sent as 
     * parameter.
     */
    void update(vectype);
        
    
private:
    /**
     * Fields
     */
    /**
     * The rotation around the vertical axis.
     */
     vectype phi;
    /**
     * The angle of elevation from the ground plane.
     */
     vectype theta;
    /**
     * The distance from the focus.
     */
     vectype r;
    /**
     * The camera's focus position.
     */
     vector4 focus;

     //states of motion
     bool bMoveLeft, bMoveRight, bZoomIn, bZoomOut, bMoveUp, bMoveDown;
};
#endif //CAMERA_H

