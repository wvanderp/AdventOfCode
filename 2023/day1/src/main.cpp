#include "readinput.h"

#include <string>
#include <iostream>
   #include <vector> // Add this line to include the <vector>
#include <regex>

using namespace std;

std::map<std::string, int> numberMap = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
    {"1", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9}
};

int main() {
    auto input = readInput("/home/walter/AdventOfCode/2023/src/input.txt");

    // split input into lines
    std::string delimiter = "\n";
    
    std::vector<std::string> lines;
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        lines.push_back(token);
        input.erase(0, pos + delimiter.length());
    }




    int sum = 0;

    for (auto line : lines) {
        std::cout << line << std::endl;

        std::regex re("^(.*?)([123456789]|(one)|(two)|(three)|(four)|(five)|(six)|(seven)|(eight)|(nine))");
        std::smatch match;
        std::regex_search(line, match, re);

        std::string firstNumberString = match[2];
        int firstNumber = numberMap[firstNumberString];


        std::regex re2(".*([123456789]|(one)|(two)|(three)|(four)|(five)|(six)|(seven)|(eight)|(nine))(.*?)$");
        std::smatch match2;
        std::regex_search(line, match2, re2);

        std::string secondNumberString = match2[1];
        int secondNumber = numberMap[secondNumberString];


        int fullNumber = firstNumber * 10 + secondNumber;

        sum += fullNumber;

        std::cout << line << std::endl;
        std::cout << firstNumber << " " << secondNumber << " " <<  std::endl;
    }

    std::cout << sum << std::endl;

    return 0;
}
