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

TEST(test_player_name)
{
    Player *Ryan = Player_factory("Ryan", "Simple");
    ASSERT_EQUAL("Ryan", Ryan->get_name());

    ostringstream oss;
    oss << *Ryan;
    ASSERT_EQUAL("Ryan", oss.str());

    delete Ryan;
}

TEST(p_make_trump_1)
{
    Player *costco = Player_factory("Costco", "Simple");
    costco->add_card(Card(NINE, SPADES));
    costco->add_card(Card(TEN, SPADES));
    costco->add_card(Card(JACK, SPADES));
    costco->add_card(Card(QUEEN, SPADES));
    costco->add_card(Card(KING, SPADES));
    Suit trump;
    bool orderup = costco->make_trump(Card(NINE, SPADES), false, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete costco;
}

TEST(p_make_trump_2)
{
    Player *bob = Player_factory("bob", "Simple");
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(TEN, DIAMONDS));
    Suit trump;
    bool orderup = bob->make_trump(Card(NINE, DIAMONDS), false, 1, trump);
    ASSERT_FALSE(orderup);

    delete bob;
}

TEST(p_make_trump_3)
{
    Player *Alex = Player_factory("Alex", "Simple");
    Alex->add_card(Card(TEN, SPADES));
    Alex->add_card(Card(JACK, SPADES));
    Alex->add_card(Card(QUEEN, SPADES));
    Alex->add_card(Card(KING, SPADES));
    Alex->add_card(Card(NINE, HEARTS));

    Suit trump;
    bool orderup = Alex->make_trump(Card(NINE, HEARTS), false, 2, trump);
    ASSERT_FALSE(orderup);

    delete Alex;
}

TEST(p_make_trump_4)
{
    Player *vaman = Player_factory("Vaman", "Simple");
    vaman->add_card(Card(JACK, DIAMONDS));
    vaman->add_card(Card(JACK, DIAMONDS));
    vaman->add_card(Card(TEN, HEARTS));
    Suit trump;
    bool orderup = vaman->make_trump(Card(NINE, SPADES), true, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);

    delete vaman;
}

TEST(p_make_trump_5)
{
    Player *manny = Player_factory("manny", "Simple");
    manny->add_card(Card(JACK, DIAMONDS));
    manny->add_card(Card(TEN, HEARTS));
    Suit trump;
    bool orderup = manny->make_trump(Card(NINE, HEARTS), false, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, DIAMONDS);

    delete manny;
}

TEST(p_lead_card_1)
{
    Player *Jarvis = Player_factory("Jarvis", "Simple");
    Jarvis->add_card(Card(NINE, SPADES));
    Jarvis->add_card(Card(ACE, SPADES));
    Jarvis->add_card(Card(KING, SPADES));
    Card led_card = Jarvis->lead_card(SPADES);
    ASSERT_EQUAL(led_card, Card(ACE, SPADES));
    delete Jarvis;
}

TEST(p_lead_card_2)
{
    Player *kevin = Player_factory("kevin", "Simple");
    kevin->add_card(Card(NINE, DIAMONDS));
    kevin->add_card(Card(ACE, DIAMONDS));
    kevin->add_card(Card(KING, DIAMONDS));
    kevin->add_card(Card(JACK, DIAMONDS));
    Card led_card = kevin->lead_card(DIAMONDS);
    ASSERT_EQUAL(led_card, Card(JACK, DIAMONDS));
    delete kevin;
}

TEST(p_lead_card_3)
{
    Player *Agustin = Player_factory("Agustin", "Simple");
    Agustin->add_card(Card(JACK, DIAMONDS));
    Agustin->add_card(Card(TEN, SPADES));
    Agustin->add_card(Card(NINE, CLUBS));
    Agustin->add_card(Card(ACE, CLUBS));
    Agustin->add_card(Card(KING, CLUBS));
    Card led_card = Agustin->lead_card(CLUBS);
    ASSERT_EQUAL(led_card, Card(JACK, DIAMONDS));
    delete Agustin;
}

TEST(p_play_card)
{
    Player *kosta = Player_factory("kosta", "Simple");
    kosta->add_card(Card(JACK, HEARTS));
    kosta->add_card(Card(KING, HEARTS));
    kosta->add_card(Card(NINE, DIAMONDS));
    kosta->add_card(Card(ACE, DIAMONDS));
    kosta->add_card(Card(KING, DIAMONDS));
    Card played_card = kosta->play_card(Card(TEN, DIAMONDS), HEARTS);
    ASSERT_EQUAL(played_card, Card(ACE, DIAMONDS));
    delete kosta;
}

TEST(p_play_card_2)
{
    Player *terry = Player_factory("terry", "Simple");
    terry->add_card(Card(JACK, CLUBS));
    terry->add_card(Card(KING, SPADES));
    Card played_card = terry->play_card(Card(TEN, CLUBS), HEARTS);
    ASSERT_EQUAL(played_card, Card(JACK, CLUBS));
    delete terry;
}

TEST(test_player_add_and_discard)
{
    Player *Vicky = Player_factory("vicky", "Simple");
    Vicky->add_card(Card(TEN, SPADES));
    Vicky->add_and_discard(Card(KING, SPADES));
    Card played_card = Vicky->play_card(Card(JACK, SPADES), HEARTS);
    ASSERT_EQUAL(played_card, Card(KING, SPADES));
    delete Vicky;
}

TEST(p_add_and_discard_2)
{
    Player *Raghav = Player_factory("Raghav", "Simple");

    Raghav->add_card(Card(NINE, DIAMONDS));
    Raghav->add_card(Card(KING, HEARTS));
    Raghav->add_card(Card(QUEEN, CLUBS));
    Raghav->add_card(Card(JACK, SPADES));
    Raghav->add_card(Card(ACE, DIAMONDS));
    Raghav->add_and_discard(Card(TEN, DIAMONDS));
    Card lead_card = Raghav->lead_card(DIAMONDS);

    ASSERT_NOT_EQUAL(lead_card, Card(JACK, SPADES));

    delete Raghav;
}

TEST(p_add_and_discard_3)
{
    Player *Vihaan = Player_factory("Vihaan", "Simple");
    Vihaan->add_card(Card(ACE, SPADES));
    Vihaan->add_and_discard(Card(NINE, SPADES));
    Card played_card = Vihaan->play_card(Card(NINE, SPADES), HEARTS);
    ASSERT_EQUAL(played_card, Card(ACE, SPADES));

    delete Vihaan;
}

TEST(p_add_and_discard_4)
{
    Player *mahee = Player_factory("mahee", "Simple");

    mahee->add_card(Card(NINE, HEARTS));
    mahee->add_card(Card(NINE, CLUBS));
    mahee->add_card(Card(KING, CLUBS));
    Card upcard(TEN, DIAMONDS);
    mahee->add_and_discard(upcard);
    Card played_card = mahee->play_card(Card(TEN, SPADES), SPADES);

    ASSERT_EQUAL(played_card, Card(NINE, CLUBS));

    delete mahee;
}

TEST(p_add_and_discard_5)
{
    Player *stephen = Player_factory("stephen", "Simple");
    stephen->add_card(Card(JACK, DIAMONDS));
    stephen->add_card(Card(NINE, DIAMONDS));
    stephen->add_and_discard(Card(KING, DIAMONDS));
    Card played_card = stephen->play_card(Card(NINE, HEARTS), DIAMONDS);
    ASSERT_EQUAL(played_card, Card(KING, DIAMONDS));
    delete stephen;
}

TEST(p_add_and_discard_6)
{
    Player *josh = Player_factory("josh", "Simple");

    josh->add_card(Card(NINE, SPADES));
    josh->add_card(Card(JACK, SPADES));
    josh->add_card(Card(TEN, CLUBS));
    josh->add_card(Card(QUEEN, SPADES));
    josh->add_card(Card(KING, SPADES));
    josh->add_and_discard(Card(NINE, HEARTS));
    Card played_card = josh->play_card(Card(JACK, DIAMONDS), HEARTS);
    ASSERT_EQUAL(played_card, Card(NINE, HEARTS));
    bool has_upcard = false;
    for (int i = 0; i < 4; i++)
    {
        Card played_card = josh->play_card(Card(JACK, DIAMONDS), HEARTS);
        if (played_card == Card(NINE, HEARTS))
        {
            has_upcard = true;
            break;
        }
    }
    ASSERT_FALSE(has_upcard);
    delete josh;
}

TEST_MAIN()