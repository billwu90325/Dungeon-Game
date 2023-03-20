#include "GameCharacter.h"

GameCharacter::GameCharacter(){

}

GameCharacter::GameCharacter(string a, string b, int c, int d, int e):Object(a,b){
    maxHealth = c;
    currentHealth = c;
    attack = d;
    defense = e;
}

bool GameCharacter::checkIsDead(){
    if(currentHealth <= 0){
        return 1;
    }else{
        return 0;
    }
}

int GameCharacter::takeDamage(int a){
    return currentHealth -= a;
}

void GameCharacter::setMaxHealth(int a){
    maxHealth = a;
}

void GameCharacter::setCurrentHealth(int a){
    currentHealth = a;
}

void GameCharacter::setAttack(int a){
    attack  = a;
}

void GameCharacter::setDefense(int a){
    defense = a;
}

int GameCharacter::getMaxHealth(){
    return maxHealth;
}

int GameCharacter::getCurrentHealth(){
    return currentHealth;
}

int GameCharacter::getAttack(){
    return attack;
}

int GameCharacter::getDefense(){
    return defense;
}
