#include <iostream>
#include <sstream>
#include "tree_structure.h"
using namespace std;

string removeQuotes(string NAMEArg){
    string newString = "";
    for(int i = 1; i < NAMEArg.size() - 1; i++){ // minus 1 don't want last one bc quotes
        newString += NAMEArg.at(i);
    }
    return newString;
}
bool idOrName(string unknownArg){
    for(char c: unknownArg){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

int main() {
    AVLTree tree;
    string line;
    string functionCall;
    string NAMEArg;
    string IDArg;
    int NArg;
    string unknownArg;
    string successVar;
    string result;
    bool valid = false;
    int intResult;
    int numLoops;
    getline(cin, line);
    numLoops = stoi(line);
    cout << endl;
    for(int i = 0; i< numLoops; i++){
        getline(cin, line);
        istringstream in(line); // gets the whole line
        in >> functionCall; // gets one word
        //cout << functionCall << endl;
        if(functionCall == "insert"){
            getline(in, NAMEArg, '"');
            getline(in, NAMEArg, '"');
            //in >> NAMEArg;
            in >> IDArg;
            //if(NAMEArg.at(0) == '"'){
                //NAMEArg = removeQuotes(NAMEArg);
                valid = tree.checkValid(NAMEArg, IDArg);
            //}
            if(valid){
                tree.insert(NAMEArg, IDArg);
            }
            else{
                cout << "unsuccessful" << endl;
            }
        }
        else if(functionCall == "remove"){
            in >> IDArg;
            tree.removeID(IDArg);
        }
        else if(functionCall == "search"){
            // determine if search name or id
            //string whiteSpace;
            in >> ws;
            getline(in, unknownArg, '"');
            getline(in, unknownArg, '"');

            if(idOrName(unknownArg)){
                IDArg = unknownArg;
                result = tree.searchID(IDArg);
                if(result != "unsuccessful"){
                    cout << result << endl;
                }
            }
            else{
                NAMEArg = unknownArg;
                result = tree.searchNAME(NAMEArg);
                if(result != "unsuccessful"){
                    cout << result << endl;
                }
            }
        }
        else if(functionCall == "printInorder"){
            tree.printIn();
            cout << endl;
        }
        else if(functionCall == "printPreorder"){
            tree.printPre();
            cout << endl;
        }
        else if(functionCall == "printPostorder"){
            tree.printPost();
            cout << endl;
        }
        else if(functionCall == "printLevelCount"){
            intResult = tree.printLevelCount();
        }
        else if(functionCall == "removeInorder"){
            in >> NArg;
            tree.removeInorderN(NArg);
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}


