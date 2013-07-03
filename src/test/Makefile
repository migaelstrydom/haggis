CPP = gcc
CFLAGS = -Wall `sdl-config --cflags` -I../game

OBJ = testvector4.o testwindow.o testoverlay.o testmaze.o test.o \
      testhaggis.o testjumpaction.o testgrenadeaction.o testwalkaction.o \
	  testwaitaction.o

.PHONY : all
all: libtest.a

.PHONY : clean
clean:
	rm -f *~ *.o *.a

libtest.a: ${OBJ}
	rm -f libtest.a && ar rcs libtest.a ${OBJ}

test.o: test.cpp
	${CPP} ${CFLAGS} -c -o test.o test.cpp

testvector4.o: testvector4.cpp
	${CPP} ${CFLAGS} -c -o testvector4.o testvector4.cpp

testwindow.o: testwindow.cpp
	${CPP} ${CFLAGS} -c -o testwindow.o testwindow.cpp

testoverlay.o: testoverlay.cpp
	${CPP} ${CFLAGS} -c -o testoverlay.o testoverlay.cpp

testmaze.o: testmaze.cpp
	${CPP} ${CFLAGS} -c -o testmaze.o testmaze.cpp

testhaggis.o: testhaggis.cpp
	${CPP} ${CFLAGS} -c -o testhaggis.o testhaggis.cpp

testjumpaction.o: testjumpaction.cpp
	${CPP} ${CFLAGS} -c -o testjumpaction.o testjumpaction.cpp

testgrenadeaction.o: testgrenadeaction.cpp
	${CPP} ${CFLAGS} -c -o testgrenadeaction.o testgrenadeaction.cpp

testwalkaction.o: testwalkaction.cpp
	${CPP} ${CFLAGS} -c -o testwalkaction.o testwalkaction.cpp

testwaitaction.o: testwaitaction.cpp
	${CPP} ${CFLAGS} -c -o testwaitaction.o testwaitaction.cpp