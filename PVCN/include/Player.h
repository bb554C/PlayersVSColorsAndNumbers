#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>

class Player
{
    public:
        Player();
        virtual ~Player();
        //setters
        void setName(std::string);
        void setPassword(std::string);
        void setScore(int);
        //getters
        std::string getName();
        std::string getPassword();
        int getScore();
    protected:

    private:
        std::string name;
        std::string password;
        int score;
};

#endif // PLAYER_H
