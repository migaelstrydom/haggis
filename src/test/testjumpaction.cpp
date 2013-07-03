/************************************************************************
 *
 * testjumpaction.cpp
 * JumpAction class tests
 *
 ************************************************************************/

#include "haggis.h"
#include "maze.h"
#include "hero.h"
#include "level.h"
#include "jumpaction.h"

#include "test.h"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

/**
 * This test suite contains one test case:
 *
 * Code: CT-Jum
 * Name: JumpAction class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the JumpAction class
 */
class testjumpaction : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testjumpaction);
    CPPUNIT_TEST(testCanJumpTrue);
    CPPUNIT_TEST(testCanJumpFalse);
    CPPUNIT_TEST(testMarkSelectable);
    CPPUNIT_TEST(testMove);
    CPPUNIT_TEST(testEnergy);
    CPPUNIT_TEST_SUITE_END();

private:
    Maze m;
    Player p;

public:

    void setUp()
    {
        // load the maze for testing the haggis
        m.load("test/testjumpaction.hag");

        // put the player on a starting cell
        p.setCell(m.getCell(0, 0));

        // give the player full energy
        p.setEnergy(p.getMaxStat());
    }

    void tearDown()
    {
    }

    /**
     * Test that JumpAction::canJump works if the player has full energy.
     */
    void testCanJumpTrue()
    {
        CPPUNIT_ASSERT(JumpAction::canJump(&p));
    }

    /**
     * Test that JumpAction::canJump works if the player has no energy.
     */
    void testCanJumpFalse()
    {
        p.setEnergy(0);
        CPPUNIT_ASSERT(!JumpAction::canJump(&p));
    }

    /**
     * Test that JumpAction::markSelectable marks some of the cells selectable
     * and leaves others unselectable.
     */
    void testMarkSelectable()
    {
        JumpAction::markSelectable(&p, &m);

        bool sel = false;
        bool unsel = false;

        for (int i=0; i<m.getHeight(); i++) {
            for (int j=0; j<m.getWidth(); j++) {
                Cell *c = m.getCell(i, j);

                sel = sel || (c->isSelectable());
                unsel = unsel || (!c->isSelectable());
            }
        }

        CPPUNIT_ASSERT(sel);
        CPPUNIT_ASSERT(unsel);
    }

    /**
     * Test that the JumpAction moves the player to the target cell after five
     * seconds.
     */
    void testMove()
    {
        Cell *target = m.getCell(5, 5);

        JumpAction a(&p, target);
        CPPUNIT_ASSERT(a.update(5.0) == false);
        CPPUNIT_ASSERT(p.getCell() == target);
    }

    /**
     * Test that the JumpAction moves reduces the player's energy after moving
     * it to the target cell.
     */
    void testEnergy()
    {
        Cell *target = m.getCell(5, 5);

        JumpAction a(&p, target);
        CPPUNIT_ASSERT(a.update(5.0) == false);
        CPPUNIT_ASSERT(p.getEnergy() < p.getMaxStat());
    }
};

void register_jumpaction()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testjumpaction);
}
