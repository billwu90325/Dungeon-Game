#include "Player.h"

Player::Player(){
    currentRoom = NULL;
    previousRoom = NULL;
}

Player::Player(string a, int b, int c, int d, int e):GameCharacter(a,"Player",b,c,d){
    currentRoom = NULL;
    previousRoom = NULL;
    gold = e;
}

void Player::addItem(Item a){
    inventory.push_back(a);
}

void Player::increaseStates(int a, int b, int c){
    setCurrentHealth(getCurrentHealth()+a);
    setMaxHealth(getMaxHealth()+a);
    setAttack(getAttack()+b);
    setDefense(getDefense()+c);
}

void Player::changeRoom(Room* a){
    previousRoom = currentRoom;
    currentRoom = a;
}

bool Player::triggerEvent(Object* a){
    cout << endl;
    cout << "[" << getName() << "]" << endl;
    cout << "- Health:" << getCurrentHealth()  << "/" << getMaxHealth() << endl;
    cout << "- Attack:" << getAttack() << endl;
    cout << "- Defense:" << getDefense() << endl;
    cout << "Gold $" << getGold() << endl << endl;
    return 1;
}

void Player::setCurrentRoom(Room* a){
    currentRoom = a;
}
void Player::setPreviousRoom(Room* a){
    previousRoom = a;
}

void Player::setInventory(Item a){
    inventory.push_back(a);
}

void Player::setItems(Item a){
    items.push_back(a);
}

void Player::addGold(int a){
    gold += a;
}

void Player::minusGold(int a){
    gold -= a;
}

Room* Player::getCurrentRoom(){
    return currentRoom;
}

Room* Player::getPreviousRoom(){
    return previousRoom;
}

vector<Item> Player::getInventory(){
    return inventory;
}

vector<Item> Player::getItems(){
    return items;
}

int Player::getGold(){
    return gold;
}
