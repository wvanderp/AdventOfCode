#include "readinput.h"

#include <string>
#include <iostream>
#include <vector> // Add this line to include the <vector>
#include <regex>

using namespace std;

std::vector<std::vector<char>> schematic;

void printSchematic()
{
    for (auto row : schematic)
    {
        for (auto c : row)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

struct schematicCell
{
    int number;
    // the location of the number in the schematic
    int row;
    int start;
    int end;
    bool hasCharacterAround;
};
std::vector<schematicCell> parseSchematic(std::vector<std::vector<char>> schematic)
{
    std::vector<schematicCell> schematicCells;

    int rowNumber = 0;
    for (auto row : schematic)
    {
        int cellNumber = 0;
        for (auto c : row)
        {
            // get the full number by checking the next chars
            std::string numberString = "";
            int i = 0;
            // if char is a number
            if (isdigit(c))
            {

                // if the char before is a number then skip
                if (isdigit(row[cellNumber - 1]))
                {
                    cellNumber++;
                    continue;
                }

                while (isdigit(row[cellNumber + i]))
                {
                    numberString += row[cellNumber + i];
                    i++;
                }

                // create a new cell
                schematicCell cell;
                cell.number = std::stoi(numberString);
                cell.row = rowNumber;
                cell.start = cellNumber;
                cell.end = cellNumber + i - 1;
                cell.hasCharacterAround = false;

                // add the cell to the vector
                schematicCells.push_back(cell);
            }
            cellNumber++;
        }
        rowNumber++;
    }

    return schematicCells;
}

void printSchematicCells(std::vector<schematicCell> schematicCells)
{
    for (auto cell : schematicCells)
    {
        std::cout << "number: " << cell.number << " row: " << cell.row << " start: " << cell.start << " end: " << cell.end << std::endl;
    }
}

// --------------------------
std::vector<char> characters = {'*', '-', '$', '=', '+', '&', '@', '#', '/', '%'};

struct foundChar
{
    char character;
    int row;
    int index;
};

std::vector<foundChar> getCharsAround(int row, int index, std::vector<std::vector<char>> schematic)
{
    std::vector<foundChar> charactersAround;

    // if this is not the first row
    if (row > 0)
    {
        // if this is not the first index
        if (index > 0)
        {
            foundChar character;
            character.character = schematic[row - 1][index - 1];
            character.row = row - 1;
            character.index = index - 1;
            charactersAround.push_back(character);
        }
        // if this is not the last index
        if (index < schematic[row].size() - 1)
        {
            foundChar character;
            character.character = schematic[row - 1][index + 1];
            character.row = row - 1;
            character.index = index + 1;
            charactersAround.push_back(character);
        }
        // get the char above
        foundChar character;
        character.character = schematic[row - 1][index];
        character.row = row - 1;
        character.index = index;
        charactersAround.push_back(character);
    }

    // if this is not the last row
    if (row < schematic.size() - 1)
    {
        // if this is not the first index
        if (index > 0)
        {
            foundChar character;
            character.character = schematic[row + 1][index - 1];
            character.row = row + 1;
            character.index = index - 1;
            charactersAround.push_back(character);
        }
        // if this is not the last index
        if (index < schematic[row].size() - 1)
        {
            foundChar character;
            character.character = schematic[row + 1][index + 1];
            character.row = row + 1;
            character.index = index + 1;
            charactersAround.push_back(character);
        }
        // get the char below
        foundChar character;
        character.character = schematic[row + 1][index];
        character.row = row + 1;
        character.index = index;
        charactersAround.push_back(character);
    }

    // if this is not the first index
    if (index > 0)
    {
        foundChar character;
        character.character = schematic[row][index - 1];
        character.row = row;
        character.index = index - 1;
        charactersAround.push_back(character);
    }

    // if this is not the last index
    if (index < schematic[row].size() - 1)
    {
        foundChar character;
        character.character = schematic[row][index + 1];
        character.row = row;
        character.index = index + 1;
        charactersAround.push_back(character);
    }

    return charactersAround;
}

bool hasCharacterAround(int row, int index, std::vector<std::vector<char>> schematic)
{
    auto charactersAround = getCharsAround(row, index, schematic);

    for (auto c : charactersAround)
    {
        for (auto character : characters)
        {
            if (c.character == character)
            {
                return true;
            }
        }
    }
    return false;
}

// --------------------------
// find to cells that are connected with a * (star)
// if two numbers can be connected with a star then they are connected
bool isConnected(schematicCell cell1, schematicCell cell2, std::vector<std::vector<char>> schematic)
{
    // check if cell1 is connected to the star
    std::vector<foundChar> charactersAroundCell1;
    for (int i = cell1.start; i <= cell1.end; i++)
    {
        auto charactersAround = getCharsAround(cell1.row, i, schematic);
        for (auto c : charactersAround)
        {
            charactersAroundCell1.push_back(c);
        }
    }

    foundChar star;

    for (auto c : charactersAroundCell1)
    {
        if (c.character == '*')
        {
            star = c;
        }
    }

    // check if cell2 is connected to the star
    std::vector<foundChar> charactersAroundCell2;
    for (int i = cell2.start; i <= cell2.end; i++)
    {
        auto charactersAround = getCharsAround(cell2.row, i, schematic);
        for (auto c : charactersAround)
        {
            charactersAroundCell2.push_back(c);
        }
    }

    for (auto c : charactersAroundCell2)
    {
        if (c.character == '*')
        {
            if (c.row == star.row && c.index == star.index)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    auto input = readInput("/home/walter/AdventOfCode/2023/day3/src/input.txt");

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

    // split lines in characters
    std::vector<char> row = {};
    for (auto line : lines)
    {
        for (auto c : line)
        {
            row.push_back(c);
        }
        schematic.push_back(row);
        row = {};
    }

    printSchematic();

    auto schematicCells = parseSchematic(schematic);

    // check if the cell has a character around it
    // the characters are *-$=+&@#/%
    // the cells are described with a row number and a start and end index
    for (auto &cell : schematicCells)
    {
        // loop over all char from the start to the end
        for (int i = cell.start; i <= cell.end; i++)
        {
            if (hasCharacterAround(cell.row, i, schematic))
            {
                cell.hasCharacterAround = true;
            }
        }
    }

    // sum all the numbers that have a character around them
    int sum = 0;
    for (auto cell : schematicCells)
    {
        if (cell.hasCharacterAround)
        {
            sum += cell.number;
        }
    }

    // part 2

    // filter out all the cells that don't have a character around them
    std::vector<schematicCell> schematicCellsWithCharacterAround;
    for (auto cell : schematicCells)
    {
        vector<foundChar> charactersAround;

        // loop over all char from the start to the end
        for (int i = cell.start; i <= cell.end; i++)
        {
            auto charactersAroundCell = getCharsAround(cell.row, i, schematic);
            for (auto c : charactersAroundCell)
            {
                charactersAround.push_back(c);
            }
        }

        for (auto c : charactersAround)
        {
            if (c.character == '*')
            {
                schematicCellsWithCharacterAround.push_back(cell);
            }
        }
    }

    int sum2 = 0;
    // collect a vector of seen pairs
    // vector of vector with 4 ints (row1, index1, row2, index2)
    std::vector<std::vector<int>> seenPairs;

    int maxComparions = schematicCellsWithCharacterAround.size() * schematicCellsWithCharacterAround.size();
    int comparisons = 0;

    for (auto cell1 : schematicCellsWithCharacterAround)
    {
        for (auto cell2 : schematicCellsWithCharacterAround)
        {
            // std::cout << "pair: " << cell1.number << " and " << cell2.number << std::endl;

            // filter out cells that are too far apart
            // manhattan distance
            int distance = abs(cell1.row - cell2.row) + abs(cell1.start - cell2.start);

            if (distance > 10)
            {
                // std::cout << "discarding pair: " << cell1.number << " and " << cell2.number << std::endl;
                comparisons++;
                continue;
            }

            // check if the cells are not the same
            if (cell1.row == cell2.row && cell1.start == cell2.start && cell1.end == cell2.end)
            {
                std::cout << "discarding pair same: " << cell1.number << " and " << cell2.number << std::endl;
                comparisons++;
                continue;
            }

            // filter out seen pairs
            bool isSeen = false;
            for (auto pair : seenPairs)
            {
                if (pair[0] == cell1.row && pair[1] == cell1.start && pair[2] == cell2.row && pair[3] == cell2.start)
                {
                    isSeen = true;
                }
            }
            if (isSeen)
            {
                // std::cout << "discarding pair seen: " << cell1.number << " and " << cell2.number << std::endl;
                comparisons++;
                continue;
            }

            // check if the cells are connected
            if (isConnected(cell1, cell2, schematic))
            {
                // check if the pair is not already seen

                // add the pair to the seen pairs
                std::vector<int> pair = {cell1.row, cell1.start, cell2.row, cell2.start};
                seenPairs.push_back(pair);
                std::vector<int> pairReversed = {cell2.row, cell2.start, cell1.row, cell1.start};
                seenPairs.push_back(pairReversed);
                // add the numbers to the sum
                sum2 += cell1.number * cell2.number;
            }

            comparisons++;
            std::cout << "comparisons: " << comparisons << " of " << maxComparions << std::endl;
        }
    }

    std::cout << "sum: " << sum << std::endl;
    std::cout << "sum2: " << sum2 << std::endl;
    return 0;
}
