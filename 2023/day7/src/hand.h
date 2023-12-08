# pragma once

#include <string>
#include <vector>

enum class HandType
{
    Five_of_a_kind,
    Four_of_a_kind,
    Full_house,
    Three_of_a_kind,
    Two_pair,
    One_pair,
    High_card
};

// class for a poker hand
class Hand {
private:
    // array of cards in the hand
    std::vector<std::string> cards;

public:
    // constructor
    Hand(std::vector<std::string> cards);

    // get the cards in the hand
    std::vector<std::string> getCards();

    // get the card at a given index
    std::string getCard(int index);

    // add a card to the hand
    void addCard(std::string card);

    // get type of hand
    HandType getType();
};
