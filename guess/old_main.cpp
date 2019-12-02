#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
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

const vector<Suit> g_suit = { Suit::spade,
                              Suit::heart,
                              Suit::clover,
                              Suit::diamond };

const vector<Rank> g_rank = { Rank::two,
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

pair<Suit, Rank> g_deck [53];

void create_deck() {
    for ( size_t i = 0; i < g_suit.size(); ++i ) {
        for ( size_t j = 0; j < g_rank.size(); ++j ) {
            unsigned index = 13 * i + j + 1;
            g_deck[index] = make_pair(g_suit[i], g_rank[j]);
        }
    }
}

void shuffle_deck() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle ( g_deck.begin(), g_deck.end(), std::default_random_engine(seed) );
}

int main() {
    create_deck();
    shuffle_deck();

    cout << "Well, it's working.\n";
    return 0;
}