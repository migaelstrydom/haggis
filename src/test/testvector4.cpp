/************************************************************************
 *
 * testvector4.cpp
 * Vector class tests
 *
 ************************************************************************/

#include "vector4.h"
#include "test.h"

#include <cppunit/extensions/HelperMacros.h>

/**
 * Code: CT-Vec
 * Name: vector4 class unit tests
 * Configuration: Unit testing context
 * Tools: Cppunit
 * Description: Class tests for the vector4 class
 */
class testvector4 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(testvector4);
    CPPUNIT_TEST(testIndex);
    CPPUNIT_TEST(testEqual);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testSubtract);
    CPPUNIT_TEST(testNegate);
    CPPUNIT_TEST(testScalarMultiply);
    CPPUNIT_TEST(testScalarDivide);
    CPPUNIT_TEST(testDotProduct);
    CPPUNIT_TEST(testCrossProduct);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST_SUITE_END();

private:
    vector4 v1, v2, v3, v4, v5, v6;
    vector4 e1, e2, e3;

public:

    void setUp()
    {
        v1 = vector4(1, 2, 3, 4);
        v2 = vector4(2, 3, 4, 5);
        v3 = vector4(1, 2, 3, 4);
        v4 = vector4(2, 4, 6, 8);
        v5 = vector4(-1, -2, -3, -4);
        v6 = vector4(3, 4, 0);

        e1 = vector4(1, 0, 0);
        e2 = vector4(0, 1, 0);
        e3 = vector4(0, 0, 1);
    }

    void tearDown()
    {
    }

    /**
     * Test accessing components by index.
     */
    void testIndex()
    {
        CPPUNIT_ASSERT(v1[0] == 1);
        CPPUNIT_ASSERT(v1[1] == 2);
        CPPUNIT_ASSERT(v1[2] == 3);
        CPPUNIT_ASSERT(v1[3] == 4);
    }

    /**
     * Test comparing vectors for equality.
     */
    void testEqual()
    {
        CPPUNIT_ASSERT(v1 == v3);
        CPPUNIT_ASSERT(v1 != v2);
    }

    /**
     * Test adding vectors.
     */
    void testAdd()
    {
        CPPUNIT_ASSERT(v1 + v3 == v4);

        // in-place add
        vector4 v(v1);
        v += v1;
        CPPUNIT_ASSERT(v == v4);
    }

    /**
     * Test subtracting vectors.
     */
    void testSubtract()
    {
        CPPUNIT_ASSERT(v4 - v3 == v1);

        // in-place subtract
        vector4 v(v4);
        v -= v1;
        CPPUNIT_ASSERT(v == v1);
    }

    /**
     * Test negating vectors.
     */
    void testNegate()
    {
        CPPUNIT_ASSERT(-v1 == v5);
    }

    /**
     * Test multiplying vectors by scalars.
     */
    void testScalarMultiply()
    {
        CPPUNIT_ASSERT(2 * v1 == v4); // pre-multiply
        CPPUNIT_ASSERT(v1 * 2 == v4); // post-multiply

        // in-place multiply
        vector4 v(v1);
        v *= 2;
        CPPUNIT_ASSERT(v == v4);
    }

    /**
     * Test dividing vectors by scalars.
     */
    void testScalarDivide()
    {
        CPPUNIT_ASSERT(v4 / 2 == v1); // post-divide

        // in-place divide
        vector4 v(v4);
        v /= 2;
        CPPUNIT_ASSERT(v == v1);
    }

    /**
     * Test finding the dot product of two vectors.
     */
    void testDotProduct()
    {
        CPPUNIT_ASSERT(v1 * v2 == 20);
        CPPUNIT_ASSERT(e1 * e1 == 1);
        CPPUNIT_ASSERT(e1 * e2 == 0);
    }

    /**
     * Test finding the cross product of two vectors.
     */
    void testCrossProduct()
    {
        CPPUNIT_ASSERT(e1 % e2 == e3);
        CPPUNIT_ASSERT(e2 % e1 == -e3);

        CPPUNIT_ASSERT(e2 % e3 == e1);
        CPPUNIT_ASSERT(e3 % e2 == -e1);

        CPPUNIT_ASSERT(e3 % e1 == e2);
        CPPUNIT_ASSERT(e1 % e3 == -e2);
    }

    /**
     * Test finding the length of a vector.
     */
    void testLength()
    {
        CPPUNIT_ASSERT(e1.length() == 1);
        CPPUNIT_ASSERT(v6.length() == 5);
    }
};

void register_vector4()
{
    CPPUNIT_TEST_SUITE_REGISTRATION(testvector4);
}
