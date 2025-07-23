#include "puzzle.h"
#include <sstream>
#include <fstream>
#include "structs.h"

using namespace std;

string Puzzle::getPosition(){
    string stringResponse;
    getline(puzzleFile,stringResponse);
    return stringResponse;
}

string Puzzle::getResponse(){
    string stringResponse;
    getline(puzzleFile,stringResponse);
    return stringResponse;
}

bool Puzzle::isCorrectMove(Move inputMove){

    string stringResponse;
    getline(puzzleFile,stringResponse);
    stringstream iss {stringResponse};

    string temp;

    iss >> temp;
    Tile ourStart = parseTile(temp);
    iss >> temp;
    Tile ourEnd = parseTile(temp);

    return ourStart == inputMove.getFrom() && ourEnd == inputMove.getTo();

}
