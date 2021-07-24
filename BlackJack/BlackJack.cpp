#include <iostream>
#include <vector>

using namespace std;

class Card {
public:
    enum suit { SPADES, HEARTS, CLUBS, DIAMONDS };
    enum rnk { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

    Card(rnk rk = ACE, suit st = SPADES, bool ps = true) : cardRank(rk), cardSuit(st), cardPos(ps) {
    }

    void Flip() {
        cardPos = !cardPos;
    }

    int GetValue() const {
        return cardPos * (cardRank > 10 ? 10 : cardRank);
    }
protected:
    bool cardPos;
    suit cardSuit;
    rnk cardRank;
};

int main()
{
    return 0;
}