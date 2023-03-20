#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"
#include "Gold.h"

using namespace std;

class Item;
class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    vector<Item> items;
    int gold;
public:
    Player();
    Player(string,int,int,int,int);
    void addItem(Item);
    void increaseStates(int,int,int);
    void changeRoom(Room*);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(Item);
    void setItems(Item);
    void addGold(int);
    void minusGold(int);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item> getInventory();
    vector<Item> getItems();
    int getGold();
};

#endif // PLAYER_H_INCLUDED
