#include "player.h"

Player::Player(std::string _name, int _health, int _damage): GameCharacter(_name, _health, _damage) {

}

void Player::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

void Player::moveToRoom(room * newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
}

void Player::retreat() {
    room *tempRoom = currentRoom;
    currentRoom = previousRoom;
    previousRoom = tempRoom;
}

void Player::pickUpItem(item item) {
    damage += item.damage;
    heal(item.health);
}