#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

// this file does not work
// so dont bother trying to run it

struct Rule {
    long long source;
    long long destination;
    long long range;
};

// seed-to-soil map:
// 50 98 2
// 52 50 48
std::vector<Rule> parseRules(const std::string& section) {
    // split on the : then take the second part and split on \n 
    // dont use istringstream
    std::vector<Rule> rules;
    std::istringstream ruleStream(section.substr(section.find(':') + 1));
    std::string rule;
    while (std::getline(ruleStream, rule)) {
        std::istringstream ruleLine(rule);
        long long source, destination, range;
        ruleLine >> source >> destination >> range;
        rules.push_back({source, destination, range});
    }

    return rules;
}

long long mapTo(const std::vector<Rule>& from, long long n) {
    for (const auto& r : from) {
        // match range
        if (n >= r.source && n <= r.source + r.range) {
            // map to destination
            return r.destination + (n - r.source);
        }
    }
    return n;
}

int main() {
    std::ifstream inputFile("/home/walter/AdventOfCode/2023/day5/input.txt");
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();
    inputFile.close();

    std::vector<std::string> sections;
    size_t pos = 0;
    while ((pos = input.find("\n\n")) != std::string::npos) {
        sections.push_back(input.substr(0, pos));
        input.erase(0, pos + 2);
    }

    std::vector<long long> seeds;
    std::istringstream seedStream(sections[0].substr(sections[0].find(':') + 1));
    long long seed;
    while (seedStream >> seed) {
        seeds.push_back(seed);
    }


    std::vector<std::vector<Rule>> ruleMaps;
    for (size_t i = 1; i < sections.size(); ++i) {
    //  std::cout << "sections[i] = " << sections[i] << std::endl;

        ruleMaps.push_back(parseRules(sections[i]));
    }

    // print rules
    for (const auto& rules : ruleMaps) {
        for (const auto& r : rules) {
            std::cout << r.source << " " << r.destination << " " << r.range << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<std::pair<long long, long long>> seedPairs;
    for (size_t i = 0; i < seeds.size(); i += 2) {
        seedPairs.push_back({seeds[i], seeds[i + 1]});
    }

    long long minSeedLocation = std::numeric_limits<long long>::max();

    // for (const auto& seedPair : seedPairs) {
    //     for (long long s = seedPair.first; s < seedPair.first + seedPair.second; ++s) {
    //         long long seedLocation = s;
    //         for (const auto& rules : ruleMaps) {
    //             seedLocation = mapTo(rules, seedLocation);
    //         }
    //         minSeedLocation = std::min(seedLocation, minSeedLocation);
    //         // if(minSeedLocation == seedLocation) {
    //         //     std::cout << "New min seed location: " << minSeedLocation << std::endl;
    //         // }
    //     }
    // }

    // std::cout << minSeedLocation << std::endl;

    return 0;
}
