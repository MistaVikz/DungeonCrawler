#include "game.h"
#include <iostream>

Game::Game(Player *_player, Dungeon *_dungeon){
    player = _player;
    dungeon = _dungeon;
    isGameOver = false;

    dungeon->setUpDungeon();
    player->currentRoom = &dungeon->rooms[dungeon->rows -1][dungeon->cols -1];
}

void Game::intiateRoomSequence() {
    room * room = player->currentRoom;
    if(room->row == 0 && room->col == 0 && room->enemies.empty()) {
        std::cout << "Congradulations, you have reached the exit and have beat the game!" << std::endl;
        isGameOver=true;
        return;
    }

    if (!room->enemies.empty()) {
        handleEnemyActions();
    } else if (!room->items.empty()) {
        handleItemActions();
    } else {
        handleMovementActions();
    }    
}

void Game::printActions(std::vector<std::string> actions) {
    for (int i=0; i < actions.size(); i++) {
        std::cout << i + 1 << ". " << actions[i] << std::endl;
    }
}

std::vector<std::string> Game::getMovementActions() {
    std::vector<std::string> actions;

    room *currentRoom = player->currentRoom;
    if(currentRoom->col > 0) {
        actions.push_back("Move left");
    }
    if(currentRoom->row > 0) {
        actions.push_back("Move up");
    }
    if(currentRoom->col < (dungeon->cols -1)) {
        actions.push_back("Move right");
    }
    if(currentRoom->row < (dungeon->rows -1)) {
        actions.push_back("Move down");
    }
    return actions;
}

void Game::handleMovementActions() {
    std::cout << "Where do you want to go next?" << std::endl;
    std::vector<std::string> actions = getMovementActions();
    printActions(actions);

    int input;
    std::cin >> input;
    std::string chosenAction = actions[input - 1];

    int horizontalMovement = 0;
    int verticalMovement = 0;
    if (chosenAction == "Move left") {
        horizontalMovement = -1;
    } else if (chosenAction == "Move up") {
        verticalMovement = -1;
    } else if (chosenAction == "Move right") {
        horizontalMovement = 1;
    } else if (chosenAction == "Move down") {
        verticalMovement = 1;
    }

    room *newRoom = &dungeon->rooms[player->currentRoom->row + verticalMovement][player->currentRoom->col + horizontalMovement];
    player->moveToRoom(newRoom);

    std::cout << "You are now in room " << newRoom->row << " " << newRoom->col << std::endl;

}

void Game::handleEnemyActions() {
    std::cout << "There is an enemy " << player->currentRoom->enemies[0].getName() << " in this room! What do you want to do?" << std::endl;
    std::vector<std::string> actions;
    actions.push_back("Engage Enemy");
    actions.push_back("Retreat");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input = 1 ) {
        engageInCombat();
    } else {
        player->retreat();
    }
}

void Game::engageInCombat() {
    GameCharacter *enemy = &player->currentRoom->enemies[0];
    while (true) {
        enemy->takeDamage(player->getDamage());
        std::cout << "You strike the " << enemy->getName() << ", dealing " << player->getDamage() << " damage." << std::endl;
        if (!enemy->checkIfAlive()) {
            std::cout << "You have defeated the " << enemy->getName() << "!" << std::endl;
            player->currentRoom->enemies.clear();
            return;
        }

        player->takeDamage(enemy->getDamage());
        std::cout << "You have been hit by the " << enemy->getName() << ", taking " << enemy->getDamage() << " damage. You now have " << player->getHealth() << " health remaining." << std::endl;
        if (!player->checkIfAlive()) {
            isGameOver = true;
            std::cout << "You have been defeated by the " << enemy->getName() << ". Game Over!" << std::endl;
            return;
        }

        std::cout << "Would you like to keep fighing the  " << enemy->getName() << " or retreat?" << std::endl;
        std::vector<std::string> actions;
        actions.push_back("Keep Fighting");
        actions.push_back("Retreat");
        printActions(actions);

        int input;
        std::cin >> input;
        if (input != 1 ) {
            player->retreat();
            return;
        }
    }
}

void Game::handleItemActions() {
    item item = player->currentRoom->items[0];
    std::cout << "You find a " << item.name << " in this room! What do you want to do?" << std::endl;
    std::vector<std::string> actions;
    actions.push_back("Pick up item");
    actions.push_back("Ignore item");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input = 1 ) {
        player->pickUpItem(item);
        std::cout << "You pick up a " << item.name << ". Your health is now " << player->getHealth() << " and your damage is now " << player->getDamage() << "." << std::endl;
        player->currentRoom->items.clear();
    } else {
        handleMovementActions();
    }
}