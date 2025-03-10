#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>
#include "Player.hpp"

using namespace std;

class SimplePlayer : public Player
{
public:
    SimplePlayer(const std::string &name) : name(name) {}

    const std::string &get_name() const override
    {
        return name;
    };

    void add_card(const Card &c) override
    {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const override
    {
        int face_count = 0;

        if (round == 1)
        {
            for (Card c : hand)
            {
                if ((c.is_face_or_ace() && c.is_trump(upcard.get_suit())) ||
                    c.is_right_bower(upcard.get_suit()) ||
                    c.is_left_bower(upcard.get_suit()))
                {
                    face_count++;
                }
            }
            if (face_count >= 2)
            {
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        else if (round == 2)
        {
            Suit next_suit = Suit_next(upcard.get_suit());
            face_count = 0;

            for (Card c : hand)
            {
                if ((c.is_face_or_ace() && c.is_trump(next_suit)) ||
                    c.is_right_bower(next_suit) ||
                    c.is_left_bower(next_suit))
                {
                    face_count++;
                }
            }

            if (is_dealer || face_count >= 1)
            {
                order_up_suit = next_suit;
                return true;
            }

            return false;
        }
        else
        {
            cout << "Invalid round number" << endl;
            assert(false);
        }
    }

    void add_and_discard(const Card &upcard) override
    {
        assert(hand.size() > 0);
        hand.push_back(upcard);
        int index_lowest = 0;
        for (int i = 0; i < hand.size(); i++)
        {
            if (!Card_less(hand[index_lowest], hand[i], upcard.get_suit()))
            {
                index_lowest = i;
            }
        }
        hand.erase(hand.begin() + index_lowest);
    };

    Card lead_card(Suit trump) override
    {
        Card best_card = hand[0];
        bool found_non_trump = false;
        for (const Card &card : hand)
        {
            if (!card.is_trump(trump))
            {
                if (!found_non_trump || card > best_card)
                {
                    best_card = card;
                    found_non_trump = true;
                }
            }
        }
        if (!found_non_trump)
        {
            best_card = hand[0];
            for (const Card &card : hand)
            {
                if (Card_less(best_card, card, trump))
                {
                    best_card = card;
                }
            }
        }

        hand.erase(remove(hand.begin(), hand.end(), best_card), hand.end());

        return best_card;
    }

    Card play_card(const Card &led_card, Suit trump) override
    {
        int best_index = -1;

        for (size_t i = 0; i < hand.size(); i++)
        {
            if (hand[i].get_suit(trump) == led_card.get_suit(trump))
            {
                if (best_index == -1 || !Card_less(hand[i], hand[best_index], trump))
                {
                    best_index = i;
                }
            }
        }

        if (best_index == -1)
        {
            best_index = 0;
            for (size_t i = 1; i < hand.size(); i++)
            {
                if (Card_less(hand[i], hand[best_index], trump))
                {
                    best_index = i;
                }
            }
        }

        Card best_card = hand[best_index];
        hand.erase(hand.begin() + best_index);
        return best_card;
    }

private:
    string name;
    vector<Card> hand;
}; // end of class SimplePlayer

////////////////////////////////////////////////////////////////////////

class HumanPlayer : public Player
{
public:
    HumanPlayer(const std::string &name) : name(name) {}

    const std::string &get_name() const override
    {
        return name;
    };

    void add_card(const Card &c) override
    {
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const override
    {
        assert(round == 1 || round == 2);
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

        string decision;
        cin >> decision;

        if (decision != "pass")
        {
            order_up_suit = string_to_suit(decision);
            return true;
        }
        else
        {
            return false;
        }
    }

    void add_and_discard(const Card &upcard) override
    {
        hand.push_back(upcard);
        print_hand();
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard: ";

        int discard_index;
        cin >> discard_index;

        if (discard_index == -1)
        {
            hand.pop_back(); // Remove the upcard
            sort(hand.begin(), hand.end());
        }
        else
        {
            assert(discard_index >= 0 && discard_index < hand.size());
            hand.erase(hand.begin() + discard_index);
        }
    }

    Card lead_card(Suit trump) override
    {
        assert(hand.size() >= 1);
        print_hand();
        cout << "Human player " << name << ", please select a card: ";

        int card_index;
        cin >> card_index;

        assert(card_index >= 0 && card_index < hand.size());
        Card c = hand[card_index];
        hand.erase(hand.begin() + card_index);
        return c;
    }

    Card play_card(const Card &led_card, Suit trump) override
    {
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        string decision;
        cin >> decision;
        int card_index = stoi(decision);
        assert(card_index >= 0 && card_index < hand.size());
        Card c = hand[card_index];
        hand.erase(hand.begin() + card_index);
        return c;
    }

private:
    string name;
    vector<Card> hand;

    void print_hand() const
    {
        for (size_t i = 0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
                 << "[" << i << "] " << hand[i] << "\n";
    }

}; // end of class HumanPlayer

Player *Player_factory(const std::string &name, const std::string &strategy)
{
    if (strategy == "Simple")
    {
        return new SimplePlayer(name);
    }
    else if (strategy == "Human")
    {
        return new HumanPlayer(name);
    }
    else
    {
        assert(false);
    }
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << p.get_name();
    return os;
}
