#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#include <iostream>
#include <string>

class Game
{
    public:
        Game();
        virtual ~Game();
        //setters
        void startGame();
        void setPlayers();
        void createCards();
        void shuffleDeck();
        void shuffleDumpPile();
        void dealCards();
        void printInfo();
        void printWinner();
        void playCard();
        void botPlayCard();
        void botPlayCardEasy();
        void botPlayCardNormal();
        void botPlayCardHard();
        void drawCard();
        void playGame();
        void sortHand();
        void dumpCard();
        void pause();
        void botPause();
    protected:

    private:
        Player player[4];
        Card pvcnCards[40];
        Card deck[40];
        Card cardsOnHand[4][40];
        Card dumpPile[40];

};

#endif // GAME_H
