#include "Card.h"

#include <iostream>
#include <string>

Card::Card()
{
    //ctor
}

Card::~Card()
{
    //dtor
}

void Card::setCard(int x, std::string y)
{
    number = x;
    colour = y;
}

int Card::getNumber()
{
    return number;
}

std::string Card::getColour()
{
    return colour;
}
