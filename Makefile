CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -MMD -I./GameLogic -I./Graphics -I./Moves -I./Players -I./Structs -I.
EXEC = chess-exec
OBJECTS = subject.o Structs/tile.o Structs/piece.o Structs/move.o Players/player-human.o Players/player-computer.o GameLogic/chessboard.o Players/evaluation.o Players/player-engine.o Moves/movemaker.o Moves/movegenerator.o GameLogic/gamestatechecker.o puzzle.o GameLogic/boardmanager.o Graphics/window.o Graphics/textdisplay.o Graphics/graphicsdisplay.o GameLogic/gamecontroller.o main.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
