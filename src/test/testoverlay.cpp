/************************************************************************
 *
 * testoverlay.cpp
 * Overlay class tests
 *
 ************************************************************************/

#include "overlay.h"
#include "test.h"
#include "action.h"
#include "level.h"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

/**
 * An extended version of Maze so that to allow overlay to be tested. This version of maze will be
 * passed to overlay and set in the right state for everything to be tested.
 */
class MazeTest : public Maze
{
 public:
    Cell *tCell;

    MazeTest()
    {
	tCell = new Cell();
    }

    ~MazeTest()
    {
	delete tCell;
    }

    Cell *getSelection()
    {
	return tCell;
    }
};
/**
 * An extended version of Level so that to allow overlay to be tested. This version of maze will be
 * passed to overlay and set in the right state for everything to be tested.
 */
class LevelTest : public Level
{
public:
    Maze *m;
    Action *a;

    LevelTest()
    {
        hero = new Hero();
        haggis = new Haggis(m = new Maze(), hero);
        a = NULL;
    }

    ~LevelTest()
    {
        delete hero;
        delete haggis;
        delete m;
    }

    virtual void notifyHeroAction(Action *a)
    {
        this->a = a;
    }

    Action* callPlayerAction()
    {
        return a;
    }

    void callSetTurn(turn t)
    {
        setCurrentTurn(t);
    }
};

/**
 * An extended version of Overlay that can be tested properly. It allows access to the protected members
 * of overlay that need to be tested.
 */
class OverlayTest : public Overlay
{
public:
    OverlayTest()
    {
    }

    void callButtonHandle(int n)
    {
	handleButton(n);
    }

    void callHandleCellSelection()
    {
	handleCellSelection();
    }
};

/**
 * This test suite tests:
 *
 * Code: CT-Ove
 * Name: Overlay class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the Overlay class
 *
 * Code: IN-Ove
 * Name: Overlay class integration tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Integration tests for the Overlay class
 */
class testoverlay : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testoverlay);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testActions);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        // setup the Testoverlay hierarchy
    }

    void tearDown()
    {
    }

    /**
     * Test the state initialized by the constructor.
     */
    void testConstructor()
    {
	Overlay ove;
	
	std::vector<Window*> childs = ove.getChildren();

	//make sure that there are 15 children
	CPPUNIT_ASSERT(childs.size() == 15);
	//Test that all the children are initialised correctly
	for(unsigned i = 0; i < childs.size(); i++)
	{
	    CPPUNIT_ASSERT(childs[i] != NULL);
	}
    }

    /**
     * This tests that overlay responds correctly to buttons being pressed and generates the correct
     * actions.
     */
    void testActions()
    {
	//go through the actions
	for(int i = 0; i < 3; i++)
	{
	    OverlayTest ove;
	    MazeTest maze;
	    LevelTest level;
	    
	    ove.setMaze(&maze);
	    ove.setLevel(&level);

	    level.callSetTurn(Level::HERO_TURN);
	    ove.callButtonHandle(i);
	    ove.callHandleCellSelection();
	    
	    CPPUNIT_ASSERT(level.callPlayerAction() != NULL);
	}
    }

};

void register_overlay()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testoverlay);
}
