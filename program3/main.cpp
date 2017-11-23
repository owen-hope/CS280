#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "parser.h"

int lineNumber = 0;
int errorCount = 0;
int idType = 0;
map<string, string> idmapstring;

void error(string file, int linenum, const string& message) {
    cout << file << ":" << linenum +1 << ":" << message << endl;
    errorCount++;
}

void postOrder(ParseTree *Node) {

    if (Node->getLeft() != 0) {
        cout << "L";
        postOrder(Node->getLeft());
        cout << "u";
    }
    if (Node->getRight() != 0) {
        cout << "R";
        postOrder((Node->getRight()));
        cout << "U";
    }
    cout << "N";
}




int main(int argc, char *argv[]) {

    istream *in = &cin;
    ifstream inFile;
    string fileName = "";
    bool tFlag = false;

    for (int i = 1; i < argc; i++) {
        string arg(argv[i]);

        if (arg == "-t") {
            tFlag = true;
        } else if (arg[0] == '-') {
            cerr << arg << " UNRECOGNIZED FLAG\n";
            return 1;
        } else if(in != &cin) {
            cerr << "TOO MANY FILES" << endl;
            return 1;
        }else{
            inFile.open(arg);
            if (inFile.is_open() == false) {
                cerr << arg << " FILE NOT FOUND\n";
                return 1;
            }
            fileName += arg;
            in = &inFile;
        }
    }


    map<string, int> symbol;
    ParseTree *tree = Prog(in, fileName, symbol);
    //iderror(tree);



    //postOrder(tree);
    if (tFlag) {
        postOrder(tree);
        cout << "\n";
    }
    iderror(tree);
    if (!thereIsAnError and errorCount == 0) {
        //There was some kind of pars error

        cout << "Total number of identifiers: " << tree->traversalCount(&ParseTree::isID) << endl;
        cout << "Total number of set: " << tree->traversalCount(&ParseTree::isSet) << endl;
        cout << "Total number of +: " << tree->traversalCount(&ParseTree::isPlus) << endl;
        cout << "Total number of *: " << tree->traversalCount(&ParseTree::Star) << endl;
    }




    return 0;
}