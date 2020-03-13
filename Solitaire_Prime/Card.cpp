//
// Created by sergio on 9/14/19.
//

#include "Card.h"

Card::Card() {
    rank = '?';
    suit = '?';
}

Card::Card(char r, char s) {
    rank = r;
    suit = s;
}

int Card::getValue() {
    if(isdigit(rank)){
        return rank - '0';
    } else if(rank == 'A'){
        return 1;
    } else {
        return 10;
    }
}

void Card::setCard(char r, char s) {
    rank = r;
    suit = s;
}

void Card::showCard() {
    if(rank == 'T'){
        cout << "10";
    } else {
        cout << rank;
    }
    cout << suit;
}

