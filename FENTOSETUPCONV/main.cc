#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>  

using namespace std;

string getFenPiecePlacementWithoutSlashes(string& fenString) {
    if (fenString.empty()) {
        return "";
    }

    size_t firstSpacePos = fenString.find(' ');
    string piecePlacementPart;

    if (firstSpacePos == string::npos) {
        piecePlacementPart = fenString;
        fenString = "";
    } else {
        piecePlacementPart = fenString.substr(0, firstSpacePos);
        fenString = fenString.substr(firstSpacePos + 1);
    }

    piecePlacementPart.erase(remove(piecePlacementPart.begin(), piecePlacementPart.end(), '/'), piecePlacementPart.end());
    return piecePlacementPart;
}


string extractBoardPart(string& fenString) {
    if (fenString.empty()) {
        return "";
    }

    size_t firstSpacePos = fenString.find(' ');
    string boardPart;

    if (firstSpacePos == string::npos) {
        boardPart = fenString;
        fenString = ""; 
    } else {
        boardPart = fenString.substr(0, firstSpacePos);
        fenString = fenString.substr(firstSpacePos + 1); 
    }
    return boardPart;
}




int main() {
    string moveToMake="*";

    while(!cin.eof() && moveToMake=="*"){
        string fullFenString;
        cin >> fullFenString;

        cout << "PUZZLESTART"<<endl;


        for(int i =1;i<=8;++i){
            for(char j='a';j<='h';++j){
                cout << "- " << j << i << endl;
            }
        }

        string boardPartWithSlashes = extractBoardPart(fullFenString);

        stringstream ss_board(boardPartWithSlashes);
        string rankString;
        int currentRank = 8; 
        while (getline(ss_board, rankString, '/') && currentRank >= 1) {
            char currentCol = 'a'; 
            
            for (char c : rankString) {
                if (isdigit(c)) {
                    int emptySquares = c - '0'; 
                    currentCol += emptySquares; 
                } else {

                    cout << "+ " << c << " " << currentCol << currentRank << endl;
                    currentCol++; 
                }

            }
            currentRank--; 
        }

        //white
        //black
        string colour;
        cin >>  colour;
        
        if (colour == "W" || colour == "w"){
            cout << "= white" << endl;
            colour = "White to move";

        }else{
            cout << "= black" << endl;
            colour = "Black to move";

        }
        cout << "PUZZLESETUP"<<endl;
        cout << colour << endl;
        cout << "PUZZLESOLUTION"<<endl;

        for(int i =0;i<4;++i){
            cin >> moveToMake;
        }

        while(cin >> moveToMake && moveToMake!= "*"){

            cout << moveToMake.substr(0, 2) << " " << moveToMake.substr(2, 2) << endl;
        }
        cout << "PUZZLEEND"<<endl;
    }

    return 0;
}
// puzzle list:
// 5r2/8/1R6/ppk3p1/2N3P1/P4b2/1K6/5B2 w b6 b5 c5 b5 c4 e5 b5 c5 e5 d7 c5 d6 d7 f8
// 