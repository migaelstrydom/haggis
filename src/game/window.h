/************************************************************************
 *
 * Window.h
 * Window class
 *
 ************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include "keyevent.h"
#include "mouseevent.h"
#include "buttonevent.h"
#include "vector4.h"

#include <vector>

#define RENDER_PASS_1 1
#define RENDER_PASS_2 2
#define RENDER_PASS_3 4

/**
 * A window represents a portion of the screen. Windows can have children which
 * lie within the parent window. Input events are propagated to the child
 * windows.
 *
 * The position of a window is the position of its bottom-left corner. The
 * top-right corner is getPosition() + getSize(). The root window always has
 * size (aspect, 1) regardless of the actual resolution. In the draw method,
 * you should keep your drawing in a box with corners (0,0) and getSize().
 *
 * When using Windows, you must be careful not to call the addChild() or
 * removeChild() methods when the window tree is being transversed.
 */
class Window
{
public:
    /**
     * Constructor. The window position and size are set to the zero vector.
     */
    Window();

    /**
     * Destructor.
     */
    virtual ~Window();

    /**
     * Render the contents of the window. This will not affect the screen
     * outside the window. Subclasses should override the draw() method, not
     * this method. If the window is disabled, no rendering will be performed.
     * The rendering pass is either 1 or 2.
     */
    virtual void render(int pass, float dt);

    /**
     * Handles a KeyEvent. If the window is disabled, the event will not
     * be processed.
     */
    virtual void handleKeyEvent(KeyEvent event);

    /**
     * Handles a ButtonEvent.
     * Returns true if this window or any of its children handled event,
     * so that other windows do not have to. The idea is that each event is
     * handled by only one window and ancestor windows. If the window is
     * disabled, this method will always return false.
     */
    bool handleButtonEvent(ButtonEvent event);

    /**
     * Handles a MouseEvent.
     * Returns true if this window or any of its children handled event,
     * so that other windows do not have to. The idea is that each event is
     * handled by only one window and ancestor windows. If the window is
     * disabled, this method will always return false.
     */
    bool handleMouseEvent(MouseEvent event);

    /**
     * Adds a child window. If the window already has a parent, it is removed
     * from the parent first. The window's parent is set to this.
     */
    void addChild(Window *child);

    /**
     * Returns a vector of the children of this window.
     */
    std::vector<Window*> getChildren();

    /**
     * Removes a child window. Returns true if the window was a child or false
     * if not. If the window was a child, its parent is set to NULL.
     */
    bool removeChild(Window *child);

    /**
     * Return the parent window. This may be NULL if there is no parent.
     */
    Window *getParent();

    /**
     * Returns the position of the mouse relative to the window.
     */
    vector4 getMousePosition();

    /**
     * Returns true if the position relative to the window is inside or
     * outside the window.
     */
    bool isInside(vector4 p);

    /**
     * Returns the position of this window relative to the parent. Only the x
     * and y components of the position are used.
     */
    vector4 getPosition();

    /**
     * Returns the position of this window relative to the root window.
     * Only the x and y components of the position are used.
     */
    vector4 getAbsolutePosition();

    /**
     * Set the position of the window relative to the parent. Only the x and y
     * components of the position are used.
     */
    void setPosition(vector4 pos);

    /**
     * Return the size of the window. Only the x and y components of the
     * position are used.
     */
    vector4 getSize();

    /**
     * Set the size of the window. Only the x and y components of the
     * position are used.
     */
    virtual void setSize(vector4 size);

    /**
     * Return whether the window is enabled or disabled.
     */
    bool isEnabled();

    /**
     * Set whether the window is enabled or disabled. A disabled window and
     * all its children do not render and do not respond to events.
     */
    void setEnabled(bool enabled);

    /**
     * Returns a bitmask where the bits indicate which render passes this
     * window should be rendered in.
     */
    int getRenderPasses();

    /**
     * Set the render pass bitmask for the window and all its children.
     */
    void setRenderPasses(int pass);

protected:
    /**
     * A type of projection matrix.
     */
    enum projection {ORTHOGRAPHIC, PERSPECTIVE};

    /**
     * Set the projection method for the window. The projection matrix will
     * be set depending on this before draw() is called.
     */
    void setProjection(projection p);

    /**
     * Draw the window contents. This should be extended by subclasses.
     */
    virtual void draw(float dt);

    /**
     * This is called by the handleMouseEvent method. It is specific to
     * each child class and therefore the implementation can be found in
     * each of the descendent classes. It returns true if it handled the event.
     */
    virtual bool onHandleMouseEvent(MouseEvent event);

    /**
     * This is called by the handleMouseEvent method. It is specific to
     * each child class and therefore the implementation can be found in
     * each of the descendent classes. It returns true if it handled the event.
     */
    virtual bool onHandleButtonEvent(ButtonEvent event);

private:
    /**
     * The position of the window relative to the parent window.
     */
    vector4 pos;

    /**
     * The size of the window. Only the x and y components of the
     * position are used.
     */
    vector4 size;

    /**
     * The parent window.
     */
    Window* parent;

    /**
     * A list of child windows.
     */
    std::vector<Window*> childs;

    /**
     * The projection method for the window.
     */
    projection proj;

    /**
     * Whether the window is enabled or disabled.
     */
    bool enabled;

    /**
     * A bitmask of render passes where the window should be rendered.
     */
    int pass;
};

#endif //WINDOW_H

