/************************************************************************
 *
 * Window.cpp
 * Window class implementation
 *
 ************************************************************************/

#include "window.h"

#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"

/**
 * Constructor. The window position and size are set to the zero vector.
 */
Window::Window()
    : parent(NULL), proj(ORTHOGRAPHIC), enabled(true), pass(RENDER_PASS_1)
{
}

/**
 * Destructor.
 */
Window::~Window()
{
}

/**
 * Render the contents of the window. This will not affect the screen
 * outside the window. Subclasses should override the draw() method, not
 * this method. If the window is disabled, no rendering will be performed.
 * The rendering pass is either 1 or 2.
 */
void Window::render(int pass, float dt)
{
    // if the window is disabled, do nothing
    if (!isEnabled()) {
        return;
    }

    // set the projection matrix

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // find the root window to calculate the aspect ratio
    Window *root = this;
    while (root->getParent()) {
        root = root->getParent();
    }
    float aspect = root->getSize().x / root->getSize().y;

    if (proj == PERSPECTIVE) {
        glEnable(GL_DEPTH_TEST);
        gluPerspective(40, aspect, 1.0, 600.0);
    } else {
        glDisable(GL_DEPTH_TEST);
        glOrtho(0, aspect, 0, 1, 1, -1);
    }

    // draw the window

    // translate the coordinate system to the window space
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(getPosition().x, getPosition().y, getPosition().z);

    // draw this window if we are in the correct render pass
    if (getRenderPasses() & pass) {
        draw(dt);
    }

    // render all the child windows
    for (std::vector<Window*>::iterator i=childs.begin(); i != childs.end();
         i++) {
        (*i)->render(pass, dt);
    }

    glPopMatrix();
}

/**
 * Handles a KeyEvent. If the window is disabled, the event will not
 * be processed.
 */
void Window::handleKeyEvent(KeyEvent event)
{
    // if the window is disabled, do nothing
    if (!isEnabled()) {
        return;
    }

    // propagate the event to all child windows
    for (std::vector<Window*>::iterator i=childs.begin(); i != childs.end();
         i++) {
        (*i)->handleKeyEvent(event);
    }
}

/**
 * Handles a ButtonEvent.
 * Returns true if this window or any of its children handled event,
 * so that other windows do not have to. The idea is that each event is
 * handled by only one window and ancestor windows. If the window is
 * disabled, this method will always return false.
 */
bool Window::handleMouseEvent(MouseEvent event)
{
    // if the window is disabled, do nothing
    if (!isEnabled()) {
        return false;
    }

    //Check that the mouse event happened in this window.
    //Otherwise return.
    if (!isInside(event.getPosition())) {
        return false;
    }

    //Send the event to all the children first.
    //If any window processes it, the rest don't have to.
    bool bHandled = false;

    for (std::vector<Window*>::iterator i=childs.begin();
	 (i != childs.end()) && (!bHandled); i++) {
        bHandled =
	    (*i)->handleMouseEvent(MouseEvent(event, (*i)->getPosition()));
    }

    if(!bHandled) {
        // now let this class handle the MouseEvent if it hasn't been handled
        // already
        return onHandleMouseEvent(event);
    } else {
        return true; // the event was handled by a child
    }
}

/**
 * Handles a MouseEvent.
 * Returns true if this window or any of its children handled event,
 * so that other windows do not have to. The idea is that each event is
 * handled by only one window and ancestor windows. If the window is
 * disabled, this method will always return false.
 */
bool Window::handleButtonEvent(ButtonEvent event)
{
    // if the window is disabled, do nothing
    if (!isEnabled()) {
        return false;
    }

    //Check that the mouse event happened in this window.
    //Otherwise return.
    if (!isInside(event.getPosition())) {
        return false;
    }

    //Send the event to all the children first.
    //If any window processes it, the rest don't have to.
    bool bHandled = false;

    for (std::vector<Window*>::iterator i=childs.begin();
	 (i != childs.end()) && (!bHandled); i++) {
        bHandled =
	    (*i)->handleButtonEvent(ButtonEvent(event, (*i)->getPosition()));
    }

    if(!bHandled) {
        // now let this class handle the ButtonEvent if it hasn't been handled
        // already
        return onHandleButtonEvent(event);
    } else {
        return true; // the event was handled by a child
    }
}

/**
 * Adds a child window. If the window already has a parent, it is removed
 * from the parent first. The window's parent is set to this.
 */
void Window::addChild(Window *child)
{
    if (child->getParent()) {
        child->getParent()->removeChild(child);
    }

    childs.push_back(child);
    child->parent = this;
}

/**
 * Returns a vector of the children of this window.
 */
std::vector<Window*> Window::getChildren()
{
    return childs;
}

/**
 * Removes a child window. Returns true if the window was a child or false
 * if not. If the window was a child, its parent is set to NULL.
 */
bool Window::removeChild(Window *child)
{
    for (std::vector<Window*>::iterator i=childs.begin(); i != childs.end();
         i++) {
        if (*i == child) {
            childs.erase(i);
            child->parent = NULL;
            return true;
        }
    }
    return false;
}

/**
 * Return the parent window. This may be NULL if there is no parent.
 */
Window *Window::getParent()
{
    return parent;
}

/**
 * Returns the position of the mouse relative to the window.
 */
vector4 Window::getMousePosition()
{
    // get the viewport dimensions
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float aspect = (float) viewport[2] / (float) viewport[3];

    // Get the mouse coordinates from SDL.
    int vx, vy;
    SDL_GetMouseState(&vx, &vy);

    // SDL places the origin in the top-left. We must transform it so
    // the origin is in the bottom-left.
    float x = (float) vx / (float) viewport[2] * aspect;
    float y = 1.0 - (float) vy / (float) viewport[3];

    // return the relative position
    return vector4(x, y) - getAbsolutePosition();
}

/**
 * Returns true if the position relative to the window is inside or
 * outside the window.
 */
bool Window::isInside(vector4 p)
{
    return (p.x >= 0) && (p.y >= 0) &&
        (p.x < getSize().x) && (p.y < getSize().y);
}

/**
 * Returns the position of this window relative to the parent. Only the x
 * and y components of the position are used.
 */
vector4 Window::getPosition()
{
    return pos;
}

/**
 * Returns the position of this window relative to the root window.
 * Only the x and y components of the position are used.
 */
vector4 Window::getAbsolutePosition()
{
    if (getParent()) {
        return getParent()->getAbsolutePosition() + getPosition();
    } else {
        return getPosition();
    }
}

/**
 * Set the position of the window relative to the parent. Only the x and y
 * components of the position are used.
 */
void Window::setPosition(vector4 pos)
{
    this->pos = pos;
}

/**
 * Return the size of the window. Only the x and y components of the
 * position are used.
 */
vector4 Window::getSize()
{
    return size;
}

/**
 * Set the size of the window. Only the x and y components of the
 * position are used.
 */
void Window::setSize(vector4 size)
{
    this->size = size;
}

/**
 * Return whether the window is enabled or disabled.
 */
bool Window::isEnabled()
{
    return enabled;
}

/**
 * Set whether the window is enabled or disabled. A disabled window and
 * all its children do not render and do not respond to events.
 */
void Window::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

/**
 * Returns a bitmask where the bits indicate which render passes this
 * window should be rendered in.
 */
int Window::getRenderPasses()
{
    return pass;
}

/**
 * Set the render pass bitmask for the window and all its children.
 */
void Window::setRenderPasses(int pass)
{
    this->pass = pass;

    // recursively set the children's renderpasses
    for (std::vector<Window*>::iterator i=childs.begin(); i != childs.end();
         i++) {
        (*i)->setRenderPasses(pass);
    }
}

/**
 * Set the projection method for the window. The projection matrix will
 * be set depending on this before draw() is called.
 */
void Window::setProjection(projection p)
{
    proj = p;
}

/**
 * Draw the window contents. This should be extended by subclasses.
 */
void Window::draw(float dt)
{
    /*glColor3f(1, 1, 1);

    // draws a bevelled rectangle

    float w = getSize().x;
    float h = getSize().y;
    float f = 0.05 * w;

    glBegin(GL_LINE_LOOP);
    glVertex2f(f, 0);
    glVertex2f(w-f, 0);
    glVertex2f(w, f);
    glVertex2f(w, h-f);
    glVertex2f(w-f, h);
    glVertex2f(f, h);
    glVertex2f(0, h-f);
    glVertex2f(0, f);
    glEnd();*/
}

/**
 * This is called by the handleMouseEvent method. It is specific to
 * each child class and therefore the implementation can be found in
 * each of the descendent classes. It returns true if it handled the event.
 */
bool Window::onHandleMouseEvent(MouseEvent)
{
    return false;
}

/**
 * This is called by the handleMouseEvent method. It is specific to
 * each child class and therefore the implementation can be found in
 * each of the descendent classes. It returns true if it handled the event.
 */
bool Window::onHandleButtonEvent(ButtonEvent)
{
    return false;
}
