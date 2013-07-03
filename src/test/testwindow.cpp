/************************************************************************
 *
 * testwindow.cpp
 * Window class tests
 *
 ************************************************************************/

#include "window.h"
#include "test.h"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

/**
 * An extended version of Window for testing the event methods.
 * When it receives an event, it increments the corresponding counter and
 * returns the chosen response. It also keeps a count of the number of time
 * render() and draw() are called.
 */
class TestWindow : public Window
{
private:
    bool response; // response to events

public:
    int mouseEvent, buttonEvent, keyEvent; // event counters
    int renders, draws; // render counters

    TestWindow()
    {
        mouseEvent = buttonEvent = keyEvent = 0;
        renders = draws = 0;
        response = false;
    }

    void setResponse(bool r)
    {
        response = r;
    }

    virtual void handleKeyEvent(KeyEvent event)
    {
        Window::handleKeyEvent(event);
        keyEvent++;
    }

    virtual void render(int pass, float dt)
    {
        Window::render(pass, dt);
        renders++;
    }

protected:
    virtual bool onHandleMouseEvent(MouseEvent event)
    {
        mouseEvent++;
        return response;
    }

    virtual bool onHandleButtonEvent(ButtonEvent event)
    {
        buttonEvent++;
        return response;
    }

    virtual void draw(float dt)
    {
        draws++;
    }
};

/**
 * This test suite contains two test cases:
 *
 * Code: CT-Win
 * Name: Window class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the Window class
 *
 * Code: IN-Win
 * Name: Window class integration tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Integration tests for the Window class
 */
class testwindow : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testwindow);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAddChild_NoParent);
    CPPUNIT_TEST(testAddChild_Parent);
    CPPUNIT_TEST(testRemoveChild_WrongParent);
    CPPUNIT_TEST(testRemoveChild_RightParent);
    CPPUNIT_TEST(testIsInside_Inside);
    CPPUNIT_TEST(testIsInside_Outside);
    CPPUNIT_TEST(testSetPosition);
    CPPUNIT_TEST(testAbsolutePosition);
    CPPUNIT_TEST(testSetSize);
    CPPUNIT_TEST(testSetEnabled);
    CPPUNIT_TEST(testSetRenderPasses);
    CPPUNIT_TEST(testKeyEvent);
    CPPUNIT_TEST(testMouseEvent_All);
    CPPUNIT_TEST(testMouseEvent_Priority);
    CPPUNIT_TEST(testMouseEvent_Second);
    CPPUNIT_TEST(testButtonEvent_All);
    CPPUNIT_TEST(testButtonEvent_Priority);
    CPPUNIT_TEST(testButtonEvent_Second);
    CPPUNIT_TEST(testRender_Draw);
    CPPUNIT_TEST(testRender_All);
    CPPUNIT_TEST(testRender_Enabled);
    CPPUNIT_TEST(testRender_Pass1);
    CPPUNIT_TEST(testRender_Pass2);
    CPPUNIT_TEST(testRender_Pass3);
    CPPUNIT_TEST_SUITE_END();

private:
    /**
     * Count the number of occurences of child in the parent's child list.
     */
    bool countChild(Window *parent, Window *child)
    {
        int n = 0;
        std::vector<Window*> c = parent->getChildren();

        for (std::vector<Window*>::iterator i=c.begin(); i != c.end(); i++) {
            if (*i == child) {
                n++;
            }
        }

        return n;
    }

    /**
     * A hierarchy of TestWindows.
     */
    TestWindow a, b, c, d;

public:

    void setUp()
    {
        // setup the TestWindow hierarchy
        a.addChild(&b);
        a.addChild(&c);
        b.addChild(&d);

        a.setSize(vector4(10, 10));
        b.setSize(vector4(10, 10));
        c.setSize(vector4(10, 10));
        d.setSize(vector4(10, 10));

        a.setRenderPasses(RENDER_PASS_1 | RENDER_PASS_2 | RENDER_PASS_3);
        b.setRenderPasses(RENDER_PASS_2);
        c.setRenderPasses(RENDER_PASS_3);
        d.setRenderPasses(RENDER_PASS_1);
    }

    void tearDown()
    {
    }

    /**
     * Test the state initialized by the constructor.
     */
    void testConstructor()
    {
        Window win;
        CPPUNIT_ASSERT(win.getPosition() == vector4());
        CPPUNIT_ASSERT(win.getSize() == vector4());
        CPPUNIT_ASSERT(win.getParent() == NULL);
        CPPUNIT_ASSERT(win.isEnabled());
        CPPUNIT_ASSERT(win.getRenderPasses() == RENDER_PASS_1);
    }

    /**
     * Test adding a parentless child to a window.
     */
    void testAddChild_NoParent()
    {
        Window win;
        Window child;

        win.addChild(&child);

        // check that the child's parent pointer is set
        CPPUNIT_ASSERT(child.getParent() == &win);

        // check that the child is in the parent's child list
        CPPUNIT_ASSERT(countChild(&win, &child) == 1);
    }

    /**
     * Test adding an already parented child to a window.
     */
    void testAddChild_Parent()
    {
        Window win;
        Window parent;
        Window child;

        parent.addChild(&child);
        win.addChild(&child);

        // check that the child's parent pointer is correct
        CPPUNIT_ASSERT(child.getParent() == &win);

        // check that the child is not found in the previous parent's list
        CPPUNIT_ASSERT(countChild(&parent, &child) == 0);

        // check that the child is in the new parent's child list
        CPPUNIT_ASSERT(countChild(&win, &child) == 1);
    }

    /**
     * Test removing a child from the wrong parent.
     */
    void testRemoveChild_WrongParent()
    {
        Window win, parent, child;

        parent.addChild(&child);
        bool result = win.removeChild(&child);

        // check the return code
        CPPUNIT_ASSERT(result == false);

        // check that the child's parent pointer is still correct
        CPPUNIT_ASSERT(child.getParent() == &parent);

        // check that the child is still in the parent's child list
        CPPUNIT_ASSERT(countChild(&parent, &child) == 1);

        // check that the child is not in win's child list
        CPPUNIT_ASSERT(countChild(&win, &child) == 0);
    }

    /**
     * Test removing a child from its parent.
     */
    void testRemoveChild_RightParent()
    {
        Window win, child;

        win.addChild(&child);
        bool result = win.removeChild(&child);

        // check the return code
        CPPUNIT_ASSERT(result == true);

        // check the child's parent pointer
        CPPUNIT_ASSERT(child.getParent() == NULL);

        // check that the child is not in win's child list
        CPPUNIT_ASSERT(countChild(&win, &child) == 0);
    }

    /**
     * Test whether isInside() works for a point inside the window.
     */
    void testIsInside_Inside()
    {
        Window win;
        win.setSize(vector4(100, 100));

        // check for the window positioned at the origin
        CPPUNIT_ASSERT(win.isInside(vector4(50, 50))); // middle
        CPPUNIT_ASSERT(win.isInside(vector4(0, 0))); // botton-left
        CPPUNIT_ASSERT(win.isInside(vector4(99, 99))); // top-right

        // check for the window positioned not at the origin
        win.setPosition(vector4(50, 50));
        CPPUNIT_ASSERT(win.isInside(vector4(75, 75))); // middle
        CPPUNIT_ASSERT(win.isInside(vector4(0, 0))); // bottom-left
        CPPUNIT_ASSERT(win.isInside(vector4(99, 99))); // top-right
    }

    /**
     * Test whether isInside() works for a point outside the window.
     */
    void testIsInside_Outside()
    {
        Window win;
        win.setSize(vector4(100, 100));

        // check for the window positioned at the origin
        CPPUNIT_ASSERT(!win.isInside(vector4(-1, -1))); // bottom-left
        CPPUNIT_ASSERT(!win.isInside(vector4(100, 100))); // top-right
        CPPUNIT_ASSERT(!win.isInside(vector4(50, -1))); // y out of range

        // check for the window positioned not at the origin
        win.setPosition(vector4(50, 50));
        CPPUNIT_ASSERT(!win.isInside(vector4(-1, -1))); // bottom-left
        CPPUNIT_ASSERT(!win.isInside(vector4(100, 100))); // top-right
        CPPUNIT_ASSERT(!win.isInside(vector4(50, -1))); // y out of range
    }

    /**
     * Test setting the window position.
     */
    void testSetPosition()
    {
        Window win;

        win.setPosition(vector4(25, 25));
        CPPUNIT_ASSERT(win.getPosition() == vector4(25, 25));
    }

    /**
     * Test calculating the window's absolute position.
     */
    void testAbsolutePosition()
    {
        Window parent, win, win2;

        parent.addChild(&win);
        win.addChild(&win2);

        parent.setPosition(vector4(25, 25));
        win.setPosition(vector4(5, 3));
        win2.setPosition(vector4(1, 2));

        CPPUNIT_ASSERT(parent.getAbsolutePosition() == vector4(25, 25));
        CPPUNIT_ASSERT(win.getAbsolutePosition() == vector4(30, 28));
        CPPUNIT_ASSERT(win2.getAbsolutePosition() == vector4(31, 30));
    }

    /**
     * Test setting the window size.
     */
    void testSetSize()
    {
        Window win;

        win.setSize(vector4(100, 256));
        CPPUNIT_ASSERT(win.getSize() == vector4(100, 256));
    }

    /**
     * Test setting the enabled state of the window.
     */
    void testSetEnabled()
    {
        Window win;

        win.setEnabled(true);
        CPPUNIT_ASSERT(win.isEnabled());

        win.setEnabled(false);
        CPPUNIT_ASSERT(!win.isEnabled());
    }

    /**
     * Test setting the window render passes bitmask.
     */
    void testSetRenderPasses()
    {
        Window win;

        win.setRenderPasses(0);
        CPPUNIT_ASSERT(win.getRenderPasses() == 0);

        win.setRenderPasses(RENDER_PASS_1);
        CPPUNIT_ASSERT(win.getRenderPasses() == RENDER_PASS_1);

        int pass = RENDER_PASS_2 | RENDER_PASS_3;
        win.setRenderPasses(pass);
        CPPUNIT_ASSERT(win.getRenderPasses() == pass);
    }

    /**
     * Tests that key events are passed to every child.
     */
    void testKeyEvent()
    {
        // emit an event
        KeyEvent e('x', KeyEvent::PRESSED);
        a.handleKeyEvent(e);

        // check that that all the windows received a single event
        CPPUNIT_ASSERT(a.keyEvent == 1);
        CPPUNIT_ASSERT(b.keyEvent == 1);
        CPPUNIT_ASSERT(c.keyEvent == 1);
        CPPUNIT_ASSERT(d.keyEvent == 1);
    }

    /**
     * Tests that mouse events are passed to every child if none of them
     * accept the event.
     */
    void testMouseEvent_All()
    {
        // emit an event
        bool r = a.handleMouseEvent(MouseEvent(vector4(1, 1), vector4()));

        // check the result
        CPPUNIT_ASSERT(r == false);

        // check that all the windows received a single event
        CPPUNIT_ASSERT(a.mouseEvent == 1);
        CPPUNIT_ASSERT(b.mouseEvent == 1);
        CPPUNIT_ASSERT(c.mouseEvent == 1);
        CPPUNIT_ASSERT(d.mouseEvent == 1);
    }

    /**
     * Tests that childs added first get a higher mouse event priority.
     */
    void testMouseEvent_Priority()
    {
        // make both d and c respond
        d.setResponse(true);
        c.setResponse(true);

        // emit an event
        bool r = a.handleMouseEvent(MouseEvent(vector4(1, 1), vector4()));

        // check the result
        CPPUNIT_ASSERT(r == true);

        // check that the windows recieve the correct number of events
        CPPUNIT_ASSERT(a.mouseEvent == 0);
        CPPUNIT_ASSERT(b.mouseEvent == 0);
        CPPUNIT_ASSERT(c.mouseEvent == 0);
        CPPUNIT_ASSERT(d.mouseEvent == 1);
    }

    /**
     * Tests that the second child gets the mouse event if the first didn't
     * accept it.
     */
    void testMouseEvent_Second()
    {
        // make only c respond
        c.setResponse(true);

        // emit an event
        bool r = a.handleMouseEvent(MouseEvent(vector4(1, 1), vector4()));

        // check the result
        CPPUNIT_ASSERT(r == true);

        // check that the windows recieve the correct number of events
        CPPUNIT_ASSERT(a.mouseEvent == 0);
        CPPUNIT_ASSERT(b.mouseEvent == 1);
        CPPUNIT_ASSERT(c.mouseEvent == 1);
        CPPUNIT_ASSERT(d.mouseEvent == 1);
    }

    /**
     * Tests that button events are passed to every child if none of them
     * accept the event.
     */
    void testButtonEvent_All()
    {
        // emit an event
        bool r = a.handleButtonEvent(ButtonEvent(ButtonEvent::LEFT,
                                                 ButtonEvent::PRESSED,
                                                 vector4(1, 1)));

        // check the result
        CPPUNIT_ASSERT(r == false);

        // check that all the windows received a single event
        CPPUNIT_ASSERT(a.buttonEvent == 1);
        CPPUNIT_ASSERT(b.buttonEvent == 1);
        CPPUNIT_ASSERT(c.buttonEvent == 1);
        CPPUNIT_ASSERT(d.buttonEvent == 1);
    }

    /**
     * Tests that childs added first get a higher button event priority.
     */
    void testButtonEvent_Priority()
    {
        // make both d and c respond
        d.setResponse(true);
        c.setResponse(true);

        // emit an event
        bool r = a.handleButtonEvent(ButtonEvent(ButtonEvent::LEFT,
                                                 ButtonEvent::PRESSED,
                                                 vector4(1, 1)));

        // check the result
        CPPUNIT_ASSERT(r == true);

        // check that the windows recieve the correct number of events
        CPPUNIT_ASSERT(a.buttonEvent == 0);
        CPPUNIT_ASSERT(b.buttonEvent == 0);
        CPPUNIT_ASSERT(c.buttonEvent == 0);
        CPPUNIT_ASSERT(d.buttonEvent == 1);
    }

    /**
     * Tests that the second child gets the button event if the first didn't
     * accept it.
     */
    void testButtonEvent_Second()
    {
        // make only c respond
        c.setResponse(true);

        // emit an event
        bool r = a.handleButtonEvent(ButtonEvent(ButtonEvent::LEFT,
                                                 ButtonEvent::PRESSED,
                                                 vector4(1, 1)));

        // check the result
        CPPUNIT_ASSERT(r == true);

        // check that the windows recieve the correct number of events
        CPPUNIT_ASSERT(a.buttonEvent == 0);
        CPPUNIT_ASSERT(b.buttonEvent == 1);
        CPPUNIT_ASSERT(c.buttonEvent == 1);
        CPPUNIT_ASSERT(d.buttonEvent == 1);
    }

    /**
     * Tests that render() calls the draw() method.
     */
    void testRender_Draw()
    {
        TestWindow win;

        win.render(RENDER_PASS_1 | RENDER_PASS_2 | RENDER_PASS_3, 0);

        // check that the right number of methods were called
        CPPUNIT_ASSERT(win.renders == 1);
        CPPUNIT_ASSERT(win.draws == 1);
    }

    /**
     * Test rendering the entire hierarchy.
     */
    void testRender_All()
    {
        a.render(RENDER_PASS_1 | RENDER_PASS_2 | RENDER_PASS_3, 0);

        // check that everything was rendered and drawn
        CPPUNIT_ASSERT(a.renders == 1);
        CPPUNIT_ASSERT(b.renders == 1);
        CPPUNIT_ASSERT(c.renders == 1);
        CPPUNIT_ASSERT(d.renders == 1);

        CPPUNIT_ASSERT(a.draws == 1);
        CPPUNIT_ASSERT(b.draws == 1);
        CPPUNIT_ASSERT(c.draws == 1);
        CPPUNIT_ASSERT(d.draws == 1);
    }

    /**
     * Tests that child windows are not rendered or drawn if a window is
     * disabled.
     */
    void testRender_Enabled()
    {
        b.setEnabled(false);
        a.render(RENDER_PASS_1 | RENDER_PASS_2 | RENDER_PASS_3, 0);

        // check the number of renders
        CPPUNIT_ASSERT(a.renders == 1);
        CPPUNIT_ASSERT(b.renders == 1);
        CPPUNIT_ASSERT(c.renders == 1);
        CPPUNIT_ASSERT(d.renders == 0);

        // check the number of draws
        CPPUNIT_ASSERT(a.draws == 1);
        CPPUNIT_ASSERT(b.draws == 0);
        CPPUNIT_ASSERT(c.draws == 1);
        CPPUNIT_ASSERT(d.draws == 0);
    }

    /**
     * Tests that the right windows get drawn in RENDER_PASS_1.
     */
    void testRender_Pass1()
    {
        a.render(RENDER_PASS_1, 0);

        CPPUNIT_ASSERT(a.draws == 1);
        CPPUNIT_ASSERT(b.draws == 0);
        CPPUNIT_ASSERT(c.draws == 0);
        CPPUNIT_ASSERT(d.draws == 1);
    }

    /**
     * Tests that the right windows get drawn in RENDER_PASS_2.
     */
    void testRender_Pass2()
    {
        a.render(RENDER_PASS_2, 0);

        CPPUNIT_ASSERT(a.draws == 1);
        CPPUNIT_ASSERT(b.draws == 1);
        CPPUNIT_ASSERT(c.draws == 0);
        CPPUNIT_ASSERT(d.draws == 0);
    }

    /**
     * Tests that the right windows get drawn in RENDER_PASS_3.
     */
    void testRender_Pass3()
    {
        a.render(RENDER_PASS_3, 0);

        CPPUNIT_ASSERT(a.draws == 1);
        CPPUNIT_ASSERT(b.draws == 0);
        CPPUNIT_ASSERT(c.draws == 1);
        CPPUNIT_ASSERT(d.draws == 0);
    }
};

void register_window()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testwindow);
}
