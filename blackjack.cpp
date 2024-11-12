#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Card{
public:
  int rank, suite;

  Card(int inputRank, int inputSuite){
    rank = inputRank;
    suite = inputSuite;
  }

  void printCard() const {
    cout << "Rank: " << rank << ", Suite: " << suite << endl;
  }

  int getValue() const {
        if (rank > 10) {
            return 10;
        }
        return rank;
  }
};

class Hand{
public:
  vector <Card> cardsInHand;

  void addCard(Card &card){
    cardsInHand.push_back(card);
  }

  void printHand(){
    for (const Card& card : cardsInHand){
      card.printCard();
    }
  }

  int calculateHandValue() const {
        int value = 0;
        int aceCount = 0;

        for (const Card& card : cardsInHand) {
            value += card.getValue();
            if (card.rank == 1) { 
                aceCount++;
            }
        }

        while (value <= 11 && aceCount > 0) {
            value += 10;
            aceCount--;
        }

        return value;
    }
};

class Deck{
public:
  vector <Card> cardsInDeck;

  void addCard(Card &card){
    cardsInDeck.push_back(card);
  }

  Card drawCard(){
    cardsInDeck.back().printCard();
    Card cardToReturn = cardsInDeck.back();
    cardsInDeck.pop_back();
    return cardToReturn;
  }

  void printDeck(){
    for (const Card& card : cardsInDeck){
      card.printCard();
    }
  }
};

class Dealer{
public:
  Hand dealerHand;
  void dealerTurn(Deck& deck){
    while (dealerHand.calculateHandValue() < 17) {
        cout << "Dealer draws a card:\n";
        Card drawnCard = deck.drawCard();
        dealerHand.addCard(drawnCard);
    }
    cout << "\nDealer's final hand:\n";
    dealerHand.printHand();
    cout << "Dealer's hand value: " << dealerHand.calculateHandValue() << endl;
    }
};

class Player{
public:
  Hand playerHand;

  void playerTurn(Deck& deck) {
        char choice;
        do {
            cout << "\nYour current hand:\n";
            playerHand.printHand();
            cout << "Your hand value: " << playerHand.calculateHandValue() << endl;

            cout << "Do you want to draw a card? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                Card drawnCard = deck.drawCard();
                playerHand.addCard(drawnCard);
            } else {
                break;
            }

            if (playerHand.calculateHandValue() > 21) {
                cout << "\nYour hand value: " << playerHand.calculateHandValue() << " - You busted.\n";
                break;
            }

        } while (playerHand.calculateHandValue() <= 21);
    }
};

void createDeck(Deck& deck){
  for (int suite = 1; suite <= 4; suite++){
    for (int rank = 1; rank <= 13; rank++){
      Card card(rank, suite);
      deck.addCard(card);
    }
  }
}

void shuffleDeck(Deck& deck){
  random_device rd;
  mt19937 g(rd());
  shuffle(deck.cardsInDeck.begin(), deck.cardsInDeck.end(), g);
}

int main (){
  Deck deck;
  createDeck(deck);
  shuffleDeck(deck);

  Dealer dealer;
  Player player;

  cout << "Dealing initial cards:\n";
  Card playerCard1 = deck.drawCard();
  player.playerHand.addCard(playerCard1);
  Card playerCard2 = deck.drawCard();
  player.playerHand.addCard(playerCard2);

  Card dealerCard1 = deck.drawCard();
  dealer.dealerHand.addCard(dealerCard1);
  Card dealerCard2 = deck.drawCard();
  dealer.dealerHand.addCard(dealerCard2);

  player.playerTurn(deck);

  if (player.playerHand.calculateHandValue() <= 21) {
      dealer.dealerTurn(deck);
  }

  cout << "\nGame over.\n";
  if (player.playerHand.calculateHandValue() > 21) {
      cout << "Player busted. Dealer wins.\n";
  } else if (dealer.dealerHand.calculateHandValue() > 21) {
      cout << "Dealer busted. Player wins.\n";
  } else if (player.playerHand.calculateHandValue() > dealer.dealerHand.calculateHandValue()) {
      cout << "Player wins.\n";
  } else if (player.playerHand.calculateHandValue() < dealer.dealerHand.calculateHandValue()) {
      cout << "Dealer wins.\n";
  } else {
      cout << "Tie.\n";
  }
}
