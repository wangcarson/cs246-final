#include "puzzle.h"
#include <sstream>
#include <fstream>
#include "structs.h"

using namespace std;


string Puzzle::getfileInput(){

    ifstream inFile;
    inFile.open(fileName);

    string stringResponse;
    getline(inFile,stringResponse);

    inFile.close();   
    return stringResponse;
}

bool Puzzle::isCorrectMove(Move inputMove){

    ifstream inFile;
    inFile.open(fileName);
    string stringResponse;
    getline(inFile,stringResponse);
    inFile.close(); 

    stringstream iss {stringResponse};

    string temp;

    iss >> temp;
    Tile ourStart = parseTile(temp);
    iss >> temp;
    Tile ourEnd = parseTile(temp);

    return ourStart == inputMove.getFrom() && ourEnd == inputMove.getTo();

}
