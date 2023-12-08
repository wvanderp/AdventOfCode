#include "readinput.h"

#include <string>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;



int main()
{
    auto input = readInput("/home/walter/AdventOfCode/2023/day7/src/input.txt");

    // split input into lines
    std::string delimiter = "\n";

    std::vector<std::string> lines;
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos)
    {
        token = input.substr(0, pos);
        lines.push_back(token);
        input.erase(0, pos + delimiter.length());
    }


    for (auto line : lines)
    {
        std::cout << line << std::endl;
    }

   
    return 0;
}
