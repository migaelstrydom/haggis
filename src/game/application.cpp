/************************************************************************
 *
 * application.cpp
 * Application class implementation
 *
 ************************************************************************/

#include "application.h"
#include "keyevent.h"

#include "SDL/SDL.h"
#include <GL/gl.h>

#include <string>
#include <iostream>

/**
 * Default constructor for the application error class. Takes a string
 * error message as a parameter.
 */
app_error::app_error(std::string err)
{
    msg = err;
}

/**
 * Destructor.
 */
app_error::~app_error() throw()
{
    //nothing to destruct
}

/**
 * Returns the value of the error message.
 */
std::string app_error::what()
{
    return msg;
}

/**
 * Default constructor. Initialises variables to default values.
 */
Application::Application()
{
    running = false;
    maxfps = 25.0;
    w = 800;
    h = 600;
    root = NULL;
}

/**
 * Destructor.
 */
Application::~Application()
{
    //nothing to destruct
}
/**
 * Initialize libraries and start the main loop. This method blocks until
 * stop() is called.
 */
void Application::run() throw(app_error)
{
    //perform startup operations
    startup();

    // DT is the objective time per frame
    // dt is the actual time per frame
    float DT = 1.0/maxfps;
    float dt = DT;

    //get the time
    Uint32 start = SDL_GetTicks();
    running = true;
    while(running) {
        Uint32 now = SDL_GetTicks();

	//find the time since the start
        float t = (now - start) / 1000.0;
        try {
	    //start the next frame
            step(t, dt);
        } catch (app_error e) {  //if a fatal error occured
            shutdown();
            throw;
        }

        // update dt with the time spent on the last frame
        float dt = (SDL_GetTicks() - now) / 1000.0;

        // if dt < DT, we must delay before starting the next frame
        if (dt < DT) {
            SDL_Delay(Uint32((DT - dt)*1000.0));
            dt = DT;
        }
    }
    
    //shut down and deinitialise
    shutdown();
}

/**
 * Stop the main loop.
 */
void Application::stop()
{
    running = false;
}

/**
 * Set the maximum number of frames per second. If the program runs too
 * fast, a delay will be added to each frame so that this number is not
 * exceeded.
 */
void Application::setFPSLimit(float fps)
{
    maxfps = fps;
}

/**
 * Set the root window. This will be the first window rendered and
 * the first to receive events. NULL may be passed. If the window is
 * not NULL, its position and size will be set so that it fills the entire
 * screen.
 */
void Application::setRootWindow(Window *win)
{
    root = win;
    float aspect = (float) w / (float) h;
    root->setPosition(vector4());
    root->setSize(vector4(aspect, 1, 0, 0));
}
/**
 * Transform the window coordinate p to a coordinate relative to the root
 * window.
 */
vector4 Application::transformToRoot(vector4 p)
{
    return vector4(p.x / (float) h, 1.0 - p.y / (float) h);
}

/**
 * Convert the event into a KeyEvent and dispatch it to the root window.
 */
void Application::dispatchKeyEvent(SDL_Event event)
{
    if (root) {
        char key = (char) event.key.keysym.sym;

        if (event.key.type == SDL_KEYDOWN) {
            root->handleKeyEvent(KeyEvent(key, KeyEvent::PRESSED));
        } else {
            root->handleKeyEvent(KeyEvent(key, KeyEvent::RELEASED));
        }
    }
}

/**
 * Convert the event into a MouseEvent and dispatch it to the root window.
 */
void Application::dispatchMouseEvent(SDL_Event event)
{
    if (root) {
        vector4 p(event.motion.x, event.motion.y, 0);
        vector4 d(event.motion.xrel, event.motion.yrel, 0);
        root->handleMouseEvent(MouseEvent(transformToRoot(p),
                                          transformToRoot(d)));
    }
}

/**
 * Convert the event into a ButtonEvent and dispatch it to the root window.
 */
void Application::dispatchButtonEvent(SDL_Event event)
{
    if (root) {
        ButtonEvent::bstate s;
        if (event.button.type == SDL_MOUSEBUTTONDOWN) {
            s = ButtonEvent::PRESSED;
        } else {
            s = ButtonEvent::RELEASED;
        }

	//which button was pressed?
        ButtonEvent::button b;
        switch(event.button.button) {
        case 1: b = ButtonEvent::LEFT; break;
        case 2: b = ButtonEvent::MIDDLE; break;
        case 3: b = ButtonEvent::RIGHT; break;
        }

        vector4 p(event.button.x, event.button.y, 0);

	//dispatch
        root->handleButtonEvent(ButtonEvent(b, s, transformToRoot(p)));
    }
}

/**
 * Perform a single iteration of the main loop.
 */
void Application::step(float t, float dt) throw(app_error)
{
    // flush the event queue
    SDL_Event event;
    while(SDL_PollEvent(&event)) {  //see if there are any SDL events
        switch(event.type) {
        case SDL_QUIT:
            quit();
            break;
        case SDL_KEYDOWN:
	case SDL_KEYUP:    //a key has been pressed
            dispatchKeyEvent(event);
            break;
        case SDL_MOUSEMOTION:
            dispatchMouseEvent(event);  //the mouse moved
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            dispatchButtonEvent(event);   //a mouse button was pressed
            break;
        }
    }

    //clear the color and depth buffer
    glClearColor(0.32, 0.65, 0.89, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //reset the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // render the root window
    if (root) {
        root->render(RENDER_PASS_1, dt);
        root->render(RENDER_PASS_2, dt);
    }

    //flush the OpenGL pipeline
    glFlush();
    SDL_GL_SwapBuffers();
}

/**
 * Called when the user want to exit the program. The default behaviour
 * is to stop the main loop.
 */
void Application::quit()
{
    stop();
}

/**
 * Initialize all libraries and set up OpenGL.
 */
void Application::startup() throw(app_error)
{
    //initialise graphics
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::string s = "Error initializing SDL: ";
        throw app_error(s + SDL_GetError());
    }

    //set video mode
    if (!SDL_SetVideoMode(w, h, 32, SDL_OPENGL)) {
        std::string s = "Error creating window: ";
        throw app_error(s + SDL_GetError());
    }

    //window caption
    SDL_WM_SetCaption("Save the Haggis", NULL);

    //enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    //set the viewport
    glViewport(0, 0, w, h);

    //for lighting effects
    glShadeModel(GL_SMOOTH);

    glFrontFace(GL_CCW);

    //create an ambient light
    float ambientLight[] = {0.3, 0.3, 0.3, 0.3};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    float lightcol[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcol);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
/**
 * Shutdown all libraries.
 */
void Application::shutdown()
{
    SDL_Quit();
}
