#include "Dungeon.h"

Dungeon::Dungeon(){

}
 
void Dungeon::createPlayer(){
    string id;
    cout << "> Please enter player id:";
    cin >> id;
    player = Player(id, 100, 50, 30, 100);
    player.setCurrentRoom(&rooms[0]);
    player.setPreviousRoom(&rooms[0]);
}

void Dungeon::createMap(){
    for(int i=0; i<8; i++){
        rooms.push_back(Room());
        rooms[i].setIndex(i);
        if(i == 7){
            rooms[i].setIsExit(1);
        }else{
            rooms[i].setIsExit(0);
        }

        rooms[i].setLeftRoom(NULL);
        rooms[i].setRightRoom(NULL);
        rooms[i].setDownRoom(NULL);
        rooms[i].setUpRoom(NULL);
    }

    rooms[0].setUpRoom(&rooms[1]);
    rooms[1].setDownRoom(&rooms[0]);

    rooms[1].setLeftRoom(&rooms[2]);
    rooms[2].setRightRoom(&rooms[1]);

    rooms[1].setRightRoom(&rooms[3]);
    rooms[3].setLeftRoom(&rooms[1]);

    rooms[1].setUpRoom(&rooms[5]);
    rooms[5].setDownRoom(&rooms[1]);

    rooms[3].setUpRoom(&rooms[4]);
    rooms[4].setDownRoom(&rooms[3]);

    rooms[4].setLeftRoom(&rooms[5]);
    rooms[5].setRightRoom(&rooms[4]);

    rooms[5].setUpRoom(&rooms[6]);
    rooms[6].setDownRoom(&rooms[5]);

    rooms[6].setUpRoom(&rooms[7]);
    rooms[7].setDownRoom(&rooms[6]);
}

void Dungeon::handleMovement(){
    string movement;
    cout << endl;
    while(1){
        if(player.getCurrentRoom()->getUpRoom() != NULL){
            cout << "U. go up" << endl;
        }
        if(player.getCurrentRoom()->getDownRoom() != NULL){
            cout << "D. go down" << endl;
        }
        if(player.getCurrentRoom()->getLeftRoom() != NULL){
            cout << "L. go left" << endl;
        }
        if(player.getCurrentRoom()->getRightRoom() != NULL){
            cout << "R. go right" << endl;
        }

        cin >> movement;
        if(player.getCurrentRoom()->getUpRoom() != NULL && movement == "U"){
            player.changeRoom(player.getCurrentRoom()->getUpRoom());
            break;
        }else if(player.getCurrentRoom()->getDownRoom() != NULL && movement == "D"){
            player.changeRoom(player.getCurrentRoom()->getDownRoom());
            break;
        }else if(player.getCurrentRoom()->getLeftRoom() != NULL && movement == "L"){
            player.changeRoom(player.getCurrentRoom()->getLeftRoom());
            break;
        }else if(player.getCurrentRoom()->getRightRoom() != NULL && movement == "R"){
            player.changeRoom(player.getCurrentRoom()->getRightRoom());
            break;
        }else{
            cout << "> Wrong command!" << endl << endl;
        }
    }
    cout << endl << "[room" << player.getCurrentRoom()->getIndex() << "]" << endl;
}

void Dungeon::chooseAction(){
    int result;
    if(player.getCurrentRoom()->getObjects().size() > 0){
        result = player.getCurrentRoom()->getObjects()[0]->triggerEvent(&player);
        if(player.getCurrentRoom()->getObjects()[0]->getTag() == "Item"){
            Item* item = dynamic_cast<Item*>(player.getCurrentRoom()->getObjects()[0]);
            player.setItems(*item);
            player.getCurrentRoom()->popObject();
        }else if(player.getCurrentRoom()->getObjects()[0]->getTag() == "Gold"){
            player.getCurrentRoom()->popObject();
        }
    }
    
    while(1){
        string reply;
        if(result == 1){
            reply = "retreat";
        }else{
            cout << "A. Move" << endl;
            cout << "B. Show map" << endl;
            cout << "C. Check status" << endl;
            cout << "D. Check bag" << endl;
            cout << "E. Talk to shop" << endl;
            cout << "F. Save to file" << endl;
            cin >> reply;
        }
        if(reply == "retreat"){
            player.changeRoom(player.getPreviousRoom());
            result = 0;
        }else if(reply == "A"){
            handleMovement();
            break;
        }else if(reply == "B"){
            string room[7];
            for(int i=0; i<7; i++){
                room[i] = to_string(i);
            }
            int number = player.getCurrentRoom()->getIndex();
            room[number] = "*";
            /*
                           _______
                          |       |
                          |   7   |
                          |_______|
                           ___|___               
                          |       |              
                          |   6   |              
                          |_______|              
                           ___|___    _______     
                          |       |  |       |   
                          |   5   |--|   4   |           
                          |_______|  |_______|   
                _______    ___|___    ___|___    
               |       |  |       |  |       |   
               |   2   |--|   1   |--|   3   |   
               |_______|  |_______|  |_______|   
                           ___|___               
                          |       |              
                          |   0   |              
                          |_______|              
            */

            cout << "               _______               " << endl;
            cout << "              |       |              " << endl;
            cout << "              |   7   |              " << endl;
            cout << "              |_______|              " << endl;
            cout << "               ___|___               " << endl;
            cout << "              |       |              " << endl;
            cout << "              |   " << room[6] <<"   |              " << endl;
            cout << "              |_______|              " << endl;
            cout << "               ___|___    _______    " << endl;  
            cout << "              |       |  |       |   " << endl;
            cout << "              |   " << room[5] << "   |--|   " << room[4] << "   |   " << endl;         
            cout << "              |_______|  |_______|   " << endl;
            cout << "    _______    ___|___    ___|___    " << endl;
            cout << "   |       |  |       |  |       |   " << endl;
            cout << "   |   " << room[2] << "   |--|   " << room[1] << "   |--|   " << room[3] << "   |   " << endl;
            cout << "   |_______|  |_______|  |_______|   " << endl;
            cout << "               ___|___               " << endl;
            cout << "              |       |              " << endl;
            cout << "              |   " << room[0] << "   |              " << endl;
            cout << "              |_______|              " << endl << endl;
            break;
        }else if(reply == "C"){
            player.triggerEvent(&player);
        }else if(reply == "D"){
            while(1){
                cout << endl;
                cout << "A. Check inventory" << endl;
                cout << "B. Check items" << endl;
                cout << "(Q) Exit bag" << endl;

                string answer;
                cin >> answer;

                if(answer == "A"){
                    int length = player.getInventory().size();
                    if(length > 0){
                        cout << endl;
                        cout << "[Inventory]" << endl;
                        for(int i=0; i<length; i++){
                            cout << i+1 << ". " << player.getInventory()[i].getName() << endl;
                        }
                        cout << endl;
                    }else{
                        cout << "> Your inventory is empty." << endl << endl;
                    }
                    break;
                }else if(answer == "B"){
                    int length = player.getItems().size();
                    if(length > 0){
                        cout << endl;
                        cout << "[Items]" << endl;
                        for(int i=0; i<length; i++){
                            cout << i+1 << ". " << player.getItems()[i].getName() << endl;
                        }
                        cout << endl;
                    }else{
                        cout << "> Your don't have any item." << endl << endl;
                    }
                    break;
                }else if(answer == "Q"){
                    break;
                }else{
                    continue;
                }
            }
        }else if(reply == "E"){
            while(1){
                cout << endl;
                cout << "[Price list]" << endl;
                cout << "1.    [ Armor ]         $50   | Health +30  |      -     |      -      |" << endl;
                cout << "2.  [ Cross_Bow ]       $110  |      -      | Attack +33 |      -      |" << endl;
                cout << "3.  [ Chainmail ]       $80   |      -      |      -     | Defense +28 |" << endl; 
                cout << "4. [ Meteor_Hammer ]    $150  | Health +22  | Attack +47 |      -      |" << endl;
                cout << "5. [ Roman_Shield  ]    $130  | Health +108 |      -     | Defense +17 |" << endl;
                cout << "6. [ Trinity_Force ]    $200  | Heatth +56  | Attack +29 | Defense +33 |" << endl;
                cout << "(Q) Exit the shop" << endl;
                cout << endl;
                cout << "> Your gold: $" << player.getGold() << endl;
                cout << "> Enter the number of items you want to buy." << endl;

                string answer;
                cin >> answer;

                if(answer == "1"){
                    if(player.getGold() < 50){
                        cout << "> You don't have enough gold." << endl;
                        continue;
                    }else{
                        cout << endl;
                        cout << "> You successfully buy the Armor." << endl;
                        player.minusGold(50);
                        player.increaseStates(30,0,0);
                        cout << "> Your balance: $" << player.getGold() << endl << endl;
                        Item Armor = Item("Armor",1,0,0);
                        player.setItems(Armor);
                        break;
                    }
                }else if(answer == "2"){
                    if(player.getGold() < 120){
                        cout << "> You don't have enough gold." << endl;
                        continue;
                    }else{
                        cout << endl;
                        cout << "> You successfully buy the Cross_Bow." << endl;
                        player.minusGold(110);
                        player.increaseStates(0,33,0);
                        cout << "> Your balance: $" << player.getGold() << endl << endl; 
                        Item CrossBow = Item("CrossBow",1,0,0);
                        player.setItems(CrossBow);
                        break;
                    }
                }else if(answer == "3"){
                    if(player.getGold() < 80){
                        cout << "> You don't have enough gold." << endl;
                        continue;
                    }else{
                        cout << endl;
                        cout << "> You successfully buy the Chainmail." << endl;
                        player.minusGold(80);
                        player.increaseStates(0,0,28);
                        cout << "> Your balance: $" << player.getGold() << endl << endl;
                        Item Chainmail = Item("Chainmail",1,0,0);
                        player.setItems(Chainmail);
                        break;
                    }
                }else if(answer == "4"){
                    if(player.getGold() < 150){
                        cout << "> You don't have enough gold." << endl;
                        continue;
                    }else{
                        cout << endl;
                        cout << "> You successfully buy the Meteor_Hammer." << endl;
                        player.minusGold(150);
                        player.increaseStates(22,47,0);
                        cout << "> Your balance: $" << player.getGold() << endl << endl;
                        Item MeteorHammer = Item("MeteorHammer",1,0,0);
                        player.setItems(MeteorHammer);
                        break;
                    }
                }else if(answer == "5"){
                    if(player.getGold() < 130){
                        cout << "> You don't have enough gold." << endl << endl;
                        continue;
                    }else{
                        cout << endl;
                        cout << "> You successfully buy the Roman_Shield." << endl;
                        player.minusGold(130);
                        player.increaseStates(108,0,17);
                        cout << "> Your balance: $" << player.getGold() << endl << endl;
                        Item RomanShield = Item("RomanShield",1,0,0);
                        player.setItems(RomanShield);
                        break;
                    }
                }else if(answer == "6"){
                    if(player.getGold() < 130){
                        cout << "> You don't have enough gold." << endl;
                        continue;
                    }else{
                        cout << endl;
                        cout << "> You successfully buy the Trinity_Force." << endl;
                        player.minusGold(200);
                        player.increaseStates(56,29,33);
                        cout << "> Your balance: $" << player.getGold() << endl << endl;
                        Item TrinityForce = Item("TrinityForce",1,0,0);
                        player.setItems(TrinityForce);
                        break;
                    }
                }else if(answer == "Q"){
                    break;
                }else{
                    continue;
                }
            }
        }else if(reply == "F"){
            ofstream b;
            Player* a=&player;
            b.open("player.txt");
            b<<a->getName()<<"\n";
            b<<a->getTag()<<"\n";
            b<<a->getMaxHealth()<<"\n";
            b<<a->getCurrentHealth()<<"\n";
            b<<a->getAttack()<<"\n";
            b<<a->getDefense()<<"\n";
            b<<a->getCurrentRoom()->getIndex()<<"\n";
            b<<a->getPreviousRoom()->getIndex()<<"\n";
            b<<a->getInventory().size()<<"\n";
            for(int i=0; i<a->getInventory().size(); i++){
                b<<a->getInventory()[i].getName()<<"\n";
                b<<a->getInventory()[i].getHealth()<<"\n";
                b<<a->getInventory()[i].getAttack()<<"\n";
                b<<a->getInventory()[i].getDefense()<<"\n";
            }
            b<<a->getItems().size()<<"\n";
            for(int i=0; i<a->getItems().size(); i++){
                b<<a->getItems()[i].getName()<<"\n";
                b<<a->getItems()[i].getHealth()<<"\n";
                b<<a->getItems()[i].getAttack()<<"\n";
                b<<a->getItems()[i].getDefense()<<"\n";
            }
            b<<a->getGold()<<"\n";

            b.close();

            ofstream c;
            c.open("room.txt");
            GameCharacter* ro1 = dynamic_cast<GameCharacter*>(rooms[1].getObjects()[0]);
            c<<ro1->getCurrentHealth()<<"\n";
            if(rooms[2].getObjects().size() > 0){
                Item* ro2 = dynamic_cast<Item*>(rooms[2].getObjects()[0]);
                c<<ro2->getTag()<<"\n";
            }else{
                c<<"empty"<<"\n";
            }
            if(rooms[3].getObjects().size() > 0){
                Gold* ro3 = dynamic_cast<Gold*>(rooms[3].getObjects()[0]);
                c<<ro3->getTag()<<"\n";
            }else{
                c<<"empty"<<"\n";
            }
            GameCharacter* ro4 = dynamic_cast<GameCharacter*>(rooms[4].getObjects()[0]);
            GameCharacter* ro5 = dynamic_cast<GameCharacter*>(rooms[6].getObjects()[0]);
            c<<ro4->getCurrentHealth()<<"\n";
            c<<ro5->getCurrentHealth()<<"\n";
            c.close();
            cout << "> File successfully saved." << endl;
            exit(0);
        }else{
            continue;
        }
    }
}

bool Dungeon::checkGameLogic(){
    if(player.getCurrentRoom()->getIsExit() == 1){
        return 1;
    }else{
        return 0;
    }
}

void Dungeon::runDungeon(){
    cout << endl;
    cout << "--- WECOME TO DUNGEON ---" << endl;
    createMap();
    while(1){
        cout << "(C) Continue" << endl;
        cout << "(N) New game" << endl;

        string reply;
        cin >> reply;

        if(reply == "C"){
            ifstream a;
            a.open("player.txt");
            string name,tag;
            int maxhealth,currenthealth,attack,defense,gold;
            int temp;

            a>>name;
            a>>tag;
            a>>maxhealth;
            a>>currenthealth;
            a>>attack;
            a>>defense;
            player = Player(name,maxhealth,attack,defense,0);
            player.setCurrentHealth(currenthealth);
            a>>temp;
            player.setCurrentRoom(&rooms[temp]);
            a>>temp;
            player.setPreviousRoom(&rooms[temp]);
            a>>temp;
            for(int i=0; i<temp; i++){
                a>>name;
                a>>currenthealth;
                a>>attack;
                a>>defense; 
                player.setInventory(Item(name,currenthealth,attack,defense));
            }
            a>>temp;
            for(int i=0; i<temp; i++){
                a>>name;
                a>>currenthealth;
                a>>attack;
                a>>defense; 
                player.setItems(Item(name,currenthealth,attack,defense));
            }
            a>>temp;
            player.addGold(temp);
            a.close();

            ifstream d;
            d.open("room.txt");

            vector<Object*> v0;
            vector<Object*> v1;
            vector<Object*> v2;
            vector<Object*> v3;
            vector<Object*> v4;
            vector<Object*> v5;
            vector<Object*> v6;
            
            d>>temp;
            if(temp > 0){
                Monster* slime = new Monster("Slime",temp,37,24);
                v1.push_back(slime);
                rooms[1].setObjects(v1);
            }
            
            d>>name;
            if(name == "Item"){
                Item* longsword =  new Item("Long_sword",6,15,8);
                v2.push_back(longsword);
                rooms[2].setObjects(v2);
            }

            d>>name;
            if(name == "Gold"){
                Gold* gold = new Gold(67);
                v3.push_back(gold);
                rooms[3].setObjects(v3);
            }

            d>>temp;
            if(temp > 0){
                vector<Item> vnpc;
                Item scroll = Item("scroll",1,0,0);
                Item healingpotion = Item("healing_potion",1,0,0);
                Item poison = Item("poison",1,0,0);
                vnpc.push_back(scroll);
                vnpc.push_back(healingpotion);
                vnpc.push_back(poison);
                NPC* npc = new NPC("an elder","script",vnpc);
                v4.push_back(npc);
                rooms[4].setObjects(v4);
            }

            d>>temp;
            if(temp > 0){
                Monster* asiagodtone = new Monster("Boss",temp,88,62);
                v6.push_back(asiagodtone);
                rooms[6].setObjects(v6);
            }
            d.close();
            break;

        }else if(reply == "N"){
            createPlayer();
            vector<Object*> v0;
            vector<Object*> v1;
            vector<Object*> v2;
            vector<Object*> v3;
            vector<Object*> v4;
            vector<Object*> v5;
            vector<Object*> v6;

            Monster* slime = new Monster("Slime",50,37,24);
            v1.push_back(slime);
            rooms[1].setObjects(v1);

            Item* longsword =  new Item("Long_sword",6,15,8);
            v2.push_back(longsword);
            rooms[2].setObjects(v2);

            Gold* gold = new Gold(67);
            v3.push_back(gold);
            rooms[3].setObjects(v3);

            vector<Item> vnpc;
            Item scroll = Item("scroll",1,0,0);
            Item healingpotion = Item("healing_potion",1,0,0);
            Item poison = Item("poison",1,0,0);
            vnpc.push_back(scroll);
            vnpc.push_back(healingpotion);
            vnpc.push_back(poison);
            NPC* npc = new NPC("an elder","script",vnpc);
            v4.push_back(npc);
            rooms[4].setObjects(v4);
            
            Monster* asiagodtone = new Monster("Boss",198,88,62);
            v6.push_back(asiagodtone);
            rooms[6].setObjects(v6);
            break;
        }else{
            continue;
        }
    }
    cout << endl;
    cout << "[room" << player.getCurrentRoom()->getIndex() << "]" << endl;
    while(true){
        chooseAction();
        if(checkGameLogic() == 1){
            cout << "> You arrive at the exit." << endl;
            cout << "--- VICTORY ---" << endl;
            exit(0);
        }
    }
}