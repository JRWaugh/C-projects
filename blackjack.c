#include <stdio.h>
#include <math.h>
#define DECK_SIZE 52

//Enumerate four suits from 0 to 3
enum Suit {HEARTS = 0, DIAMONDS, SPADES, CLUBS};
//Enumerate card values from 1 to 13
enum Value {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

//Define structure of card that has suit and value
struct card {
    enum Suit suit;
    enum Value value;
};

struct player {
    struct card[5];
}

void shuffle(struct card deck[DECK_SIZE], int times);

int main() {
    char *suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"}; 
    struct card deck[DECK_SIZE] = {
        {HEARTS, ACE}, {HEARTS, TWO}, {HEARTS, THREE}, {HEARTS, FOUR}, {HEARTS, FIVE}, {HEARTS, SIX}, {HEARTS, SEVEN}, {HEARTS, EIGHT}, {HEARTS, NINE}, {HEARTS, TEN}, {HEARTS, JACK}, {HEARTS, QUEEN}, {HEARTS, KING},
        {DIAMONDS, ACE}, {DIAMONDS, TWO}, {DIAMONDS, THREE}, {DIAMONDS, FOUR}, {DIAMONDS, FIVE}, {DIAMONDS, SIX}, {DIAMONDS, SEVEN}, {DIAMONDS, EIGHT}, {DIAMONDS, NINE}, {DIAMONDS, TEN}, {DIAMONDS, JACK}, {DIAMONDS, QUEEN}, {DIAMONDS, KING},
        {SPADES, ACE}, {SPADES, TWO}, {SPADES, THREE}, {SPADES, FOUR}, {SPADES, FIVE}, {SPADES, SIX}, {SPADES, SEVEN}, {SPADES, EIGHT}, {SPADES, NINE}, {SPADES, TEN}, {SPADES, JACK}, {SPADES, QUEEN}, {SPADES, KING},
        {CLUBS, ACE}, {CLUBS, TWO}, {CLUBS, THREE}, {CLUBS, FOUR}, {CLUBS, FIVE}, {CLUBS, SIX}, {CLUBS, SEVEN}, {CLUBS, EIGHT}, {CLUBS, NINE}, {CLUBS, TEN}, {CLUBS, JACK}, {CLUBS, QUEEN}, {CLUBS, KING}
        };

    //Print array before shuffle
    for(int i = 0; i < DECK_SIZE; i++){
        printf("%d ", deck[i].value);
    }
    shuffle(deck, 200);

    //Print array after shuffle
    for(int i = 0; i < DECK_SIZE; i++){
        printf("%s %d, ", suits[deck[i].suit], deck[i].value);
    }
}

void shuffle(struct card deck[DECK_SIZE], int times) {
    int card1, card2;
    struct card dummy;
    for(int i = 0; i < times; i++){
        //rand() will return the same result on every execution of the program. Use srand to make it actually somewhat random.
        card1 = rand() % 52;
        card2 = rand() % 52;
        dummy = deck[card1];
        deck[card1] = deck[card2];
        deck[card2] = dummy;
    }
}