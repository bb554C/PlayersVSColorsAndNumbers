#include "Player.h"

#include <iostream>
#include <string>


Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::setName(std::string n)
{
    name = n;
}

void Player::setScore(int s)
{
    score = s;
}

void Player::setPassword(std::string p)
{
    password = p;
}

std::string Player::getName()
{
    return name;
}

std::string Player::getPassword()
{
    return password;
}
