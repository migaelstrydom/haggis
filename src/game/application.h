/************************************************************************
 *
 * application.h
 * Application class
 *
 * 2006-08-30  Timothy Stranex  Created
 *
 ************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

#include <stdexcept>
#include <string>

#include "SDL/SDL.h"

/**
 * A fatal error has occured in the application.
 */
class app_error : public std::exception
{
public:
    /**
     * Constructor. The error message will be printed to stderr.
     */
    app_error(std::string err);

    /**
     * Destructor.
     */
    virtual ~app_error() throw();

    /**
     * Returns the error message.
     */
    virtual std::string what();

private:
    /**
     * The error message.
     */
    std::string msg;
};

/**
 * The Application is in charge of initializing the libraries and setting up
 * windows. It receives events from the windowing system and sends them to the
 * root window. It is also responsible for running the main loop.
 */
class Application
{
public:
    /**
     * Constructor. The constructor does not initialize any libraries. This
     * is done by the run() method.
     */
    Application();

    /**
     * Destructor. Needs to be virtual otherwise the compiler complains.
     */
    virtual ~Application();

    /**
     * Initialize libraries and start the main loop. This method blocks until
     * stop() is called.
     */
    void run() throw(app_error);

    /**
     * Stop the main loop.
     */
    void stop();

    /**
     * Set the maximum number of frames per second. If the program runs too
     * fast, a delay will be added to each frame so that this number is not
     * exceeded.
     */
    void setFPSLimit(float fps);

    /**
     * Set the root window. This will be the first window rendered and
     * the first to receive events. NULL may be passed. If the window is
     * not NULL, its position and size will be set so that it fills the entire
     * screen.
     */
    void setRootWindow(Window *win);

protected:
    /**
     * Perform a single iteration of the main loop.
     */
    virtual void step(float t, float dt) throw(app_error);

    /**
     * Called when the user want to exit the program. The default behaviour
     * is to stop the main loop.
     */
    void quit();

private:
    /**
     * The main loop runs while running is true.
     */
    bool running;

    /**
     * The maximum number of frames per second.
     */
    float maxfps;

    /**
     * The width and height of the screen.
     */
    int w, h;

    /**
     * The root window. May be NULL.
     */
    Window *root;

    /**
     * Initialize all libraries.
     */
    void startup() throw(app_error);

    /**
     * Shutdown all libraries.
     */
    void shutdown();

    /**
     * Transform the window coordinate p to a coordinate relative to the root
     * window.
     */
    vector4 transformToRoot(vector4 p);

    /**
     * Convert the event into a KeyEvent and dispatch it to the root window.
     */
    void dispatchKeyEvent(SDL_Event event);

    /**
     * Convert the event into a MouseEvent and dispatch it to the root window.
     */
    void dispatchMouseEvent(SDL_Event event);

    /**
     * Convert the event into a ButtonEvent and dispatch it to the root window.
     */
    void dispatchButtonEvent(SDL_Event event);
};

#endif //APPLICATION_H

