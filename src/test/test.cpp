/************************************************************************
 *
 * test.cpp
 * Test suites
 *
 ************************************************************************/

#include "test.h"

void registerAll()
{
    register_vector4();
    register_window();
    register_overlay();
    register_maze();
    register_haggis();
    register_jumpaction();
    register_grenadeaction();
    register_walkaction();
    register_waitaction();
}
