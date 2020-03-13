#include <iostream>
#include "Deck.h"
#include "Card.h"

bool isPrime(int number);
void solitairePrime(Deck deck);

int main() {
    Deck deck;
    cout<< "Welcome to Solitaire Prime!"<<endl;

    while(true) {
        cout<<"1) New Deck"<<endl;
        cout<<"2) Display Deck"<<endl;
        cout<<"3) Shuffle Deck"<<endl;
        cout<<"4) Play Solitaire Prime"<<endl;
        cout<<"5) Exit"<<endl;
        int choice;
        std::cin >> choice;

        switch (choice){
            case 1:
                deck.refreshDeck();
                break;
            case 2:
                deck.showDeck();
                break;
            case 3:
                deck.shuffle();
                break;
            case 4:
                solitairePrime(deck);
                break;
            case 5:
                return 0;
        }
    }
}

bool isPrime(int number){

    if(number == 0 || number == 1){
        return false;
    }

    bool canidates[number + 1];

    for(int i = 0; i <= number; ++i){
        canidates[i] = true;
    }

    for(int i = 2;i*i <= number;++i){
        if(canidates[i]){
            for(int j = i*i;j <= number;j+=i){
                canidates[j] = false;
            }
        }
    }
    return canidates[number];
}

void solitairePrime(Deck deck){
    cout<<"Playing Solitaire Prime!!!"<<endl<<endl;

    Card current_pile[52];
    int current_pile_index = 0;
    int current_pile_sum = 0;
    int piles = 0;
    bool won = false;
    while(deck.cardsLeft()){
        Card current_card = deck.deal();
        current_pile_sum += current_card.getValue();
        current_pile[current_pile_index++] = current_card;

        if(isPrime(current_pile_sum)){
            piles++;

            for(int i = 0; i < current_pile_index;++i){
                current_pile[i].showCard();
                cout<<", ";
            }
            cout<<"Prime:"<<current_pile_sum;
            if(deck.cardsLeft() == 0){
                cout<<endl;
                cout<<"Winner in " << piles <<" piles!"<<endl;

                won  = true;
            }
            cout<<endl;
            current_pile_index = 0;
            current_pile_sum = 0;
        }
    }

    if (!won){
        for(int i = 0; i < current_pile_index;++i){
            current_pile[i].showCard();
            cout<<", ";
        }
        cout<<"Loser"<<endl;
    }

}
