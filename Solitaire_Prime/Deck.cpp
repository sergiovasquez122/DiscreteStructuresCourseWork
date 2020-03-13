//
// Created by sergio on 9/14/19.
//

#include "Deck.h"
#include "stdlib.h"

Deck::Deck() {
    card_index = 0;

    char rank_type[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suit_type[] = {'S', 'H', 'D', 'C'};


    for(int current_suit = 0; current_suit < 4; ++current_suit){
        for(int current_rank = 0; current_rank < 13; ++current_rank){
            cards[current_suit*13 + current_rank].setCard(rank_type[current_rank], suit_type[current_suit]);
        }
    }
}

void Deck::refreshDeck() {
    *this = Deck();
}

int Deck::cardsLeft() {
    return 52 - card_index;
}

Card Deck::deal() {
    return cards[card_index++];
}

void Deck::showDeck() {
    for(int current_suit = 0;current_suit<4;++current_suit){
        for(int current_rank = 0;current_rank<13;++current_rank){
            cards[current_suit*13 + current_rank].showCard();
            cout<<" ";
        }
        cout<<endl;
    }
}

void Deck::shuffle() {
    srand(time(NULL));

    for(int current_iteration = 0;current_iteration < 1000;++current_iteration){
        int i = (rand() % 52);
        int j = (rand() % 52);
        std::swap(cards[i], cards[j]);
    }
}
