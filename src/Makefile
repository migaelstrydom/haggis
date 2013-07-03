CPP = gcc
CFLAGS = -Wall `sdl-config --cflags` -Igame -Itest -g
LIBS = -Lgame -Ltest `sdl-config --libs` -lSDL_image -lGL -lGLU \
	   -lcppunit -lgame -ltest

.PHONY : all
all: haggis

.PHONY : clean
clean:
	rm -f *~ *.o haggis && ${MAKE} -C game clean && ${MAKE} -C test clean

.PHONY : game/libgame.a
game/libgame.a:
	${MAKE} -C game

.PHONY : test/libtest.a
test/libtest.a:
	${MAKE} -C test

haggis: main.cpp game/libgame.a test/libtest.a
	 ${CPP} ${CFLAGS} -o haggis main.cpp ${LIBS}

.PHONY : build
build: haggis
	cp haggis ../build && cp images ../build -R && cp level1.hag ../build && mkdir -p ../build/test && cp test/*.hag ../build/test
