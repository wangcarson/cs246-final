#include "puzzle.h"
#include <sstream>
#include <fstream>
#include "structs.h"
#include <iostream>

using namespace std;

Puzzle::Puzzle(string fileName): inFile{fileName} {}

string Puzzle::getPosition(){
    string temp;
    getline(inFile,temp);
    if (temp=="PUZZLEEND"){
        getline(inFile,temp);
    }
    return temp;
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
    puzzleLineNumber+=2;


    string line1, line2;
    string a, b, c, d;

    getline(inFile, line1); //GetNthLine()
    if (line1 == "PUZZLEEND") throw puzzle_end();
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

