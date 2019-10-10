#include "Game.h"
#include "Player.h"
#include "Card.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

int main()
{
    Game game;
	int choice = 0, repeat = 1;
    system("CLS");
    while(repeat == 1)
    {
        std::cout << " ~~~ PLAYERS VS COLORS AND NUMBERS ~~~" << std::endl;
        std::cout << "1. Instructions" << std::endl;
        std::cout << "2. Play Game"  << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << " Please enter 0 - 2: ";
        std::cin >> choice;
        switch(choice)
        {
            case 0:
                repeat = 0;
                break;
            case 1:
                std::cout << std::endl << "Instructions: " << std::endl;
                std::cout << "Each card have a color and a number" << std::endl;
                std::cout << "At the start of the game, 1 card from the deck will be placed in the dump pile faced up" << std::endl;
                std::cout << "A player can do 1 of the 2 possible actions every turn" << std::endl;
                std::cout << "\t A. Draw a card from the deck" << std::endl;
                std::cout << "\t B. Play a card with the same number or color as the top card in the dump pile" << std::endl;
                std::cout << "Every time there are no more cards on the deck, the dump pile will be shuffled and made into the deck" << std::endl;
                std::cout << "If there are no more cards in the deck and dump pile, the player who chose action (A.) will skip a turn" << std::endl;
                std::cout << "Players must enter the number beside the cards to play a card" << std::endl;
                std::cout << "The first player who has no more cards on his hand wins" << std::endl;
                std::cout << std::endl;
                break;
            case 2:
                game.startGame();
                game.setPlayers();
                game.createCards();
                game.shuffleDeck();
                game.dealCards();
                game.playGame();
                game.printWinner();
                repeat = 0;
                break;
            default:
                std::cout << "ERROR: Please enter 0 - 2 only!" << std::endl;
                repeat = 1;
                break;
        }
    }
    return 0;
}
