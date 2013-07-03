/************************************************************************
 *
 * testwalkaction.cpp
 * WalkAction class tests
 *
 ************************************************************************/

#include "haggis.h"
#include "maze.h"
#include "hero.h"
#include "level.h"
#include "walkaction.h"

#include "test.h"

#include <iostream>
#include <vector>

#include <cppunit/extensions/HelperMacros.h>

/**
 * This test suite contains one test case:
 *
 * Code: CT-Wal
 * Name: WalkAction class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the WalkAction class
 */
class testwalkaction : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testwalkaction);
    CPPUNIT_TEST(testCanWalkTrue);
    CPPUNIT_TEST(testCanWalkFalse);
    CPPUNIT_TEST(testMove);
    CPPUNIT_TEST(testEnergy);
    CPPUNIT_TEST(testMarkSelectable);
    CPPUNIT_TEST_SUITE_END();

private:
    Maze m;
    Player p;

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
     * Test that WalkAction::canWalk works if the player has full energy.
     */
    void testCanWalkTrue()
    {
        CPPUNIT_ASSERT(WalkAction::canWalk(&p));
    }

    /**
     * Test that WalkAction::canWalk works if the player has no energy.
     */
    void testCanWalkFalse()
    {
        p.setEnergy(0);
        CPPUNIT_ASSERT(!WalkAction::canWalk(&p));
    }

    /**
     * Test that the WalkAction moves the player to the target cell.
     */
    void testMove()
    {
        Cell *target = m.getCell(1, 0);

        WalkAction a(&p, target);
        cycleAction(&a);

        CPPUNIT_ASSERT(p.getCell() == target);
    }

    /**
     * Test that the WalkAction reduces the player's energy after moving
     * it to the target cell.
     */
    void testEnergy()
    {
        Cell *target = m.getCell(5, 5);

        WalkAction a(&p, target);
        cycleAction(&a);

        CPPUNIT_ASSERT(p.getEnergy() < p.getMaxStat());
    }

    /**
     * Test that WalkAction::markSelectable marks only adjacent cells
     * selectable.
     */
    void testMarkSelectable()
    {
        WalkAction::markSelectable(&p, &m);

        m.findCellNeighbours(p.getCell());
        std::vector<Cell*> neigh = p.getCell()->neighbours;

        for (int i=0; i<m.getHeight(); i++) {
            for (int j=0; j<m.getWidth(); j++) {

                Cell *c = m.getCell(i, j);
                if (!c->isSelectable()) {
                    continue;
                }

                // for each cell that is selectable, check if it is adjacent

                bool found = false;
                std::vector<Cell*>::iterator i;
                for (i=neigh.begin(); i != neigh.end(); i++) {
                    if (*i == c) {
                        found = true;
                        break;
                    }
                }

                CPPUNIT_ASSERT(found);
            }
        }
    }
};

void register_walkaction()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testwalkaction);
}
