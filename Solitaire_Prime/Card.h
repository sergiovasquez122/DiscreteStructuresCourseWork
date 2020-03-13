//
// Created by sergio on 9/14/19.
//

#ifndef SOLITAIRE_PRIME_CARD_H
#define SOLITAIRE_PRIME_CARD_H
#include <iostream>

using std::cout;
using std::endl;

class Card {
    private:
        char rank;
        char suit;
    public:
        Card();
        Card(char r, char s);
        void setCard(char r, char s);
        void showCard();
        int getValue();
};


#endif //SOLITAIRE_PRIME_CARD_H
