#include <iostream>
#include <fstream>
#include <vector>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"

using namespace std;

class Game
{
public:
    Game(
        ifstream *pack_in,
        bool should_shuffle,
        int points_to_win,
        vector<Player *> players)
        : should_shuffle(should_shuffle), points_to_win(points_to_win), players(players)
    {
        pack = Pack(*pack_in);
    }

    void play()
    {
        while (true)
        {
            cout << "Hand " << hand << endl;
            setup();

            int trump_order_upper = make_trump(hand % 4);
            cout << endl;

            trick(hand % 4, trump_order_upper);
            cout << endl;

            for (int i = 0; i <= 1; i++) // Check team scores
            {
                if (scores[i] >= points_to_win)
                {
                    cout << players[i]->get_name() << " and "
                         << players[i + 2]->get_name() << " win!" << endl;
                    return;
                }
            }
            hand++;
        }
    }

    void setup()
    {
        pack.reset();
        if (should_shuffle)
        {
            pack.shuffle();
        }

        deal_cards(hand % 4);

        upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
    }

    void deal_cards(int dealer)
    {
        cout << players[dealer]->get_name() << " deals" << endl;

        for (int i = 1; i < 5; i++)
        {
            for (int j = 0; j < (i % 2) + 2; j++)
            {
                players[(dealer + i) % 4]->add_card(pack.deal_one());
            }
        }

        for (int i = 1; i < 5; i++)
        {
            for (int j = 0; j < 3 - (i % 2); j++)
            {
                players[(dealer + i) % 4]->add_card(pack.deal_one());
            }
        }
    }

    int make_trump(int dealer)
    {
        for (int round = 1; round <= 2; round++)
        {
            for (int j = (dealer + 1) % 4; j < ((dealer + 1) % 4) + 4; j += 1)
            {
                if (players[j % 4]->make_trump(
                        upcard, ((j % 4) == dealer),
                        round, trump))
                {
                    cout << players[j % 4]->get_name()
                         << " orders up " << trump << endl;
                    if (round == 1)
                        players[dealer]->add_and_discard(upcard);
                    return j % 4;
                }
                cout << players[j % 4]->get_name() << " passes" << endl;
            }
        }
        return -1;
    }

    void trick(int dealer, int trump_order_upper)
    {
        int lead_card_index = (dealer + 1) % 4;
        vector<int> trick_winners{0, 0, 0, 0};

        for (int i = 0; i < 5; i++)
        {
            Card lead_card = players[lead_card_index]->lead_card(trump);
            cout << lead_card << " led by "
                 << players[lead_card_index]->get_name() << endl;

            Card bestCard = lead_card;
            int bestIndex = lead_card_index;

            for (int j = lead_card_index + 1; j < lead_card_index + 4; j++)
            {

                Card played_card = players[j % 4]->play_card(lead_card, trump);
                cout << played_card << " played by "
                     << players[j % 4]->get_name() << endl;

                if (Card_less(bestCard, played_card, lead_card, trump))
                {
                    bestCard = played_card;
                    bestIndex = j % 4;
                }
            }

            lead_card_index = bestIndex;
            trick_winners[bestIndex]++;
            cout << players[bestIndex]->get_name() << " takes the trick" << endl;
            cout << endl;
        }

        calculate_scores(trick_winners, trump_order_upper);
    }

    void calculate_scores(vector<int> trick_winners, int trump_order_upper)
    {
        for (int i = 0; i <= 1; i++)
        {
            if (trick_winners[i] + trick_winners[i + 2] == 3 ||
                trick_winners[i] + trick_winners[i + 2] == 4)
            {
                if (i == trump_order_upper || i + 2 == trump_order_upper)
                {
                    cout << players[i]->get_name() << " and "
                         << players[i + 2]->get_name() << " win the hand" << endl;
                    scores[i] += 1;
                    scores[i + 2] += 1;
                }
                else
                {
                    cout << players[i]->get_name() << " and "
                         << players[i + 2]->get_name() << " win the hand" << endl;
                    scores[i] += 2;
                    scores[i + 2] += 2;
                    cout << "euchred!" << endl;
                }
            }
            if (trick_winners[i] + trick_winners[i + 2] == 5)
            {
                if (i == trump_order_upper || i + 2 == trump_order_upper)
                {
                    cout << players[i]->get_name() << " and "
                         << players[i + 2]->get_name() << " win the hand" << endl;
                    scores[i] += 2;
                    scores[i + 2] += 2;
                    cout << "march!" << endl;
                }
                else
                {
                    cout << players[i]->get_name() << " and "
                         << players[i + 2]->get_name() << " win the hand" << endl;
                    scores[i] += 2;
                    scores[i + 2] += 2;
                    cout << "euchred!" << endl;
                }
            }
        }

        for (int i = 0; i <= 1; i++)
        {
            cout << players[i]->get_name() << " and "
                 << players[i + 2]->get_name() << " have "
                 << scores[i] << " points" << endl;
        }
    }

    void stop()
    {
        for (size_t i = 0; i < players.size(); i++)
        {
            delete players[i];
        }
    }

private:
    Pack pack;
    bool should_shuffle;
    int points_to_win;
    vector<Player *> players;
    int hand;
    Card upcard;
    Suit trump;
    vector<int> scores = {0, 0, 0, 0};
}; // EOC

int main(int argc, char **argv)
{
    if (argc != 12)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    string pack_filename = argv[1];
    ifstream pack_file(pack_filename);
    if (!pack_file.is_open())
    {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    bool shuffle = (string(argv[2]) == "shuffle");
    int points_to_win = stoi(argv[3]);

    cout << "./euchre.exe "
         << pack_filename << " "
         << argv[2] << " "
         << points_to_win << " "
         << argv[4] << " "
         << argv[5] << " "
         << argv[6] << " "
         << argv[7] << " "
         << argv[8] << " "
         << argv[9] << " "
         << argv[10] << " "
         << argv[11] << " " << endl;

    vector<Player *> players;
    players.push_back(Player_factory(argv[4], argv[5]));
    players.push_back(Player_factory(argv[6], argv[7]));
    players.push_back(Player_factory(argv[8], argv[9]));
    players.push_back(Player_factory(argv[10], argv[11]));

    Game game(&pack_file, shuffle, points_to_win, players);
    game.play();
    game.stop();

    return 0;
}