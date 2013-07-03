CPP = gcc
CFLAGS = -Wall `sdl-config --cflags` -g
LIBS = `sdl-config --libs` -lGL -lGLU -lcppunit

OBJ = application.o keyevent.o mouseevent.o buttonevent.o \
	  window.o game.o cell.o maze.o mesh.o camera.o level.o player.o \
      hero.o entity.o action.o walkaction.o widget.o button.o texture.o \
	  levelbegin.o grenadeaction.o overlay.o staticimage.o waitaction.o \
	  jumpaction.o haggis.o introwindow.o progressbar.o levelend.o \
	  creditswindow.o item.o itemaction.o billboard.o psychicaction.o \
	  floataction.o

.PHONY : all
all: libgame.a

.PHONY : clean
clean:
	rm -f *~ *.o *.a

libgame.a: ${OBJ}
	rm -f libgame.a && ar rcs libgame.a ${OBJ}

application.o: application.cpp
	${CPP} ${CFLAGS} -c -o application.o application.cpp

keyevent.o: keyevent.cpp
	${CPP} ${CFLAGS} -c -o keyevent.o keyevent.cpp

mouseevent.o: mouseevent.cpp
	${CPP} ${CFLAGS} -c -o mouseevent.o mouseevent.cpp

buttonevent.o: buttonevent.cpp
	${CPP} ${CFLAGS} -c -o buttonevent.o buttonevent.cpp

window.o: window.cpp window.h
	${CPP} ${CFLAGS} -c -o window.o window.cpp

game.o: game.cpp game.h
	${CPP} ${CFLAGS} -c -o game.o game.cpp

cell.o: cell.cpp cell.h
	${CPP} ${CFLAGS} -c -o cell.o cell.cpp

maze.o: maze.cpp maze.h
	${CPP} ${CFLAGS} -c -o maze.o maze.cpp

mesh.o: mesh.cpp mesh.h
	${CPP} ${CFLAGS} -c -o mesh.o mesh.cpp

camera.o: camera.cpp camera.h
	${CPP} ${CFLAGS} -c -o camera.o camera.cpp

level.o: level.cpp level.h
	${CPP} ${CFLAGS} -c -o level.o level.cpp

player.o: player.cpp player.h
	${CPP} ${CFLAGS} -c -o player.o player.cpp

hero.o: hero.cpp hero.h
	${CPP} ${CFLAGS} -c -o hero.o hero.cpp

entity.o: entity.cpp entity.h
	${CPP} ${CFLAGS} -c -o entity.o entity.cpp

action.o: action.cpp action.h
	${CPP} ${CFLAGS} -c -o action.o action.cpp

walkaction.o: walkaction.cpp walkaction.h
	${CPP} ${CFLAGS} -c -o walkaction.o walkaction.cpp

widget.o: widget.cpp widget.h
	${CPP} ${CFLAGS} -c -o widget.o widget.cpp

button.o: button.cpp button.h
	${CPP} ${CFLAGS} -c -o button.o button.cpp

texture.o: texture.cpp texture.h
	${CPP} ${CFLAGS} -c -o texture.o texture.cpp

levelbegin.o: levelbegin.cpp levelbegin.h
	${CPP} ${CFLAGS} -c -o levelbegin.o levelbegin.cpp

grenadeaction.o: grenadeaction.cpp grenadeaction.h
	${CPP} ${CFLAGS} -c -o grenadeaction.o grenadeaction.cpp

overlay.o: overlay.cpp overlay.h
	${CPP} ${CFLAGS} -c -o overlay.o overlay.cpp

staticimage.o: staticimage.cpp staticimage.h
	${CPP} ${CFLAGS} -c -o staticimage.o staticimage.cpp

waitaction.o: waitaction.cpp waitaction.h
	${CPP} ${CFLAGS} -c -o waitaction.o waitaction.cpp

jumpaction.o: jumpaction.cpp jumpaction.h
	${CPP} ${CFLAGS} -c -o jumpaction.o jumpaction.cpp

haggis.o: haggis.cpp haggis.h
	${CPP} ${CFLAGS} -c -o haggis.o haggis.cpp

introwindow.o: introwindow.cpp introwindow.h
	${CPP} ${CFLAGS} -c -o introwindow.o introwindow.cpp

progressbar.o: progressbar.cpp progressbar.h
	${CPP} ${CFLAGS} -c -o progressbar.o progressbar.cpp

levelend.o: levelend.cpp levelend.h
	${CPP} ${CFLAGS} -c -o levelend.o levelend.cpp

creditswindow.o: creditswindow.cpp creditswindow.h
	${CPP} ${CFLAGS} -c -o creditswindow.o creditswindow.cpp

item.o: item.cpp item.h
	${CPP} ${CFLAGS} -c -o item.o item.cpp

itemaction.o: itemaction.cpp itemaction.h
	${CPP} ${CFLAGS} -c -o itemaction.o itemaction.cpp

billboard.o: billboard.cpp billboard.h
	${CPP} ${CFLAGS} -c -o billboard.o billboard.cpp

psychicaction.o: psychicaction.cpp psychicaction.h
	${CPP} ${CFLAGS} -c -o psychicaction.o psychicaction.cpp

floataction.o: floataction.cpp floataction.h
	${CPP} ${CFLAGS} -c -o floataction.o floataction.cpp