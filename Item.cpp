#include "Item.h"

Item::Item(){

}

Item::Item(string a, int b, int c, int d):Object(a,"Item"){
    health = b;
    attack = c;
    defense = d;
}

bool Item::triggerEvent(Object* a){
    Player* player = dynamic_cast<Player*>(a);

    cout << "> There is a " << getName()  << "." << endl;
    while(1){
        cout << "A. Ignore the " << getName() << endl;
        cout << "B. Pick up the " << getName() << endl;
        cout << "C. Check status" << endl;

        string reply;
        cin >> reply;

        if(reply == "A"){
            break;
        }else if(reply == "B"){
            cout << endl;
            cout << "> The strengthen of " << getName()  << ":"<< endl;
            cout << "- Health  +" << health << endl;
            cout << "- Attack  +" << attack << endl;
            cout << "- Defense +" << defense << endl;
            cout << "> Do you want to equip the " << getName() << "(y,n)"<< endl;

            string answer;
            cin >> answer;

            if(answer == "y"){
                player->increaseStates(health,attack,defense);
                cout << "> Your successfully equip the " << getName() << "." << endl << endl;
                break;
            }else if(answer == "n"){
                break;
            }else{
                break;
            }
        }else if(reply == "C"){
            player->triggerEvent(player);
        }else{
            continue;
        }
    }
    return 0;
}

void Item::setHealth(int a){
    health = a;
}

void Item::setAttack(int a){
    attack = a;
}

void Item::setDefense(int a){
    defense = a;
}

int Item::getHealth(){
    return health;
}

int Item::getAttack(){
    return attack;
}

int Item::getDefense(){
    return defense;
}