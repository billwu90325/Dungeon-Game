#include "Monster.h"

Monster::Monster(){

}

Monster::Monster(string a, int b, int c, int d):GameCharacter(a,"Monster",b,c,d){

}

bool Monster::triggerEvent(Object* a){
    Player* player = dynamic_cast<Player*>(a);
    if(checkIsDead()){
        return 0;
    }else{
        while(1){
            cout << "> You run into " << getName()  << "." << endl;
            cout << "A. Fight with " << getName()  << endl;
            cout << "B. Retreat" << endl;
            cout << "C. Check status" << endl;

            string reply;
            cin >> reply;

            if(reply == "A"){
                cout << endl;
                cout << "["  << getName() << "]" << endl;
                cout << "- Health:" << getCurrentHealth() << "/" <<getMaxHealth() << endl;
                cout << "- Attack:" << getAttack() << endl;
                cout << "- Defense:" << getDefense() << endl;
                cout << "> Are you sure to fight with it?(y,n)" << endl;

                string answer;
                cin >> answer;

                if(answer == "y"){
                    while(getCurrentHealth() > 0){
                        if(player->getCurrentHealth() > 0){
                            cout << endl;
                            cout << "A. Attack." << endl;
                            cout << "B. Retreat." << endl;
                            cout << "C. Use props." << endl;
                            cout << "D. Check status." << endl;

                            string choice;
                            cin >> choice;

                            if(choice == "A"){
                                int damage = player->getAttack() - getDefense();
                                if(damage > 0){
                                    setCurrentHealth(getCurrentHealth() - damage);
                                    if(getCurrentHealth() < 0){
                                        break;
                                    }
                                }
                                int injury = getAttack() - player->getDefense();
                                if(injury > 0){
                                    player->setCurrentHealth(player->getCurrentHealth() - injury);
                                }

                                if(player->getCurrentHealth() < 0){
                                    cout << "> You are dead." << endl;
                                    cout << "--- GAME OVER ---" << endl;
                                    exit(0);
                                }

                                cout << "> Enemy's HP:" << getCurrentHealth() << "/" << getMaxHealth() << endl;
                                cout << "> Your HP:" << player->getCurrentHealth() << "/" <<  player->getMaxHealth() << endl;

                            }else if(choice == "B"){
                                //player->changeRoom(player->getPreviousRoom());
                                return 1;
                            }else if(choice == "C"){
                                int length = player->getInventory().size();
                                if(length > 0){
                                    cout << endl;
                                    cout << "[Inventory]" << endl;
                                    for(int i=0; i<length; i++){
                                        cout << i+1 << ". " << player->getInventory()[i].getName() << endl;
                                    }
                                    while(1){
                                        cout << "> Enter the name of item you want to use." << endl;
                                        cout << "(Q) exit inventory" << endl;
                                        string item;
                                        cin >> item; 
                                        if(item == "scroll"){
                                            player->increaseStates(15,15,15);
                                            cout << "[Enhancement]" << endl;
                                            cout << "- Health  +15" << endl;
                                            cout << "- Attack  +15" << endl;
                                            cout << "- Defense +15" << endl;
                                            break;
                                        }else if(item == "healing_potion"){
                                            int hp = player->getCurrentHealth()+50;
                                            if(hp > player->getMaxHealth()){
                                                hp = player->getMaxHealth();
                                            }
                                            player->setCurrentHealth(hp);
                                            cout << "> Your health is recover to " << player->getCurrentHealth() << "." << endl;
                                            break;
                                        }else if(item == "poison"){
                                            int df = getDefense()-21;
                                            if(df < 0){
                                                df = 0;
                                            }
                                            setDefense(df);
                                            cout << "Enemy's defense is decrease to " << getDefense() << "." << endl;
                                            break;
                                        }else if(item == "Q"){
                                            break;
                                        }else{
                                            continue;
                                        }
                                    }
                                }else{
                                    cout << "> Your inventory is empty." << endl;
                                }
                            }else if(choice == "D"){
                                player->triggerEvent(a);
                            }else{
                                continue;
                            }
                        }else{
                            cout << "You lose." << endl;
                            return 0;
                        }
                    }
                    cout << "> You defeat the monster." << endl;
                    cout << "> You get the reward of $" << getAttack() << " gold." << endl << endl; 
                    player->addGold(getAttack());
                    break;
                }else{
                    return 1;
                }
            }else if(reply == "B"){
                //player->changeRoom(player->getPreviousRoom());
                return 1;
            }else if(reply == "C"){
                player->triggerEvent(a);
            }else{
                continue;
            }
        }
        return 0;
    }
}