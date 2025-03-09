#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"

Pack::Pack()
{
    for (int i = SPADES; i <= DIAMONDS; i++)
    {
        for (int j = NINE; j <= ACE; j++)
        {
            cards[i * 6 + j - 7] = Card(static_cast<Rank>(j), static_cast<Suit>(i));
        }
    }
    next = 0;
}

Pack::Pack(std::istream &pack_input)
{
    for (int i = 0; i < PACK_SIZE; i++)
    {
        pack_input >> cards[i];
    }
    next = 0;
}

Card Pack::deal_one()
{
    Card card = cards[next];
    next++;
    return card;
}

void Pack::reset()
{
    next = 0;
}

void Pack::shuffle()
{
    std::array<Card, PACK_SIZE> cards2 = std::array<Card, PACK_SIZE>();
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < PACK_SIZE / 2; j++)
        {
            cards2[2 * j + 1] = cards[j];
            cards2[2 * j] = cards[j + PACK_SIZE / 2];
        }
        for (int k = 0; k < PACK_SIZE; k++)
        {
            cards[k] = cards2[k];
        }
    }
    reset();
}

bool Pack::empty() const
{
    return next == PACK_SIZE;
}