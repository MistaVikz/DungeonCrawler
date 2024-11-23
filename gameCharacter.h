#include <string>

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

class GameCharacter {
    private:
        std::string name;
    protected:
        int maxHealth;
        int currentHealth;
        int damage;
    public:
        GameCharacter(std::string, int, int);
        void takeDamage(int);
        bool checkIfAlive();
        std::string getName();
        int getHealth();
        int getDamage();
};

#endif