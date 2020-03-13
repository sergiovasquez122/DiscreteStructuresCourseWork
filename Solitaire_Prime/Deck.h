//
// Created by sergio on 9/14/19.
//

#ifndef SOLITAIRE_PRIME_DECK_H
#define SOLITAIRE_PRIME_DECK_H

#include "Card.h"

class Deck {
private:
    int card_index;
    Card cards[52];
public:
    Deck();
    void refreshDeck();
    Card deal();
    void shuffle();
    int cardsLeft();
    void showDeck();
};


#endif //SOLITAIRE_PRIME_DECK_H
