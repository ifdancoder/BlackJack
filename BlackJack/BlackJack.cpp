#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Card {
public:
    enum suit { SPADES, HEARTS, CLUBS, DIAMONDS };
    enum rnk { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    string ranks[14] = { "Error", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    char suits[4] = { 6, 3, 5, 4 };

    Card(rnk cardRank = ACE, suit cardSuit = SPADES, bool cardPos = true) : cardRank(cardRank), cardSuit(cardSuit), cardPos(cardPos) {
    }
    bool getCardPos() const {
        return cardPos;
    }
    suit getCardSuit() const {
        return cardSuit;
    }
    rnk getCardRank() const {
        return cardRank;
    }
    void Flip() {
        cardPos = !cardPos;
    }
    int GetValue() const {
        return cardPos * (cardRank > 10 ? 10 : cardRank);
    }
    friend ostream& operator<<(ostream& otp, const Card& card);
protected:
    bool cardPos;
    suit cardSuit;
    rnk cardRank;
};

ostream& operator<<(ostream& otp, const Card& card)
{
    if (card.cardPos)
    {
        otp << "********\n* " << card.ranks[card.cardRank] << (card.ranks[card.cardRank].size() > 1 ? " " : "  ") << card.suits[card.cardSuit] << " *\n********\n";
    }
    else
    {
        otp << "********\n********\n********\n";
    }
    return otp;
}

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
    friend ostream& operator<<(ostream& otp, const GenericPlayer& gp);
protected:
    string name;
};

ostream& operator<<(ostream& otp, const GenericPlayer& gp)
{
    otp << gp.name << " (Total is " << gp.GetTotal() << "):\n";
    if (gp.cardsArr.size()) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < gp.cardsArr.size(); j++) {
                if (gp.cardsArr[j]->getCardPos()) {
                    switch (i) {
                        case 0:
                            cout << "******** ";
                            break;
                        case 1:
                            cout << "* " << gp.cardsArr[i]->ranks[gp.cardsArr[j]->getCardRank()] << (gp.cardsArr[j]->ranks[gp.cardsArr[j]->getCardRank()].size() > 1 ? " " : "  ") << gp.cardsArr[i]->suits[gp.cardsArr[j]->getCardSuit()] << " * ";
                            break;
                        case 2:
                            cout << "******** ";
                            break;
                    }
                }
                else {
                    cout << "******** ";
                }
            }
            cout << endl;
        }
    }
    else
    {
        otp << "<empty>" << endl;
    }
    return otp;
}

class Player : public GenericPlayer
{
public:
    Player(const string& name = "") : GenericPlayer(name) {
    }
    virtual ~Player() {
    }
    virtual bool IsHitting() const {
        cout << name << ", do you want a hit (Y/N)? ";
        char tmp;
        cin >> tmp;
        return tmp == 'Y' || tmp == 'y';
    }
    void Win() const {
        cout << name << " wins" << endl;
    }
    void Lose() const {
        cout << name << " loses" << endl;
    }
    void Push() const {
        cout << name << " pushes" << endl;
    }
};

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) {
    }
    virtual ~House() {
    }
    virtual bool IsHitting() const {
        return GetTotal() <= 16;
    }
    void FlipFirstCard() {
        if (cardsArr.size()) {
            cardsArr[0]->Flip();
        }
        else {
            cout << "No card to flip" << endl;
        }
    }
};

int main()
{
    Player p("Daniel");
    cout << p;

    Card a(Card::TEN, Card::DIAMONDS, 1);
    Card b(Card::TEN, Card::HEARTS, 0);
    Card c(Card::ACE, Card::SPADES, 1);

    p.Add(&a);
    p.Add(&b);
    p.Add(&c);

    cout << p;
    return 0;
}