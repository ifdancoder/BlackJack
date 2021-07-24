#include <iostream>
#include <vector>

using namespace std;

class Card {
public:
    enum suit { SPADES, HEARTS, CLUBS, DIAMONDS };
    enum rnk { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

    Card(rnk cardRank = ACE, suit cardSuit = SPADES, bool cardPos = true) : cardRank(cardRank), cardSuit(cardSuit), cardPos(cardPos) {
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

class Hand {
public:
    Hand() {
        cardsArr.reserve(7);
    };
    virtual ~Hand() {
        Clear();
    };
    void Add(Card* pCard) {
        cardsArr.push_back(pCard);
    }
    void Clear() {
        for (int i = 0; i < cardsArr.size(); i++) {
            delete cardsArr[i];
            cardsArr[i] = nullptr;
        }
        cardsArr.clear();
    }
    int GetTotal() const {
        int amount = 0;
        bool ace = false;
        for (int i = 0; i < cardsArr.size(); i++) {
            amount += cardsArr[i]->GetValue();
            if (cardsArr[i]->GetValue() == Card::ACE) {
                ace++;
            }
        }
        return amount + 10 * (amount <= 11 && ace);
    }
protected:
    vector<Card*> cardsArr;
};

class GenericPlayer : public Hand {
public:
    GenericPlayer(const string& const name="") : name(name) {
    }
    virtual ~GenericPlayer() {
    }
    virtual bool IsHitting() const = 0;
    bool isBoosted() const {
        return GetTotal() > 21;
    }
    void Bust() const {
        cout << name << " busts" << endl;
    }
protected:
    string name;
};

int main()
{
    return 0;
}