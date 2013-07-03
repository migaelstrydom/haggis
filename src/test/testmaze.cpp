/************************************************************************
 *
 * testmaze.cpp
 * Maze class tests
 *
 ************************************************************************/

#include "maze.h"
#include "test.h"

#include <iostream>

#include <cppunit/extensions/HelperMacros.h>

/**
 * This test suite tests:
 *
 * Code: CT-Maze
 * Name: Maze class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the Maze class
 *
 */
class testmaze : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testmaze);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testLoadMaze);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        // setup the Test
    }

    void tearDown()
    {
    }

    /**
     * Test the state initialized by the constructor.
     */
    void testConstructor()
    {
	Maze m;

	CPPUNIT_ASSERT(m.getHeroCell() == NULL);
	CPPUNIT_ASSERT(m.getHaggisCell() == NULL);
	CPPUNIT_ASSERT(m.getLevel() == NULL);
	CPPUNIT_ASSERT(m.isCellSelectionEnabled() == false);
	CPPUNIT_ASSERT(m.getSelection() == NULL);
	CPPUNIT_ASSERT(m.getWidth() == -1);
	CPPUNIT_ASSERT(m.getHeight() == -1);
    }

    /**
     * Test the loading of level files.
     */
    void testLoadMaze()
    {
	Maze m;
	//maze position
	int pi, pj;

	m.load("test/testmaze.hag");
	CPPUNIT_ASSERT(m.getWidth() == 11);
	CPPUNIT_ASSERT(m.getHeight() == 11);

	CPPUNIT_ASSERT(m.getHeroCell() != NULL);
	m.getHeroCell()->getMazePosition(pi, pj);
	CPPUNIT_ASSERT((pi == 1) && (pj == 1));

	CPPUNIT_ASSERT(m.getHaggisCell() != NULL);
	m.getHaggisCell()->getMazePosition(pi, pj);
	CPPUNIT_ASSERT((pi == 1) && (pj == 2));

	//make sure all cells were allocated
	for(int i = 0; i < 11; i++)
	{
	    for(int j = 0; j < 11; j++)
	    {
		CPPUNIT_ASSERT(m.getCell(i, j) != NULL);
	    }
	}

	//make sure the items are placed on the cells
	CPPUNIT_ASSERT(m.getCell(1, 3)->getEntities().size() == 1);
	CPPUNIT_ASSERT(m.getCell(1, 4)->getEntities().size() == 1);
	CPPUNIT_ASSERT(m.getCell(1, 5)->getEntities().size() == 1);

	//make sure there are walls
	for(int i = 0; i < 11; i++)
	{
	    CPPUNIT_ASSERT(m.getCell(i, 0)->getWall() == true);
	}

	//make sure there are not walls
	for(int i = 1; i < 10; i++)
	{
	    CPPUNIT_ASSERT(m.getCell(1, i)->getWall() == false);
	}

	//make sure that the neighbours are correctly calculated
	for(int i = 0; i < 11; i++)
	{
	    for(int j = 0; j < 11; j++)
	    {
		for(unsigned k = 0; k < m.getCell(i, j)->neighbours.size(); k++)
		{
		    vector4 diff = m.getCell(i, j)->neighbours[k]->getPosition() - m.getCell(i,j)->getPosition();
		    diff.y = 0;
		    CPPUNIT_ASSERT(diff.length() < 1.8);
		}
	    }
	}
    }
};

void register_maze()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testmaze);
}
