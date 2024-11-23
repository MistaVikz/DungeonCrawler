# include "dungeon.h"

void Dungeon::setUpDungeon() {
    for (int r =0; r < rows; r++) {
        for (int c=0; c< cols; c++) {
            room room;
            room.row = r;
            room.col = c;
            rooms[r][c] = room;
        } 
    }

    GameCharacter enemy1 = GameCharacter("Ozzie", 20, 5);
    GameCharacter enemy2 = GameCharacter("Beaker", 20, 10);
    GameCharacter enemy3 = GameCharacter("Buffer", 100, 10);

    rooms[2][1].enemies.push_back(enemy1);
    rooms[1][2].enemies.push_back(enemy2);
    rooms[0][0].enemies.push_back(enemy3);

    item healingPotion;
    healingPotion.name = "Healing Potion";
    healingPotion.health = 50;

    item sword;
    sword.name = "Sword";
    sword.damage = 20;

    rooms[1][1].items.push_back(healingPotion);
    rooms[0][2].items.push_back(sword);
}