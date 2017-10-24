#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include "lexer.h"

using namespace std;

int lineNumber;

bool tooManyFiles(int argc, char *argv[]) {

    int numOfFlags = 0;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
        if (argv[i][0] == '<') {
            numOfFlags++;
        }
    }

    if (argc - numOfFlags > 2) {
        return true;
    }
    return false;
}

bool badFile(int argc, char *argv[]) {
    int numOfFlags = 0;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
        if (argv[i][0] == '<') {
            numOfFlags++;
        }
    }

    for (int i = numOfFlags+1; i < argc; i++) {
        ifstream inFile;
        inFile.open(argv[i]);
        if (!inFile.is_open()) {
            return true;
        }
        inFile.close();
    }

    return false;
}


int main(int argc, char *argv[]) {
    bool uArg = false, vArg = false, sArg = false, iArg = false;
    string unvalidFlag = "";
    int numOfFlags = 0;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }

    vector<string> idSorted;

    istream *br;
    ifstream inFile;
    string lexeme;
    Token tok;

    if (argc - numOfFlags == 2) {
        inFile.open(argv[numOfFlags + 1]);
        br = &inFile;
    } else if (argc - numOfFlags == 1) {
        br = &cin;
    }





    for (int j = 0; j < argc; j++) {

        if (argv[j][0] == '-') {
            unvalidFlag += argv[j];
            if (argv[j][1] == 'v') {
                vArg = true;
            } else if (argv[j][1] == 's') {
                sArg = true;
            } else if (argv[j][1] == 'i') {
                iArg = true;
            } else {
                uArg = true;
            }
        }
    }

        if (uArg) {
            cout << unvalidFlag << " INVALID FLAG\n";
        } else {
            if (badFile(argc, argv)) {
                cout << argv[1] << " FILE NOT FOUND\n";
            } else if (tooManyFiles(argc, argv)) {
                cout << "TOO MANY FILES\n";
            } else {
                cout << "in the else" << endl;




                //cout << "you\n";

                int tokenCount = 0;
                int identifierCount = 0;
                int stringCount = 0;
                string aString = "";
                while ((tok = getToken(br)) != T_DONE && tok != T_ERROR) {
                    //cout << "in the while" << endl;
                    //cout << tok << endl;
                    if (vArg) {
                        cout << tok << endl;
                    }
                    tokenCount++;
                    if (tok == T_ID) {
                        identifierCount++;
                        idSorted.push_back(tok.GetLexeme());
                    }
                    if (tok == T_SCONST) {
                        stringCount++;
                        aString += tok.GetLexeme();
                    }


                }

                if (tok == T_ERROR) {
                    //cout << argc << endl;
                    cout << "Lexical error " << tok << endl;
                    return 1;
                } else {
                    int vectSize = idSorted.size();
                    int count = 0;
                    cout << "Token count: " << tokenCount << endl;
                    cout << "Identifier count: " << identifierCount << endl;
                    cout << "String count: " << stringCount << endl;
                    if (sArg) {
                        if (aString != "") {
                            cout << aString << endl;
                        }
                        //cout << aString << endl;
                    }
                    if (iArg) {
                        sort(idSorted.begin(), idSorted.end());

                        for (std::vector<string>::const_iterator j = idSorted.begin(); j != idSorted.end(); j++) {
                            if (count < vectSize - 1) {
                                cout << *j << ", ";
                                count++;
                            } else {
                                cout << *j << endl;
                            }
                        }
                    }

                }
                inFile.close();
            }

        }
    }