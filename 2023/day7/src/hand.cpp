#include "hand.h"
#include <cassert>

int rank(std::string card)
{
    if (card[0] == 'A')
    {
        return 14;
    }
    if (card[0] == 'K')
    {
        return 13;
    }
    if (card[0] == 'Q')
    {
        return 12;
    }
    if (card[0] == 'J')
    {
        return 11;
    }
    if (card[0] == 'T')
    {
        return 10;
    }
    return stoi(card);
}



Hand::Hand(std::vector<std::string> cards) : cards(cards) {}

std::vector<std::string> Hand::getCards()
{
    return cards;
}

std::string Hand::getCard(int index)
{
    if (index >= 0 && index < cards.size())
    {
        return cards[index];
    }
    return "";
}

void Hand::addCard(std::string card)
{
    cards.push_back(card);
}

HandType Hand::getType()
{
    assert((rank("2") == 2)  && "There are five lights");
    assert((rank("9") == 9));
    assert((rank("T") == 10));
    assert((rank("2") == 2));

    // Implementation of hand type determination goes here
    // You can use the cards vector to analyze the hand and determine its type
    // Return the appropriate HandType enum value based on your analysis
    return HandType::High_card;
}
