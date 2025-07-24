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
    for (auto it : legalMoves) {
        if (responseStart == it.getFrom() && responseEnd == it.getTo()) {
            return it;
        }
    }
    throw runtime_error("getResponseMove(): No legal move found.");
}

bool Puzzle::isCorrectMove(Move inputMove){
    return correctStart == inputMove.getFrom() && correctEnd == inputMove.getTo();
}

void Puzzle::loadMoves() {
    string line1, line2;
    string a, b, c, d;

    getline(inFile, line1);
    if (line1 == "PUZZLEEND") throw eof_error();
    stringstream iss1{line1};
    iss1 >> a >> b;

    getline(inFile, line2);
    stringstream iss2{line2};
    iss2 >> c >> d;

    try {
        responseStart = parseTile(a);
        responseEnd = parseTile(b);
        correctStart = parseTile(c);
        correctEnd = parseTile(d);
    } catch (...) {
        cerr << "updateCorrectMove(): on line " << line1 << " & " << line2 << endl;
        throw;
    }
}

