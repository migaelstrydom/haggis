/************************************************************************
 *
 * testwaitaction.cpp
 * WaitAction class tests
 *
 ************************************************************************/

#include "player.h"
#include "waitaction.h"

#include "test.h"

#include <iostream>
#include <vector>

#include <cppunit/extensions/HelperMacros.h>

/**
 * This test suite contains one test case:
 *
 * Code: CT-Wai
 * Name: WaitAction class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the WaitAction class
 */
class testwaitaction : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testwaitaction);
    CPPUNIT_TEST(testCanWait);
    CPPUNIT_TEST(testCanWaitEmpty);
    CPPUNIT_TEST(testFinishes);
    CPPUNIT_TEST_SUITE_END();

private:
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
    }

    void tearDown()
    {
    }

    /**
     * Test that WaitAction::canWait always returns true.
     */
    void testCanWait()
    {
        CPPUNIT_ASSERT(WaitAction::canWait(&p));
    }

    /**
     * Test that WaitAction::canWait returns true even when the player has
     * no energy.
     */
    void testCanWaitEmpty()
    {
        p.setEnergy(0);
        CPPUNIT_ASSERT(WaitAction::canWait(&p));
    }

    /**
     * Test that the WaitAction finishes within twenty seconds.
     */
    void testFinishes()
    {
        WaitAction a(&p);
        cycleAction(&a);
    }
};

void register_waitaction()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testwaitaction);
}
