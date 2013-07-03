/************************************************************************
 *
 * testhaggis.cpp
 * Haggis class tests
 *
 ************************************************************************/

#include "haggis.h"
#include "maze.h"
#include "hero.h"
#include "level.h"
#include "action.h"
#include "grenadeaction.h"
#include "walkaction.h"
#include "jumpaction.h"

#include "test.h"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

/**
 * An extended version of Level for testing observing Actions generated
 * by a Haggis. When it receives an Action, it stores it in the lastact
 * member and increments nacts.
 */
class TestLevel : public Level
{
public:
    Action *lastact;
    int nacts;

    TestLevel()
    {
        lastact = NULL;
        nacts = 0;
    }

    ~TestLevel()
    {
        if (lastact) {
            delete lastact;
            lastact = NULL;
        }
    }

    virtual void notifyHaggisAction(Action *a)
    {
        if (lastact) {
            delete lastact;
        }

        lastact = a;
        nacts++;
    }
};

/**
 * This test suite contains two test cases:
 *
 * Code: CT-Hag
 * Name: Haggis class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the Haggis class
 *
 * Code: IN-Hag
 * Name: Haggis-level class integration tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Level integration tests for the Haggis class
 */
class testhaggis : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testhaggis);
    CPPUNIT_TEST(testTurn);
    CPPUNIT_TEST(testDoesSomething);
    CPPUNIT_TEST(testOnlyOne);
    CPPUNIT_TEST(testForever);
    CPPUNIT_TEST(testGrenade);
    CPPUNIT_TEST(testWalk);
    CPPUNIT_TEST(testJump);
    CPPUNIT_TEST_SUITE_END();

private:
    // Infrastructure needed for exercising the haggis
    Maze m;
    Hero hero;
    TestLevel level;

    // The haggis object to use for testing
    Haggis *hag;

    // The number of turns to test over for tests which require multiple turns
    int N;

public:

    void setUp()
    {
        // load the maze for testing the haggis
        m.setLevel(&level);
        m.load("test/testhaggis.hag");

        // create the test haggis
        hag = new Haggis(&m, &hero);

        // put the hero on its starting cell
        hero.setCell(m.getHeroCell());

        // put the haggis on its starting cell
        hag->setCell(m.getHaggisCell());

        N = 100;
    }

    void tearDown()
    {
        delete hag;
    }

    /**
     * Test that the haggis doesn't generate any actions when it is not its
     * turn.
     */
    void testTurn()
    {
        hag->render(0.1);
        CPPUNIT_ASSERT(level.nacts == 0);
    }

    /**
     * Test that the haggis always performs some action in its turn.
     */
    void testDoesSomething()
    {
        hag->setTurn();
        hag->render(0.1);
        CPPUNIT_ASSERT(level.nacts == 1);
    }

    /**
     * Test that the haggis doesn't generate more than one action during its
     * turn.
     */
    void testOnlyOne()
    {
        hag->setTurn();
        for (int i=0; i<10; i++) {
            hag->render(0.1);
        }
        CPPUNIT_ASSERT(level.nacts == 1);
    }

    /**
     * Test that the haggis continues to generate moves forever. This is
     * tested for N turns.
     */
    void testForever()
    {
        for (int i=0; i<N; i++) {
            hag->setTurn();
            hag->render(0.1);
            CPPUNIT_ASSERT(level.nacts == i+1);
        }
    }

    /**
     * Check that the haggis never throws grenades when it has no ammunition.
     * This is tested for N turns.
     */
    void testGrenade()
    {
        for (int i=0; i<N; i++) {
            hag->setTurn();
            hag->render(0.1);
            CPPUNIT_ASSERT(level.nacts == i+1);

            if (!GrenadeAction::canThrow(hag)) {
                CPPUNIT_ASSERT(!(typeid(level.lastact) == typeid(GrenadeAction*)));
            }
        }
    }

    /**
     * Check that the haggis never walks when it doesn't have enough energy.
     * This is tested for N turns.
     */
    void testWalk()
    {
        for (int i=0; i<N; i++) {
            hag->setTurn();
            hag->render(0.1);
            CPPUNIT_ASSERT(level.nacts == i+1);

            if (!WalkAction::canWalk(hag)) {
                CPPUNIT_ASSERT(!(typeid(level.lastact) == typeid(WalkAction*)));
            }
        }
    }

    /**
     * Check that the haggis never jumps when it doesn't have enough energy.
     * This is tested for N turns.
     */
    void testJump()
    {
        for (int i=0; i<N; i++) {
            hag->setTurn();
            hag->render(0.1);
            CPPUNIT_ASSERT(level.nacts == i+1);

            if (!JumpAction::canJump(hag)) {
                CPPUNIT_ASSERT(!(typeid(level.lastact) == typeid(JumpAction*)));
            }
        }
    }
};

void register_haggis()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testhaggis);
}
