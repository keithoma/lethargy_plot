#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>


using namespace std;

enum class Suit {
    spade,
    heart,
    clover,
    diamond
};

enum class Rank {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    J,
    Q,
    K,
    A
};

class Deck {

  private:
    const vector<Suit> suit = { Suit::spade,
                                Suit::heart,
                                Suit::clover,
                                Suit::diamond };

    const vector<Rank> rank = { Rank::two,
                                Rank::three,
                                Rank::four,
                                Rank::five,
                                Rank::six,
                                Rank::seven,
                                Rank::eight,
                                Rank::nine,
                                Rank::ten,
                                Rank::J,
                                Rank::Q,
                                Rank::K,
                                Rank::A };

    array<pair<Suit, Rank>, 53> deck;

  public:
    void sort_deck();
    void shuffle_deck();
    Deck();

    array<pair<Suit, Rank>, 53> give_deck() { return deck; }

};

void Deck::sort_deck() {
    for ( size_t i = 0; i < suit.size(); ++i ) {
        for ( size_t j = 0; j < rank.size(); ++j ) {
            unsigned index = 13 * i + j + 1;
            deck[index] = make_pair(suit[i], rank[j]);
        }
    }
}

void Deck::shuffle_deck() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle ( deck.begin(), deck.end(), std::default_random_engine(seed) );
}

Deck::Deck() {
    sort_deck();
    shuffle_deck();
}

string suit_string(Suit suit) {
    switch (suit) {
        case Suit::spade : return "spade";
        case Suit::heart : return "heart";
        case Suit::clover : return "clover";
        case Suit::diamond : return "diamond";
    }
}

string rank_string(Rank rank) {
    switch (rank) {
        case Rank::two : return "2";
        case Rank::three : return "3";
        case Rank::four : return "4";
        case Rank::five : return "5";
        case Rank::six : return "6";
        case Rank::seven : return "7";
        case Rank::eight : return "8";
        case Rank::nine : return "9";
        case Rank::ten : return "10";
        case Rank::J : return "J";
        case Rank::Q : return "Q";
        case Rank::K : return "K";
        case Rank::A : return "A";
    }
}

int main() {
    Deck main_deck;
    cout << "The first card is " << suit_string(main_deck.give_deck[0]->first) << " " << rank_string(main_deck.give_deck[0]->second);
    return 0;
}