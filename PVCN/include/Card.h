#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card
{
    public:
        Card();
        virtual ~Card();
        //setters
        void setCard(int,std::string);
         //getters
        int getNumber();
        std::string getColour();
    protected:

    private:
        int number;
        std::string colour;
};

#endif // CARD_H
