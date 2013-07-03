"Save the Haggis"
=====================================

Authors: Migael Strydom
         Timothy Stranex

This game was completed by the authors as a project for the CSC2002S course
at the University of Cape Town in 2006. We are now releasing it under the
Apache 2.0 license.

Overview
--------
"Save the Haggis" is a turn-based computer game in 3D where the
player sets off on a quest to destroy a mythical creature called a Haggis. The
game is called "Save the Haggis" as opposed to "Destroy the Haggis"
because of an ironic plot development in the game. According to the in-game
story in the introduction of the game, a country that had been eating Haggis
for generations had finally agreed to honoring the rights of the Haggis not
to be eaten, and were in the process of a political move to outlaw the eating
of Haggis. The aim of the hero in this game is to undermine this whole "Save
the Haggis" campaign.

Gameplay
--------
The gameplay takes place in a maze. The game is turn-based, alternating
between the hero's turn and the Haggis' turn. During the hero's turn, the user
can choose to move the hero to an adjacent cell in the maze (that is, take a
single step), jump over several intermediate cells to get to a cell that is not
adjacent, throw a grenade, use a psychic ability, or do nothing for the
turn. Each of these moves can be useful in overcoming obstacles in the maze,
discovering obstacles in the maze, or cunning tactics to defeat the
Haggis. During the Haggis' turn, it also has the option of any of the actions
the hero can do, and the program will decide what it is that the Haggis does
to avoid being defeated.

The hero has certain attributes. These attributes include health, energy and
ammunition. When the hero runs out of health or energy, the haggis wins the
game. The amount of ammunition is the number of grenades the hero can
throw. Every time the hero takes a step, he loses a bit of energy, but not as
much as when the hero jumps to a new cell. Health is lost when the hero gets
injured by the Haggis, which is when the Haggis throws a grenade at the hero,
or when the hero steps on a cell that contains a trap. The Haggis also has
these attributes and the same rules apply to it.

The maze consists of cells, some containing items and some containing a
wall. The hero and the Haggis each need to be occupying exactly one of the
cells at any one time, with the only conditions being that neither the hero
nor the Haggis can occupy a cell containing a wall, and they cannot occupy the
same cell. Some cells also contain items. When the hero steps on a cell that
contains an item, the effect of that item gets played out on the hero. Items
basically only alter the attributes of the hero in some way. There are health
items to increase the hero's health, and traps that decrease it. There are
also energy items to increase the hero's energy and ammunition crates that
increase the number of grenades the hero is carrying. The Haggis can also pick
up items on a cell.

The object of the game, with all these rules in place, is to attempt to kill
the Haggis by making either its health or its energy drop to zero, while not
being killed by the Haggis or traps in the maze first. Once this goal has been
achieved, the game will be over.

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

