#ifndef GOLD_H_INCLUDED
#define GOLD_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Gold: public Object
{
private:
    int gold;
public:
    Gold();
    Gold(int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setGold(int);
    int getGold();
};

#endif // GOLD_H_INCLUDED