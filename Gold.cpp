#include "Gold.h"

Gold::Gold(){

}

Gold::Gold(int a):Object("Gold","Gold"){
    gold = a;
}

void Gold::setGold(int a){
    gold = a;
}

bool Gold::triggerEvent(Object* a){
    Player* player = dynamic_cast<Player*>(a);
    cout << "> You get $" << gold << " gold." << endl << endl;
    player->addGold(gold);
    return 0; 
}

int Gold::getGold(){
    return gold;
}