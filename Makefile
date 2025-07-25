CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -MMD
EXEC = chess-exec
OBJECTS = structs.o subject.o player-human.o player-computer.o chessboard.o evaluation.o player-engine.o movemaker.o movegenerator.o gamestatechecker.o puzzle.o boardmanager.o window.o textdisplay.o graphicsdisplay.o gamecontroller.o main.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
