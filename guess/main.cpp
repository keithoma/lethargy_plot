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

class Card {
  public:
    Suit suit;
    Rank rank;
    Card(Suit _suit, Rank _rank);
};

Card::Card(Suit _suit, Rank _rank) {
    suit = _suit;
    rank = _rank;
}

int main() {
    return 0;
}