#include "NPC.h"

NPC::NPC(){

}

NPC::NPC(string a, string b, vector<Item> c):GameCharacter(a, "NPC",1,0,0){
    script = b;
    commodity = c;
}

void NPC::listCommodity(){
    int length = commodity.size();
    for(int i=0; i<length; i++){
        cout << commodity[i].getName() << " ";
    }
}

bool NPC::triggerEvent(Object* a){
    if(checkIsDead()){
        return 0;
    }else{
        Player* player = dynamic_cast<Player*>(a);
        cout << "> You run into " << getName()  << "." << endl;
        while(1){
            cout << "A. Ignore " << getName() << endl;
            cout << "B. Talk to " << getName() << endl;
            cout << "C. Check status." << endl;

            string reply;
            cin >> reply;

            if(reply == "A"){
                break;
            }else if(reply == "B"){
                cout << "> Do you need help?(y,n)" << endl;
                string answer;
                cin >> answer;
                if(answer == "y"){
                    cout << "> These are what I have:" << endl;
                    int length = getCommodity().size();
                    for(int i=0; i<length; i++){
                        cout << i+1 << ". " << getCommodity()[i].getName() << endl;
                    }
                    cout << "> Which item do you want?" << endl;
                    string choice;
                    cin >> choice;
                    int number;
                    int judge = 0;

                    for(int i=0; i<getCommodity().size(); i++){
                        if(choice == to_string(i+1)){
                            judge = 1 ;
                            number = i;
                        }
                    }
                    
                    if(judge == 1){
                        player->setInventory(getCommodity()[number]);
                        cout << "> You successfully get the " << getCommodity()[number].getName() << "." << endl << endl;
                    }else{
                        cout << "> You miss the chance to get props." << endl << endl;
                    }
                    
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
        setCurrentHealth(0);
        return 0;
    }
}

void NPC::setScript(string a){
    script = a;
}

void NPC::setCommodity(vector<Item> a){
    commodity = a;
}

string NPC::getScript(){
    return script;
}

vector<Item> NPC::getCommodity(){
    return commodity;
}
