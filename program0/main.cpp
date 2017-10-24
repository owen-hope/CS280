#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    for (int i = 1; i <= argc; i++) {
        int count = 0;
        char ch;

        ifstream infile;
        infile.open(argv[i]);

        if (infile.is_open() == false) {
            cout << argv[i] << " " << "FILE NOT FOUND" << endl;
        }

        if (infile.is_open()) {
            while (infile.get(ch))
            {
                count++;
            }
            cout << argv[i] << " " << count << endl;

        }

        //string word;
        //infile >> word;

        infile.close();
    }
    return 0;
}
