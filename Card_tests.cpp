#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_card_constructor)
{
    struct TestCase
    {
        Rank rank;
        Suit suit;
    };

    // Define all test cases
    TestCase test_cases[] = {
        {ACE, HEARTS}, {ACE, CLUBS}, {ACE, DIAMONDS}, {ACE, SPADES}, {KING, HEARTS}, {KING, CLUBS}, {KING, DIAMONDS}, {KING, SPADES}, {QUEEN, HEARTS}, {QUEEN, CLUBS}, {QUEEN, DIAMONDS}, {QUEEN, SPADES}, {JACK, HEARTS}, {JACK, CLUBS}, {JACK, DIAMONDS}, {JACK, SPADES}, {TEN, HEARTS}, {TEN, CLUBS}, {TEN, DIAMONDS}, {TEN, SPADES}, {NINE, HEARTS}, {NINE, CLUBS}, {NINE, DIAMONDS}, {NINE, SPADES}, {EIGHT, HEARTS}, {EIGHT, CLUBS}, {EIGHT, DIAMONDS}, {EIGHT, SPADES}, {SEVEN, HEARTS}, {SEVEN, CLUBS}, {SEVEN, DIAMONDS}, {SEVEN, SPADES}, {SIX, HEARTS}, {SIX, CLUBS}, {SIX, DIAMONDS}, {SIX, SPADES}, {FIVE, HEARTS}, {FIVE, CLUBS}, {FIVE, DIAMONDS}, {FIVE, SPADES}, {FOUR, HEARTS}, {FOUR, CLUBS}, {FOUR, DIAMONDS}, {FOUR, SPADES}, {THREE, HEARTS}, {THREE, CLUBS}, {THREE, DIAMONDS}, {THREE, SPADES}, {TWO, HEARTS}, {TWO, CLUBS}, {TWO, DIAMONDS}, {TWO, SPADES}};

    // Loop through each test case
    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i)
    {
        Card c(test_cases[i].rank, test_cases[i].suit);
        ASSERT_EQUAL(c.get_rank(), test_cases[i].rank);
        ASSERT_EQUAL(c.get_suit(), test_cases[i].suit);
    }
}

TEST(test_card_is_face_or_ace)
{
    struct TestCase
    {
        Rank rank;
        Suit suit;
        bool expected;
    };

    TestCase test_cases[] = {
        {ACE, HEARTS, true}, {KING, CLUBS, true}, {QUEEN, DIAMONDS, true}, {JACK, SPADES, true}, {TEN, HEARTS, false}, {NINE, CLUBS, false}, {EIGHT, DIAMONDS, false}, {SEVEN, SPADES, false}, {SIX, HEARTS, false}, {FIVE, CLUBS, false}, {FOUR, DIAMONDS, false}, {THREE, SPADES, false}, {TWO, HEARTS, false}};

    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i)
    {
        Card c(test_cases[i].rank, test_cases[i].suit);
        ASSERT_EQUAL(c.is_face_or_ace(), test_cases[i].expected);
    }
}

TEST(test_card_less_than_operator)
{
    Card ace_hearts(ACE, HEARTS);
    Card ace_diamonds(ACE, DIAMONDS);
    Card king_spades(KING, SPADES);
    Card king_hearts(KING, HEARTS);
    Card ten_clubs(TEN, CLUBS);
    Card nine_clubs(NINE, CLUBS);

    ASSERT_TRUE(king_spades < ace_hearts);
    ASSERT_TRUE(ten_clubs < king_hearts);
    ASSERT_TRUE(nine_clubs < ten_clubs);
    ASSERT_FALSE(ace_diamonds < ace_hearts);
}

TEST(test_card_is_right_bower)
{
    Card jack_spades(JACK, SPADES);
    Card jack_hearts(JACK, HEARTS);
    Card queen_spades(QUEEN, SPADES);
    Card ten_spades(TEN, SPADES);

    ASSERT_TRUE(jack_spades.is_right_bower(SPADES));
    ASSERT_TRUE(jack_hearts.is_right_bower(HEARTS));
    ASSERT_FALSE(queen_spades.is_right_bower(SPADES));
    ASSERT_FALSE(ten_spades.is_right_bower(SPADES));
}

TEST_MAIN()
