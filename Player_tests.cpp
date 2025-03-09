#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name)
{
    Player *alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_simple_player_make_trump_ryan)
{
    Player *ryan = Player_factory("Ryan", "Simple");
    ryan->add_card(Card(NINE, SPADES));
    ryan->add_card(Card(TEN, SPADES));
    ryan->add_card(Card(QUEEN, SPADES));
    ryan->add_card(Card(KING, SPADES));
    ryan->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = HEARTS; // Initialize to a known value
    bool orderup = ryan->make_trump(nine_spades, true, 1, trump);

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete ryan;
}

TEST(test_simple_player_lead_card_james)
{
    Player *james = Player_factory("James", "Simple");
    james->add_card(Card(NINE, SPADES));
    james->add_card(Card(TEN, SPADES));
    james->add_card(Card(QUEEN, SPADES));
    james->add_card(Card(KING, SPADES));
    james->add_card(Card(ACE, SPADES));

    james->add_and_discard(Card(NINE, HEARTS));

    Card card_led = james->lead_card(HEARTS);

    // Ensure expected highest non-trump card is led
    ASSERT_EQUAL(Card(ACE, SPADES), card_led);

    delete james;
}

TEST(test_simple_player_play_card_todd)
{
    Player *todd = Player_factory("Todd", "Simple");
    todd->add_card(Card(NINE, SPADES));
    todd->add_card(Card(TEN, SPADES));
    todd->add_card(Card(QUEEN, SPADES));
    todd->add_card(Card(KING, SPADES));
    todd->add_card(Card(ACE, SPADES));

    todd->add_and_discard(Card(NINE, HEARTS));

    Card card_played = todd->play_card(Card(NINE, HEARTS), HEARTS);

    // Ensure the expected card follows suit or the lowest card is played
    ASSERT_EQUAL(Card(NINE, SPADES), card_played);

    delete todd;
}

TEST(test_human_player_make_trump_ryan)
{
    Player *ryan = Player_factory("Ryan", "Human");
    ryan->add_card(Card(NINE, SPADES));
    ryan->add_card(Card(TEN, SPADES));
    ryan->add_card(Card(QUEEN, SPADES));
    ryan->add_card(Card(KING, SPADES));
    ryan->add_card(Card(ACE, SPADES));

    Card nine_spades(NINE, SPADES);
    Suit trump = HEARTS; // Initialize to a known value
    bool orderup = ryan->make_trump(nine_spades, true, 1, trump);

    // Human input might be needed here, but assuming default behavior
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete ryan;
}

TEST(test_human_player_lead_card_james)
{
    Player *james = Player_factory("James", "Human");
    james->add_card(Card(NINE, SPADES));
    james->add_card(Card(TEN, SPADES));
    james->add_card(Card(QUEEN, SPADES));
    james->add_card(Card(KING, SPADES));
    james->add_card(Card(ACE, SPADES));

    james->add_and_discard(Card(NINE, HEARTS));

    Card card_led = james->lead_card(HEARTS);

    ASSERT_EQUAL(Card(ACE, SPADES), card_led);

    delete james;
}

TEST(test_human_player_play_card_todd)
{
    Player *todd = Player_factory("Todd", "Human");
    todd->add_card(Card(NINE, SPADES));
    todd->add_card(Card(TEN, SPADES));
    todd->add_card(Card(QUEEN, SPADES));
    todd->add_card(Card(KING, SPADES));
    todd->add_card(Card(ACE, SPADES));

    todd->add_and_discard(Card(NINE, HEARTS));

    Card card_played = todd->play_card(Card(NINE, HEARTS), HEARTS);

    ASSERT_EQUAL(Card(NINE, SPADES), card_played);

    delete todd;
}

TEST(test_human_player_add_and_discard_ryan)
{
    Player *ryan = Player_factory("Ryan", "Human");
    ryan->add_card(Card(NINE, SPADES));
    ryan->add_card(Card(TEN, SPADES));
    ryan->add_card(Card(QUEEN, SPADES));
    ryan->add_card(Card(KING, SPADES));
    ryan->add_card(Card(ACE, SPADES));

    ryan->add_and_discard(Card(JACK, HEARTS));

    Card card_played = ryan->play_card(Card(NINE, HEARTS), HEARTS);

    ASSERT_EQUAL(Card(NINE, SPADES), card_played);

    delete ryan;
}

TEST(test_human_player_add_and_discard2_james)
{
    Player *james = Player_factory("James", "Human");
    james->add_card(Card(NINE, SPADES));
    james->add_card(Card(TEN, SPADES));
    james->add_card(Card(QUEEN, SPADES));
    james->add_card(Card(KING, SPADES));
    james->add_card(Card(ACE, SPADES));

    james->add_and_discard(Card(JACK, HEARTS));

    Card card_played = james->play_card(Card(NINE, HEARTS), HEARTS);

    ASSERT_EQUAL(Card(NINE, SPADES), card_played);

    delete james;
}

TEST_MAIN()
