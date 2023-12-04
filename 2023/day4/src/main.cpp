#include "readinput.h"

#include <string>
#include <iostream>
#include <vector> // Add this line to include the <vector>
#include <regex>

using namespace std;


struct Card {
    int id;
    std::vector<int> numbers;
    std::vector<int> winningNumbers;
};

void printCard(Card card){
    std::cout << "Card " << card.id << ": ";
    for(auto number : card.numbers){
        std::cout << number << " ";
    }
    std::cout << "| ";
    for(auto number : card.winningNumbers){
        std::cout << number << " ";
    }
    std::cout << std::endl;
}



int main()
{
    auto input = readInput("/workspaces/AdventOfCode/2023/day4/src/input.txt");

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

    // split lines into cards
    // line: Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    // with the the id being the first number everything after the : are the numbers
    // and the numbers after the | are the winning numbers

    std::vector<Card> cards;
    for(auto line : lines){
        Card card;
        std::string delimiter = ":";
        size_t pos = 0;
        std::string token;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        card.id = std::stoi(token);
        line.erase(0, pos + delimiter.length());

        delimiter = "|";
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        std::string delimiter2 = " ";
        size_t pos2 = 0;
        std::string token2;
        while ((pos2 = token.find(delimiter2)) != std::string::npos)
        {
            token2 = token.substr(0, pos2);
            card.numbers.push_back(std::stoi(token2));
            token.erase(0, pos2 + delimiter2.length());
        }
        card.numbers.push_back(std::stoi(token));
        line.erase(0, pos + delimiter.length());

        delimiter = " ";
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        while ((pos2 = token.find(delimiter2)) != std::string::npos)
        {
            token2 = token.substr(0, pos2);
            card.winningNumbers.push_back(std::stoi(token2));
            token.erase(0, pos2 + delimiter2.length());
        }
        card.winningNumbers.push_back(std::stoi(token));
        cards.push_back(card);
    }

    // print cards
    for(auto card : cards){
        printCard(card);
    }

   
    return 0;
}
