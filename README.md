"Save the Haggis"
=====================================

Authors: Migael Strydom STRMIG002
         Timothy Stranex STRTIM004

This game was completed by the authors as a project for the CSC2002S course
at the University of Cape Town in 2006. We are now releasing it under the
Apache 2.0 license.

Quick Start
-----------

cd build
./haggis
(runs the game)
./haggis --test
(runs the unit tests)
cd doc
ls
(the documentation in .pdf format)

Dependencies:
  - OpenGL
  - libSDL
  - SDL_image
  - CppUnit


Building
--------

You can build the whole project by typing "make". This will build both the
documentation and the program and put them in the build directory. To build the
documentation, you need
   - LaTeX;
   - epstopdf; and,
   - python.
To build the program, you need
   - libSDL;
   - SDL_image;
   - OpenGL; and,
   - CppUnit.
You may need to edit src/Makefile and src/test/Makefile to add include and
library paths for CppUnit. You can build just the source by typing "make"
in the src/ directory. (In that case, the build output is in the src/
directory instead of the build/ directory.)


Files
-----

build/          Build output directory
build/haggis    The game binary
build/doc/      Documentation in .pdf format
build/images/   Images needed by the game
build/test/     Test data needed by the unit tests

doc/            Documentation

src/            The source code and data
src/game/       Source code for the game
src/test/       Unit testing code and data
src/images/     Images needed for the game
src/level1.hag  The level file

