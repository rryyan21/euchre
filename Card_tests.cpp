#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(Card_constructor)
{
    Card c1;
    ASSERT_EQUAL(c1.get_rank(), TWO);
    ASSERT_EQUAL(c1.get_suit(), SPADES);
    Card c2(ACE, HEARTS);
    ASSERT_EQUAL(c2.get_rank(), ACE);
    ASSERT_EQUAL(c2.get_suit(), HEARTS);
}

TEST(Card_is_face_or_ace)
{
    Card c1(TWO, SPADES);
    ASSERT_FALSE(c1.is_face_or_ace());
    Card c2(JACK, SPADES);
    ASSERT_TRUE(c2.is_face_or_ace());
    Card c3(QUEEN, SPADES);
    ASSERT_TRUE(c3.is_face_or_ace());
    Card c4(KING, SPADES);
    ASSERT_TRUE(c4.is_face_or_ace());
    Card c5(ACE, SPADES);
    ASSERT_TRUE(c5.is_face_or_ace());
}

TEST(test_card_is_right_bower)
{
    Card c1;
    Card c2(TEN, CLUBS);
    Card c3(JACK, Suit_next(HEARTS));
    Card c4(ACE, Suit_next(CLUBS));
    Card c5(NINE, CLUBS);
    Card c6(JACK, DIAMONDS);
    Card c7(JACK, HEARTS);

    ASSERT_FALSE(c1.is_right_bower(DIAMONDS));
    ASSERT_TRUE(c6.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c7.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c2.is_right_bower(DIAMONDS));
    ASSERT_TRUE(c3.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c4.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c5.is_right_bower(DIAMONDS));
}

TEST(test_card_is_left_bower)
{
    Card c1;
    Card c2(TEN, CLUBS);
    Card c3(JACK, Suit_next(HEARTS));
    Card c4(ACE, Suit_next(CLUBS));
    Card c5(NINE, CLUBS);
    Card c6(JACK, DIAMONDS);
    Card c7(JACK, HEARTS);

    ASSERT_FALSE(c1.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c2.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c3.is_left_bower(DIAMONDS));
    ASSERT_TRUE(c3.is_left_bower(HEARTS));
    ASSERT_FALSE(c4.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c5.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c6.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c7.is_left_bower(HEARTS));
}

TEST(test_card_is_trump)
{
    Card c1;
    Card c2(TEN, CLUBS);
    Card c3(JACK, Suit_next(HEARTS));
    Card c4(ACE, Suit_next(CLUBS));
    Card c5(NINE, CLUBS);
    Card c6(JACK, DIAMONDS);
    Card c7(JACK, HEARTS);

    ASSERT_FALSE(c1.is_trump(DIAMONDS));
    ASSERT_FALSE(c2.is_trump(DIAMONDS));
    ASSERT_TRUE(c3.is_trump(DIAMONDS));
    ASSERT_FALSE(c4.is_trump(CLUBS));
    ASSERT_FALSE(c5.is_trump(DIAMONDS));
    ASSERT_TRUE(c6.is_trump(DIAMONDS));
    ASSERT_TRUE(c7.is_trump(DIAMONDS));
}

TEST(Card_Card_less)
{
    Card c2(TEN, CLUBS);
    Card c3(JACK, Suit_next(HEARTS));
    Card c4(ACE, Suit_next(CLUBS));
    Card c5(NINE, CLUBS);
    Card c6(JACK, SPADES);
    Card c7(JACK, HEARTS);

    ASSERT_TRUE(Card_less(c2, c3, SPADES));
}

TEST(Card_Card_less_led)
{
    Card c2(TEN, CLUBS);
    Card c3(JACK, Suit_next(HEARTS));
    Card c4(ACE, Suit_next(CLUBS));
    Card c5(NINE, CLUBS);
    Card c6(JACK, SPADES);
    Card c7(JACK, HEARTS);

    ASSERT_FALSE(Card_less(c2, c3, c5, SPADES));
    ASSERT_TRUE(Card_less(c2, c6, c5, SPADES));
}

TEST(test_card_comparators)
{
    Card c1;
    Card c2(TEN, CLUBS);
    Card c3(JACK, Suit_next(HEARTS));
    Card c4(ACE, Suit_next(CLUBS));
    Card c5(NINE, CLUBS);
    Card c6(JACK, SPADES);
    Card c7(JACK, HEARTS);

    ASSERT_TRUE(c1 < c2);
    ASSERT_FALSE(c2 < c5);
    ASSERT_TRUE(c3 < c4);
    ASSERT_FALSE(c4 < c5);
    ASSERT_TRUE(c5 < c6);
    ASSERT_TRUE(c6 < c7);

    ASSERT_TRUE(c1 <= c2);
    ASSERT_FALSE(c2 <= c5);
    ASSERT_TRUE(c3 <= c4);
    ASSERT_FALSE(c4 <= c5);
    ASSERT_TRUE(c5 <= c6);
    ASSERT_TRUE(c6 <= c7);
    ASSERT_TRUE(c2 <= c2);

    ASSERT_FALSE(c1 > c2);
    ASSERT_TRUE(c2 > c5);
    ASSERT_FALSE(c3 > c4);
    ASSERT_TRUE(c4 > c5);
    ASSERT_FALSE(c5 > c6);
    ASSERT_FALSE(c6 > c7);

    ASSERT_TRUE(c1 != c2);
}

TEST_MAIN()