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
        string fullFenString,colour;
        cin >> fullFenString >> colour;
        
        // cout << "PUZZLESTART"<<endl;

        cout << fullFenString << " " << colour << endl;

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
