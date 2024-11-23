#include "player.h"
#include "dungeon.h"

#include <vector> // remove later

#ifndef GAME_H
#define GAME_H

class Game {
    private:
        Dungeon *dungeon;
        Player *player;
    
    public:
        bool isGameOver;
        Game(Player *, Dungeon *);
        std::vector<std::string> getMovementActions();
        void handleMovementActions();
        void printActions(std::vector<std::string>);
        void intiateRoomSequence();
        void handleEnemyActions();
        void engageInCombat();
        void handleItemActions();
};

#endif