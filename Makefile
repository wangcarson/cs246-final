CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -MMD
EXEC = chess
OBJECTS = structs.o subject.o player.o chessboard.o movegenerator.o gamestatechecker.o movemaker.o boardmanager.o window.o textdisplay.o gamecontroller.o main.o 
# add .o files - graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
