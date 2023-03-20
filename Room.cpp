#include "Room.h"

Room::Room(){
    
}

Room::Room(bool a, int b, vector<Object*> c){
    isExit = a;
    index = b;
    objects = c;
}

bool Room::popObject(){
    objects.pop_back();
    return 0;
}

void Room::setUpRoom(Room* a){
    upRoom = a;
}

void Room::setDownRoom(Room* a){
    downRoom = a;
}

void Room::setLeftRoom(Room* a){
    leftRoom = a;
}

void Room::setRightRoom(Room* a){
    rightRoom = a;
}

void Room::setIsExit(bool a){
    isExit = a;
}

void Room::setIndex(int a){
    index = a;
}

void Room::setObjects(vector<Object*> a){
    objects = a;
}

bool Room::getIsExit(){
    return isExit;
}

int Room::getIndex(){
    return index;
}

vector<Object*> Room::getObjects(){
    return objects;
}

Room* Room::getUpRoom(){
    return upRoom;
}

Room* Room::getDownRoom(){
    return downRoom;
}

Room* Room::getLeftRoom(){
    return leftRoom;
}

Room* Room::getRightRoom(){
    return rightRoom;
}