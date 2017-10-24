#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

void flagMBC (int argc, char *argv[]) {
    map<string, int> counters;
    map<string, int>:: iterator it;

    string word;
    string line;

    int maxValue  = 0;
    //int lenOfLine = 0;
    int lenOfWord = 0;
    int numOfFlags = 1;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }

    for (int i = numOfFlags; i < argc; i++) {
        counters.clear();
        lenOfWord = 0;
        //lenOfLine =0;
        int lineCount = 0;
        int bLineLen = 0;
        int biggestLine = 0;


        ifstream inFile;
        inFile.open(argv[i]);


        //lenOfWord = 0;
        //counters.clear();

        while (getline(inFile, line)) {
            bLineLen = 0;
            istringstream cin(line);


            while (cin >> word) {
                if (bLineLen == 0) {
                    bLineLen += word.length();
                } else {
                    bLineLen += word.length() + 1;
                }

                if ((int)word.length() >= lenOfWord) {
                    if ((int) word.length() > lenOfWord){
                        counters.clear();
                        counters[word]++;
                        lenOfWord = word.length();

                    } else{
                        if (counters[word]) {
                            counters[word]++;

                        } else{
                            counters[word] = 1;

                        }
                    }
                }
            }

            if (biggestLine == bLineLen) {
                lineCount++;
            } else if (biggestLine < bLineLen) {
                biggestLine = bLineLen;
                lineCount = 0;
                lineCount++;
            }

        }

        unsigned int maxAmount = 0;
        unsigned int count = 0;

        cout << argv[i] << ":\n";
        for (it = counters.begin(); it != counters.end(); ++it) {

            if (it->second > maxValue){
                maxValue = it->second;
            }
        }

        for (it = counters.begin(); it != counters.end(); ++it) {

            if (it ->second == maxValue) {
                maxAmount++;
            }

        }


        for (it = counters.begin(); it != counters.end(); ++it) {
            string k = it -> first;
            int v = it -> second;

            if (maxAmount == 0) {
                cout << k << "(" << v << ")" << endl;
            }else {
                if (count < maxAmount - 1) {
                    if (it->second == maxValue) {
                        cout << k << "(" << v << ")" << ", ";
                        count++;
                    }
                } else {
                    if (it->second == maxValue) {
                        cout << k << "(" << v << ")" << endl;
                    }
                }

            }
        }

        cout << biggestLine << "(" << lineCount << ")" << endl;

        inFile.close();


    }

    return;

}

void flagsMC (int argc, char *argv[]) {

    map<string, int> counters;
    map<string, int>:: iterator it;

    string word;
    string line;

    int maxValue  = 0;
    int lenOfLine = 0;
    int lenOfWord = 0;
    int numOfFlags = 1;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }

    for (int i = numOfFlags; i < argc; i++) {
        lenOfWord = 0;
        lenOfLine =0;
        int lineCount = 0;


        ifstream inFile;
        inFile.open(argv[i]);


            //lenOfWord = 0;
            //counters.clear();

            while (getline(inFile, line)) {
                if (lenOfLine == (int)line.length()) {
                    lineCount++;
                } else if (lenOfLine < (int)line.length()) {
                    lenOfLine = line.length();
                    lineCount = 0;
                    lineCount++;
                }

                istringstream cin(line);
                while (cin >> word) {
                    if ((int)word.length() >= lenOfWord) {
                        if ((int) word.length() > lenOfWord){
                            counters.clear();
                            counters[word]++;
                            lenOfWord = word.length();

                        } else{
                            if (counters[word]) {
                                counters[word]++;

                            } else{
                                counters[word] = 1;

                            }
                        }
                    }
                }
            }

            unsigned int maxAmount = 0;
            unsigned int count = 0;

            cout << argv[i] << ":\n";
        for (it = counters.begin(); it != counters.end(); ++it) {

            if (it->second > maxValue){
                maxValue = it->second;
            }
        }

        for (it = counters.begin(); it != counters.end(); ++it) {

            if (it ->second == maxValue) {
                maxAmount++;
            }

        }


        for (it = counters.begin(); it != counters.end(); ++it) {
            string k = it -> first;
            int v = it -> second;

            if (maxAmount == 0) {
                cout << k << "(" << v << ")" << endl;
            }else {
                if (count < maxAmount - 1) {
                    if (it->second == maxValue) {
                        cout << k << "(" << v << ")" << ", ";
                        count++;
                    }
                } else {
                    if (it->second == maxValue) {
                        cout << k << "(" << v << ")" << endl;
                    }
                }

            }
        }

            cout << lenOfLine << "(" << lineCount << ")" << endl;



        inFile.close();


    }

    return;
}


void flagB (int argc, char *argv[]) {
    map<string, int> counters;
    map<string, int>::iterator it;

    string word;
    string line;

    //int lenOfLine = 0;
    int lenOfWord = 0;

    int numOfFlags = 1;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }

    for (int i = numOfFlags; i < argc; i++) {
        counters.clear();
        lenOfWord = 0;
        //lenOfLine =0;
        int bLineLen = 0;
        int biggestLine = 0;


        ifstream inFile;
        inFile.open(argv[i]);



        //lenOfWord = 0;
        //counters.clear();



        while (getline(inFile, line)) {
            bLineLen = 0;
            istringstream cin(line);
            //while (cin >> word) {
            //  if (bLineLen == 0) {
            //    bLineLen += word.length();
            //} else {
            //  bLineLen += word.length() + 1;
            //}
            //}


            //if (biggestLine < bLineLen) {
            //  biggestLine = bLineLen;
            //}


            while (cin >> word) {
                if (bLineLen == 0) {
                    bLineLen += word.length();
                } else {
                    bLineLen += word.length() + 1;
                }

                if ((int) word.length() >= lenOfWord) {
                    if ((int) word.length() > lenOfWord) {
                        counters.clear();
                        counters[word]++;
                        lenOfWord = word.length();
                    } else {
                        if (counters[word]) {
                            counters[word]++;
                        } else {
                            counters[word] = 1;

                        }
                    }
                }
                //bLineLen ++;

            }

            if (biggestLine < bLineLen) {
                biggestLine = bLineLen;
            }
        }


        unsigned int count = 0;
        unsigned int size = counters.size();
        cout << argv[i] << ":\n";
        for (it = counters.begin(); it != counters.end(); ++it) {
            string k = it->first;

            if (count < size - 1) {
                cout << k << ", ";
            } else {
                cout << k << endl;
            }
            count++;
        }

        cout << biggestLine << endl;

        inFile.close();
    }
    return;
}

void flagM (int argc, char *argv[]) {
    map<string, int> counters;
    map<string, int>:: iterator it;

    string word;
    string line;
    int maxValue = 0;
    int lenOfLine = 0;
    int lenOfWord = 0;

    int numOfFlags = 1;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }

    for (int i = numOfFlags; i < argc; i++) {
        lenOfWord = 0;
        lenOfLine =0;




        ifstream inFile;
        inFile.open(argv[i]);

            //lenOfWord = 0;
            //counters.clear();

        while (getline(inFile, line)) {
            if (lenOfLine < (int)line.length()) {
                lenOfLine = line.length();

            }

            istringstream cin(line);
            while (cin >> word) {
                if ((int)word.length() >= lenOfWord) {
                    if ((int) word.length() > lenOfWord){
                        counters.clear();
                        counters[word]++;
                        lenOfWord = word.length();

                    } else{
                        if (counters[word]) {
                            counters[word]++;
                        } else{
                            counters[word] = 1;

                        }
                    }
                }
            }
        }


        unsigned int maxAmount=0;
        unsigned int count = 0;

        cout << argv[i] << ":\n";
        for (it = counters.begin(); it != counters.end(); ++it) {

            if (it->second > maxValue){
                maxValue = it->second;
            }
        }

        for (it = counters.begin(); it != counters.end(); ++it) {

            if (it ->second == maxValue) {
                maxAmount++;
            }

        }


        for (it = counters.begin(); it != counters.end(); ++it) {
            string k = it -> first;

            if (maxAmount == 0) {
                cout << k << endl;
            }else {
                if (count < maxAmount - 1) {
                    if (it->second == maxValue) {
                        cout << k << ", ";
                        count++;
                    }
                } else {
                    if (it->second == maxValue) {
                        cout << k << endl;
                    }
                }

            }
        }

        cout << lenOfLine << endl;
        inFile.close();


    }

    return;

}

void flagC (int argc, char *argv[]) {
    map<string, int> counters;
    map<string, int> longestWords;
    map<string, int>:: iterator it;

    int numOfFlags = 1;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }



    for (int i = numOfFlags; i < argc; i++) {
        int lenOfLine = 0;
        int lenOfWord = 0;
        int lineCount = 0;
        string word;
        string line;

        ifstream inFile;
        inFile.open(argv[i]);


        lenOfWord = 0;
        counters.clear();
        while (getline(inFile, line)) {
            if (lenOfLine == (int)line.length()) {
                lineCount++;

            } else if (lenOfLine < (int)line.length()) {
                lenOfLine = line.length();
                lineCount = 0;
                lineCount++;

            }

            istringstream cin(line);
            while (cin >> word) {
                if ((int)word.length() >= lenOfWord) {
                    if ((int) word.length() > lenOfWord){
                        counters.clear();
                        counters[word]++;
                        lenOfWord = word.length();

                    } else{
                        if (counters[word]) {
                            counters[word]++;

                        } else{
                            counters[word] = 1;

                        }
                    }

                }

            }

        }

        unsigned int count = 0;
        unsigned int size = counters.size();
        cout << argv[i] << ":\n";
        for (it = counters.begin(); it != counters.end(); it++) {
            string k = it -> first;
            int v = it -> second;
            if (count < size-1) {
                cout << k << "(" << v << ")" ", ";
            } else {
                cout << k << "(" << v << ")" << endl;
            }
            count++;
        }
        cout << lenOfLine << "(" << lineCount << ")" << endl;
        inFile.close();
    }
}

//Checks to see if there are any files in the params
void fileCheck (int argc) {
    if (argc == 1) {
        cout << "NO FILES\n";
    }
    return;
}

void defaul(int argc, char *argv[]) {

    map<string, int> counters;
    map<string, int>:: iterator it;

    string word;
    string line;

    int lenOfLine = 0;
    int lenOfWord = 0;
    int numOfFlags = 1;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            numOfFlags++;
        }
    }

    for (int i = numOfFlags; i < argc; i++) {
        lenOfWord = 0;
        lenOfLine =0;




        ifstream inFile;
        inFile.open(argv[i]);

        if (!inFile.is_open()) {
            cout << argv[i] << " FILE NOT FOUND\n";
        }
        else {

            //lenOfWord = 0;
            //counters.clear();

            while (getline(inFile, line)) {
                if (lenOfLine < (int)line.length()) {
                    lenOfLine = line.length();

                }

                istringstream cin(line);
                while (cin >> word) {
                    if ((int)word.length() >= lenOfWord) {
                        if ((int) word.length() > lenOfWord){
                            counters.clear();
                            counters[word]++;
                            lenOfWord = word.length();

                        } else{
                            if (counters[word]) {
                                counters[word]++;

                            } else{
                                counters[word] = 1;

                            }
                        }
                    }
                }
            }


            unsigned int count = 0;
            unsigned int size = counters.size();
            cout << argv[i] << ":\n";
            for (it = counters.begin(); it != counters.end(); ++it) {
                string k = it -> first;

                if (count < size-1) {
                    cout << k << ", ";
                } else {
                    cout << k << endl;
                }
                count++;
            }

            cout << lenOfLine << endl;

        }


        inFile.close();


    }


    return;
}


int main(int argc, char *argv[]) {
    bool mcArg = false;
    bool mbcArg = false;
    bool uArg = false;
    bool cArg = false;
    bool bArg = false;
    bool mArg = false;
    bool defArg = true;
    char *unvalidFlag;
    int b = 0;
    int c = 0;
    int m = 0;
    int u = 0;

    fileCheck(argc);

    for (int i = 0; i < argc; ++i) {

        if (argv[i][0] == '-') {
            unvalidFlag = argv[i];
            if (argv[i][1] == 'b') {
                b++;
            } else if (argv[i][1] == 'c') {
                c++;
            } else if (argv[i][1] == 'm') {
                m++;
            } else {
                u++;
            }
        }
    }

    if (m >= 1 && c >= 1 && b >= 1) {
        mbcArg = true;
        defArg = false;
    } else if (m >= 1 && c >= 1) {
        mcArg = true;
        defArg = false;
    } else if (m == 1) {
        mArg = true;
        defArg = false;
    } else if (u == 1) {
        uArg = true;
        defArg = false;
    } else if (b == 1) {
        bArg = true;
        defArg = false;
    } else if (c == 1) {
        cArg = true;
        defArg = false;
    }

    if (defArg){
        defaul(argc, argv);
    } else if (cArg) {
        flagC(argc, argv);
    } else if (bArg) {
        flagB(argc, argv);
    } else if (mArg) {
        flagM(argc, argv);
    } else if (mcArg){
        flagsMC(argc, argv);
    } else if (mbcArg) {
        flagMBC(argc, argv);
    } else if (uArg) {
        cout << unvalidFlag << " UNRECOGNIZED FLAG\n";
    }



    return 0;
}
