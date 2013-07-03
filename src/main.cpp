/************************************************************************
 *
 * main.cpp
 * Main program
 *
 * 2006-08-30  Timothy Stranex  Created
 *
 ************************************************************************/

#include "game.h"
#include "test.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include <cstring>
using namespace std;

bool shouldTest(int argc, char *argv[])
{
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "--test") == 0) {
            return true;
        }
    }
    return false;
}

int runTests()
{
    registerAll();

    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &reg = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(reg.makeTest());
    return !runner.run();
}

int runGame(int argc, char *argv[])
{
    Game game(argc, argv);
    game.setFPSLimit(50.0);

    try {
        game.run();
    } catch (app_error &e) {
        cout << "Fatal error occured:" << endl;
        cout << "   " << e.what() << endl;
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (shouldTest(argc, argv)) {
        return runTests();
    } else {
        return runGame(argc, argv);
    }
}
