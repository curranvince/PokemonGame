//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Wild Pokemon Class - Implementation

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

#include "WildPokemon.h"

using namespace std;

WildPokemon::WildPokemon() {
    
}

WildPokemon::WildPokemon(int newNum, string newPokeName, int newHP, int newAttack, int newDefense, int newSpeed, int newMax, string newType1, string newType2, int newX, int newY) {
    Pokemon::setLevel(1);
    Pokemon::setNum(newNum);
    Pokemon::setPokeName(newPokeName);
    Pokemon::setHP(newHP);
    Pokemon::setMaxHP(newHP);
    Pokemon::setBaseHP(newHP);
    Pokemon::setAttack(newAttack);
    Pokemon::setBaseAttack(newAttack);
    Pokemon::setDefense(newDefense);
    Pokemon::setBaseDefense(newDefense);
    Pokemon::setSpeed(newSpeed);
    Pokemon::setBaseSpeed(newSpeed);
    Pokemon::setMax(newMax);
    Pokemon::setType1(newType1);
    Pokemon::setType2(newType2);
    Pokemon::setAlive(true);
    x = newX;
    y = newY;
}

void WildPokemon::setX(int newX) {
    x = newX;
}

void WildPokemon::setY(int newY) {
    y = newY;
}

int WildPokemon::getX() {
    return x;
}

int WildPokemon::getY() {
    return y;
}

