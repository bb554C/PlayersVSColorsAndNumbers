#include "Game.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <vector>

std::string c,cc[4],lastCardColour,p;
int shuffle = 1,n,nn[4],lastCardNumber,dumpPileCount = 0, drawDeckCount = 0,playerNum = 0,cardsOnHandCount[4],totalCards = 0,cardNum = 0,select = -1,actionAlert[4],winner = -1;
int computerMode = 0, numPlayer = 1;

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::playGame()
{
	while(winner == -1)
    {
        if(drawDeckCount == 0)
        {
            shuffleDumpPile();
        }
        if(player[playerNum].getName() != "Bot")
        {
            if(numPlayer > 1)
            {
                do
                {
                    system("CLS");
                    std::cout << " ~~~ PLAYERS VS COLORS AND NUMBERS ~~~" << std::endl;
                    std::cout << "Player " << playerNum+1 << " " << player[playerNum].getName() << " please enter password: ";
                    std::cin.ignore();
                    std::getline(std::cin,p);
                }while(p != player[playerNum].getPassword());
                playCard();
            }
            else
            {
                playCard();
            }
        }
        else if(player[playerNum].getName() == "Bot")
        {
            botPlayCard();
        }
    }
    return;
}

void Game::setPlayers()
{
    char confirm;
    int i, repeat = 1,pass;
    std::string n,p;
    for(i = 0; i < 4; i = i + 1)
    {
        n = "Bot";
        player[i].setName(n);
    }
    while(repeat == 1)
    {
        repeat = 0;
        std::cout << "Please enter number of human players (1-4): ";
        std::cin >> numPlayer;
        system("CLS");
        if(numPlayer < 1 || numPlayer > 4)
        {
            std::cout << "Error: You have entered " << numPlayer << std::endl << "Please enter 1 to 4 players only!" << std::endl;
            repeat = 1;
        }
    }
    for(i = 0; i < numPlayer; i++)
    {
        repeat = 1;
        pass = 0;
        do
        {
            system("CLS");
            std::cout << "Please enter player " << i + 1 << " name: ";
            std::cin.ignore();
            pass = pass+1;
            std::getline(std::cin,n);
            player[i].setName(n);
            if(numPlayer > 1)
            {
                std::cout << "Please enter password with no spaces: ";
                std::getline(std::cin,p);
                player[i].setPassword(p);
            }
            std::cout << std::endl << "Your name is: " << player[i].getName() << std::endl;
            if(numPlayer > 1)
            {
            std::cout << "Your password is: " << player[i].getPassword() << std::endl;
            }
            std::cout << "Is the information above correct? (Y/N): ";
            std::cin >> confirm;
            if(confirm == 'Y' || confirm == 'y')
            {
                repeat = 0;
            }
            else
            {
                std::cout << "ERROR: Please enter Y or N only!";
                repeat = 1;
            }
        }while(repeat == 1);
    }
    system("CLS");
    return;
}

void Game::createCards()
{
    int i,player;
    actionAlert[0] = -1;
    actionAlert[1] = -1;
    actionAlert[2] = -1;
    actionAlert[3] = -1;
    for(i = 0; i <= 9; i++)
    {
        c = "Green";
        pvcnCards[totalCards].setCard(i,c);
        totalCards = totalCards + 1;
    }
    for(i = 0; i <= 9; i++)
    {
        c = "Blue";
        pvcnCards[totalCards].setCard(i,c);
        totalCards = totalCards + 1;
    }
    for(i = 0; i <= 9; i++)
    {
        c = "Red";
        pvcnCards[totalCards].setCard(i,c);
        totalCards = totalCards + 1;
    }
    for(i = 0; i <= 9; i++)
    {
        c = "Yellow";
        pvcnCards[totalCards].setCard(i,c);
        totalCards = totalCards + 1;
    }
    drawDeckCount = totalCards - 1;
    for(i = 0; i < totalCards; i++)
    {
        dumpPile[i].setCard(-1," ");
    }
    for(player = 0; player < 4; player++)
    {
        for(i = 0; i < totalCards; i++)
        {
            cardsOnHand[player][i].setCard(-1," ");
        }
    }
   return;
}

void Game::shuffleDeck()
{
    int x,y = 0,i;
    std::vector<int> myvector;
    srand(time(NULL));
    for (i = 0; i < totalCards; i++) myvector.push_back(i);
    std::random_shuffle ( myvector.begin(), myvector.end() );
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    {
        x = *it;
        n = pvcnCards[x].getNumber();
        c = pvcnCards[x].getColour();
        deck[y].setCard(n,c);
        y = y + 1;
    }
}

void Game::shuffleDumpPile()
{
    int y = 0;
    for (int i = dumpPileCount; i >= 0; i--)
    {
        n = dumpPile[i].getNumber();
        c = dumpPile[i].getColour();
        deck[y].setCard(n,c);
        y = y + 1;
    }
    drawDeckCount = dumpPileCount;
    dumpPileCount = 0;
    shuffle = shuffle + 1;
    return;
}

void Game::dealCards()
{
    int player;
    for(player = 0; player < 4; player++)
    {
        for(cardNum = 0; cardNum < 7; cardNum++)
        {
            cardsOnHandCount[player] = cardsOnHandCount[player] +1;
            n = deck[drawDeckCount].getNumber();
            c = deck[drawDeckCount].getColour();
            cardsOnHand[player][cardNum].setCard(n,c);
            deck[drawDeckCount].setCard(-1," ");
            drawDeckCount = drawDeckCount - 1;
        }
    }
    n = deck[drawDeckCount].getNumber();
    c = deck[drawDeckCount].getColour();
    lastCardNumber = n;
    lastCardColour = c;
    dumpPile[dumpPileCount].setCard(n,c);
    dumpPileCount = dumpPileCount + 1;
    deck[drawDeckCount].setCard(-1," ");
    drawDeckCount = drawDeckCount - 1;
    return;
}

void Game::printInfo()
{
    int i;
    system("CLS");
    std::cout << std::endl << " ~~~ PLAYERS VS COLORS AND NUMBERS ~~~" << std::endl;
    for (i = 0; i < 4; i++)
    {
        std::cout << "Player " << i+1 << " " << player[i].getName() << ": " << cardsOnHandCount[i] << " cards on hand ->";
        if(actionAlert[i] == 0 && drawDeckCount > 0)
        {
            std::cout << " Action | took a card";
        }
        if(actionAlert[i] == 0 && drawDeckCount <= 0 && dumpPileCount == 0)
        {
            std::cout << " Action | skipped a turn";
        }
        if(actionAlert[i] > 0)
        {
            std::cout << " Action | played " << nn[i] << " - " << cc[i];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "Cards left on draw deck: ";
    if(drawDeckCount <= 0)
    {
        std::cout << "0" << std::endl;
    }
    else
    {
        std::cout << drawDeckCount+1 << std::endl;
    }
    std::cout << "Cards on dump pile: " << dumpPileCount << std::endl << std::endl;
    std::cout << "Last Card Played: " << lastCardNumber << " - " << lastCardColour << std::endl;
    std::cout << "\nNow Playing..." << std::endl << "Player " << playerNum + 1 << " : " << player[playerNum].getName() << std::endl;
    if(player[playerNum].getName() != "Bot")
    {
        std::cout << "Your cards are: " << std::endl;
        cardNum = 0;
        do
        {
            std::cout << cardNum + 1 << ". " << cardsOnHand[playerNum][cardNum].getNumber() << " - " << cardsOnHand[playerNum][cardNum].getColour() << std::endl;
            cardNum++;
        }while(cardNum < cardsOnHandCount[playerNum]);
    }
    return;
}

void Game::printWinner()
{
    system("CLS");
    std::cout << std::endl << "PLAYERS VS COLORS AND NUMBERS" << std::endl;
    std::cout << "!!! CONGRATULATIONS !!!" << std::endl;
    std::cout << " You Won! Player " << playerNum+1 << " " << player[playerNum].getName() << std::endl;
    system("PAUSE");
    return;
}

void Game::playCard()
{
    int pass = 0,cardCompare = 0;
    select = -1;
    actionAlert[playerNum] = -1;
    while(cardCompare == 0)
    {
        printInfo();
        std::cout << "Enter the number beside the card you want to select or Enter 0 to draw a card. ";
        if((select < 0 && pass > 0) || (select > cardsOnHandCount[playerNum] && pass > 0))
        {
            std::cout << "\nERROR: Please enter 0 - " << cardsOnHandCount[playerNum] << " only! ";
        }
        std::cin >> select;
        pass = pass + 1;
        n = cardsOnHand[playerNum][select-1].getNumber();
        c = cardsOnHand[playerNum][select-1].getColour();
        switch(select)
        {
            case 0:
                printInfo();
                std::cout << "Player " << playerNum + 1 << " took a card!" << std::endl;
                actionAlert[playerNum] = 0;
                if(drawDeckCount != 0)
                {
                    drawCard();
                }
                cardCompare = 1;
                break;
            default:
                if( n == lastCardNumber || c == lastCardColour)
                {
                    printInfo();
                    std::cout << "Player " << playerNum + 1 << " played the card: " << n << " - " << c << std:: endl << std::endl;
                    actionAlert[playerNum] = select;
                    dumpCard();
                    cardCompare = 1;
                }
                else if(n != lastCardNumber)
                {
                    if (c != lastCardColour)
                    {
                        std::cout << "\nERROR: Please play a card with the same number or same colour!" << std::endl;
                        cardCompare = 0;
                    }
                }
                else if(c != lastCardColour)
                {
                    if (n != lastCardNumber)
                    {
                        std::cout << "\nERROR: Please play a card with the same number or same colour!" << std::endl;
                        cardCompare = 0;
                    }
                }
                break;
        }
        pause();
    }
    if(cardsOnHandCount[playerNum] == 0)
    {
        return;
    }
    playerNum = playerNum + 1;
    if(playerNum == 4)
    {
        playerNum = playerNum - 4;
    }
    return;
}

void Game::botPlayCard()
{
    int cardCompare = 0,pass = 0;
    select = -1;
    actionAlert[playerNum] = -1;
    while(cardCompare == 0)
    {
        if(computerMode == 1)
        {
            botPlayCardEasy();
        }
        else if(computerMode == 2)
        {
            botPlayCardNormal();
        }
        else if(computerMode == 3)
        {
            botPlayCardHard();
        }
        n = cardsOnHand[playerNum][select-1].getNumber();
        c = cardsOnHand[playerNum][select-1].getColour();
        switch(select)
        {
            case 0:
                printInfo();
                std::cout << "Player " << playerNum + 1 << " took a card!" << std::endl;
                actionAlert[playerNum] = 0;
                if(drawDeckCount != 0)
                {
                    drawCard();
                }
                cardCompare = 1;
                break;
            default:
                    if( n == lastCardNumber || c == lastCardColour)
                    {
                        printInfo();
                        actionAlert[playerNum] = select;
                        dumpCard();
                        cardCompare = 1;
                    }
                    else if(n != lastCardNumber)
                    {
                        if (c != lastCardColour)
                        {
                            cardCompare = 0;
                        }
                    }
                    else if(c != lastCardColour)
                    {
                        if (n != lastCardNumber)
                        {
                            cardCompare = 0;
                        }
                    }
                    break;
        }
        system("CLS");
        printInfo();
        pause();
    }
    if(cardsOnHandCount[playerNum] == 0)
    {
        return;
    }
    playerNum = playerNum + 1;
    if(playerNum == 4)
    {
        playerNum = playerNum - 4;
    }
    return;
}

void Game::botPlayCardEasy()
{
    select = -1;
    srand (time(NULL));
    select = rand() % cardsOnHandCount[playerNum];
    return;
}

void Game::botPlayCardNormal()
{
    select = -1;
    for(int i = 1; i < cardsOnHandCount[playerNum]; i++)
    {
        if(lastCardColour == cardsOnHand[playerNum][i-1].getColour())
        {
            select = i;
        }
        if(lastCardNumber == cardsOnHand[playerNum][i-1].getNumber())
        {
            select = i;
        }
    }
    if(select <= 0)
    {
        select = 0;
    }
    return;
}

void Game::botPlayCardHard()
{
    select = -1;
    for(int i = 1; i < cardsOnHandCount[playerNum]; i++)
    {
        if(lastCardNumber == cardsOnHand[playerNum][i-1].getNumber())
        {
            select = i;
        }
        if(lastCardColour == cardsOnHand[playerNum][i-1].getColour())
        {
            select = i;
        }
    }
    if(select <= 0)
    {
        select = 0;
    }
    return;
}
void Game::drawCard()
{
    if(drawDeckCount > 0)
    {
        n = deck[drawDeckCount].getNumber();
        c = deck[drawDeckCount].getColour();
        cardsOnHand[playerNum][cardsOnHandCount[playerNum]].setCard(n,c);
        deck[drawDeckCount].setCard(-1," ");
        cardsOnHandCount[playerNum] = cardsOnHandCount[playerNum] + 1;
    }
    if(dumpPileCount > 0)
    {
        lastCardNumber = dumpPile[dumpPileCount-1].getNumber();
        lastCardColour = dumpPile[dumpPileCount-1].getColour();
    }
    drawDeckCount = drawDeckCount - 1;
    if(drawDeckCount <= 0 && dumpPileCount > 0)
    {
        shuffleDumpPile();
    }
    return;
}

void Game::dumpCard()
{
    int i;
    dumpPile[dumpPileCount].setCard(n,c);
    nn[playerNum] = n;
    cc[playerNum] = c;
    if(drawDeckCount > 0)
    {
        lastCardNumber = n;
        lastCardColour = c;
    }
    for(i = select; i < cardsOnHandCount[playerNum]; i++)
    {
        n = cardsOnHand[playerNum][i].getNumber();
        c = cardsOnHand[playerNum][i].getColour();
        cardsOnHand[playerNum][i-1].setCard(n,c);
    }
    dumpPileCount = dumpPileCount + 1;
    cardsOnHandCount[playerNum] = cardsOnHandCount[playerNum] - 1;
    if(cardsOnHandCount[playerNum] == 0)
    {
        winner = playerNum;
    }
    return;
}

void Game::pause()
{
    int start, pause = 500;
    for (int i = 0; i < 1; i++)
    {
        std::cout << "Please wait verifying player " << playerNum+1 << "'s move" << std::endl;
        start = clock();
        while (clock() < start + pause);
    }
    return;
}

void Game::startGame()
{
    int pass = 0;
    system("CLS");
    std::cout << " ~~~ PLAYERS VS COLORS AND NUMBERS ~~~" << std::endl;
    std::cout << "Computer difficulty" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Normal" << std::endl;
    std::cout << "3. Hard" << std::endl;
    pass = 0;
    do
    {
        std::cout << "Please enter computer difficulty: ";
        std::cin >> computerMode;
        if(pass > 0)
        {
            std::cout << "Error: Please enter 1 - 3 only!" << std::endl;
        }
        pass = pass + 1;
    }while(computerMode < 1 || computerMode > 3);
    return;
}
