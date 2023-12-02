#include "readinput.h"

#include <string>
#include <iostream>
#include <vector> // Add this line to include the <vector>
#include <regex>

using namespace std;

// https://stackoverflow.com/a/46931770/1251780
std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

struct Round
{
    int red;
    int green;
    int blue;
};

struct Game
{
    int id;
    std::vector<Round> rounds;
};

void printGame(Game game)
{
    std::cout << "Game " << game.id << std::endl;
    for (auto round : game.rounds)
    {
        std::cout << "Round: "
                  << "r" << round.red << " g" << round.green << " b" << round.blue << std::endl;
    }
}

// actual bag content
int actualRed = 12;
int actualGreen = 13;
int actualBlue = 14;

int main()
{
    auto input = readInput("/home/walter/AdventOfCode/2023/day2/src/input.txt");

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

    std::vector<Game> games;

    // line: Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    for (auto line : lines)
    {
        Game game;

        // game id
        // split on :
        std::vector<std::string> parts = split(line, ":");
        game.id = std::stoi(parts[0].substr(5));

        // split on ;
        std::vector<std::string> rounds = split(parts[1], ";");

        for (auto round : rounds)
        {
            // split on ,
            std::vector<std::string> colors = split(round, ",");

            Round r;
            r.red = 0;
            r.green = 0;
            r.blue = 0;

            for (auto color : colors)
            {
                // split on space
                std::vector<std::string> colorParts = split(color, " ");

                if (colorParts[2] == "red")
                {
                    r.red = std::stoi(colorParts[1]);
                }
                else if (colorParts[2] == "green")
                {
                    r.green = std::stoi(colorParts[1]);
                }
                else if (colorParts[2] == "blue")
                {
                    r.blue = std::stoi(colorParts[1]);
                }
            }

            game.rounds.push_back(r);
        }

        games.push_back(game);
    }

    // part 1
    // loop over games
    std::vector<Game> possibleGames;
    int superPower = 0;

    for (auto game : games)
    {
        printGame(game);

        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        // loop over rounds
        for (auto round : game.rounds)
        {
            if (round.red > maxRed)
            {
                maxRed = round.red;
            }
            if (round.green > maxGreen)
            {
                maxGreen = round.green;
            }
            if (round.blue > maxBlue)
            {
                maxBlue = round.blue;
            }
        }

        std::cout << "Max red: " << maxRed << std::endl;
        std::cout << "Max green: " << maxGreen << std::endl;
        std::cout << "Max blue: " << maxBlue << std::endl;

        // check if the game is possible
        if (maxRed > actualRed || maxGreen > actualGreen || maxBlue > actualBlue)
        {
            std::cout << "Game " << game.id << " is not possible" << std::endl;
        }
        else
        {
            std::cout << "Game " << game.id << " is possible" << std::endl;
            possibleGames.push_back(game);
        }

        // part two

        int power = maxRed * maxGreen * maxBlue;

        superPower += power;
        std::cout << "Power: " << power << std::endl;
    }

    // sum the ids of the possible games
    int sum = 0;
    for (auto game : possibleGames)
    {
        sum += game.id;
    }


    // results

    std::cout << "Sum of possible games: " << sum << std::endl;
    std::cout << "Super power: " << superPower << std::endl;

    return 0;
}
