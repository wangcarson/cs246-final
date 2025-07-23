#include "puzzle.h"
#include <sstream>
#include <fstream>
#include "structs.h"
#include <iostream>

using namespace std;

Puzzle::Puzzle(): inFile{fileName} {}

string Puzzle::getPosition(){
    string stringResponse;
    getline(inFile, stringResponse);
    return stringResponse;
}

Move Puzzle::getResponseMove(vector<Move> &legalMoves) {
    string stringResponse;
    getline(inFile, stringResponse);

    stringstream iss {stringResponse};
    string a, b;
    iss >> a >> b;
    Tile ourStart = parseTile(a);
    Tile ourEnd = parseTile(b);

    for (auto it : legalMoves) {
        if (ourStart == it.getFrom() && ourEnd == it.getTo()) {
            inFile.close();   
            return it;
        }
    }
    throw runtime_error("getResponseMove(): ?");
}

bool Puzzle::isCorrectMove(Move inputMove){
    string stringResponse;
    getline(inFile, stringResponse);

    stringstream iss {stringResponse};
    string a, b;
    iss >> a >> b;
    Tile ourStart = parseTile(a);
    Tile ourEnd = parseTile(b);

    cout << "Input:   " << inputMove.getFrom() << " " << inputMove.getTo() << endl;
    cout << "Correct: " << ourStart << " " << ourEnd << endl;

    return ourStart == inputMove.getFrom() && ourEnd == inputMove.getTo();
}
