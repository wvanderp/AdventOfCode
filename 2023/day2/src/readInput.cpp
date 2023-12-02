#include "readinput.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * Reads the input from a file and returns it as a string.
 * @param path the relative path to the file
 * @return the input as a string
*/
string readInput(string path) {
    std:cout << "Reading input from " << path << endl;
    ifstream file(path);
    string input;
    string line;
    if(!file.is_open()) {
        cout << "Could not open file " << path << endl;
        return "";
    }
    while (getline(file, line)) {
        input += line + "\n";
    }
    return input;
}
