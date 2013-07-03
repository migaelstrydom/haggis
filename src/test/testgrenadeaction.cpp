/************************************************************************
 *
 * testgrenadeaction.cpp
 * GrenadeAction class tests
 *
 ************************************************************************/

#include "haggis.h"
#include "maze.h"
#include "hero.h"
#include "level.h"
#include "grenadeaction.h"
#include "action.h"

#include "test.h"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

/**
 * This test suite contains one test case:
 *
 * Code: CT-Gre
 * Name: GrenadeAction class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the GrenadeAction class
 */
class testgrenadeaction : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testgrenadeaction);
    CPPUNIT_TEST(testCanThrowTrue);
    CPPUNIT_TEST(testCanThrowFalse);
    CPPUNIT_TEST(testDestroyWall);
    CPPUNIT_TEST(testReduceAmmo);
    CPPUNIT_TEST(testHurtOpponent);
    CPPUNIT_TEST_SUITE_END();

private:
    Maze m;
    Player p;
    Player o;

    // Update the action until it returns false for a maximum of twenty
    // updates.
    void cycleAction(Action *a)
    {
        int n = 0;
        while (a->update(1.0) != false) {
            n++;
            CPPUNIT_ASSERT(n <= 20);
        }
    }

public:

    void setUp()
    {
        // load the maze for testing the haggis
        m.load("test/testgrenadeaction.hag");

        // put the player on a starting cell
        p.setCell(m.getCell(0, 0));

        // put the opponent player on a different starting cell
        o.setCell(m.getCell(2, 2));

        // give the player full ammunition
        p.setAmmo(p.getMaxStat());

        // give the opponent full health
        o.setHealth(o.getMaxStat());
    }

    void tearDown()
    {
    }

    /**
     * Check that GrenadeAction::canThrow returns true for a player with full
     * ammunition.
     */
    void testCanThrowTrue()
    {
        CPPUNIT_ASSERT(GrenadeAction::canThrow(&p));
    }

    /**
     * Check that GrenadeAction::canThrow returns false for a player with
     * no ammunition.
     */
    void testCanThrowFalse()
    {
        p.setAmmo(0);
        CPPUNIT_ASSERT(!GrenadeAction::canThrow(&p));
    }

    /**
     * Check that the GrenadeAction will destroy a wall if the target cell
     * is a wall.
     */
    void testDestroyWall()
    {
        Cell *target = m.getCell(m.getHeight()-1, m.getWidth()-1);
        CPPUNIT_ASSERT(target->getWall());
	for(int i = 0; i < 5; i++)
	{
	    GrenadeAction g(&p, &o, p.getCell(), target);
	    cycleAction(&g);
	}
        CPPUNIT_ASSERT(!target->getWall());
    }

    /**
     * Check that the GrenadeAction will reduce the ammunition of the
     * thrower.
     */
    void testReduceAmmo()
    {
        GrenadeAction g(&p, &o, p.getCell(), o.getCell());
        cycleAction(&g);
        CPPUNIT_ASSERT(p.getAmmo() < p.getMaxStat());
    }

    /**
     * Check that the GrenadeAction will reduce the opponent's health if
     * the opponent is on the target cell.
     */
    void testHurtOpponent()
    {
        GrenadeAction g(&p, &o, p.getCell(), o.getCell());
        cycleAction(&g);
        CPPUNIT_ASSERT(o.getHealth() < o.getMaxStat());
    }
};

void register_grenadeaction()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testgrenadeaction);
}
