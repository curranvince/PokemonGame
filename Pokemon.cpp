//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Pokemon Class - Implementation 

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon() {
    num = 0;
    hp = 0;
    attack = 0;
    defense = 0;
    speed = 0;
    max = 0;
    baseHP = 0;
    baseAttack = 0;
    baseDefense = 0;
    baseSpeed = 0;
    level = 1;
    alive = true;
}

Pokemon::Pokemon(int newNum, string newPokeName, int newHP, int newAttack, int newDefense, int newSpeed, int newMax, string newType1, string newType2) {
    level = 1;
    num = newNum;
    pokeName = newPokeName;
    hp = newHP;
    baseHP = newHP;
    maxHP = newHP;
    attack = newAttack;
    baseAttack = newAttack;
    defense = newDefense;
    baseDefense = newDefense;
    speed = newSpeed;
    baseSpeed = newSpeed;
    max = newMax;
    type1 = newType1;
    type2 = newType2;
    alive = true;
}

void Pokemon::setPokeName(string newPokeName){
    pokeName = newPokeName;
}

void Pokemon::setNum(int newNum) {
    num = newNum;
}

void Pokemon::setHP(int newHP) {
    hp = newHP;
}
void Pokemon::setMaxHP(int newMaxHP) {
    maxHP = newMaxHP;
}
void Pokemon::setBaseHP(int newBaseHP) {
    baseHP = newBaseHP;
}

void Pokemon::setAttack(int newAttack) {
    attack = newAttack;
}
void Pokemon::setBaseAttack(int newAttack) {
    baseAttack = newAttack;
}

void Pokemon::setDefense(int newDefense) {
    defense = newDefense;
}
void Pokemon::setBaseDefense(int newDefense) {
    baseDefense = newDefense;
}


void Pokemon::setSpeed(int newSpeed) {
    speed = newSpeed;
}
void Pokemon::setBaseSpeed(int newSpeed) {
    baseSpeed = newSpeed;
}

void Pokemon::setMax(int newMax) {
    max = newMax;
}

void Pokemon::setLevel(int newLevel) {
    level = newLevel;
}

void Pokemon::setType1(string newType1) {
    type1 = newType1;
}
void Pokemon::setType2(string newType2) {
    type2 = newType2;
}

void Pokemon::setAlive(bool newAlive) {
    alive = newAlive;
}

string Pokemon::getPokeName() {
    return pokeName;
}

int Pokemon::getNum() {
    return num;
}

int Pokemon::getHP() {
    return hp;
}
int Pokemon::getMaxHP() {
    return maxHP;
}
int Pokemon::getBaseHP() {
    return baseHP;
}

int Pokemon::getAttack() {
    return attack;
}
int Pokemon::getBaseAttack() {
    return baseAttack;
}

int Pokemon::getDefense() {
    return defense;
}
int Pokemon::getBaseDefense() {
    return baseDefense;
}

int Pokemon::getSpeed() {
    return speed;
}
int Pokemon::getBaseSpeed() {
    return baseSpeed;
}

int Pokemon::getMax() {
    return max;
}

int Pokemon::getLevel() {
    return level;
}

string Pokemon::getType1() {
    return type1;
}

string Pokemon::getType2() {
    return type2;
}

void Pokemon::levelUp() {
    speed += ceil(0.02*baseSpeed);
    maxHP += ceil(0.02*baseHP);
    hp += ceil(0.02*baseHP);
    if (attack < max) {
        attack += ceil(0.02*baseAttack);
    }
    if (defense < max) {
        defense += ceil(0.02*baseDefense);
    }
    level++;
}

bool Pokemon::isAlive() {
    return alive;
}

void Pokemon::faint() {
    alive = false;
}

void Pokemon::printPokeStats() {
    cout << "Name: " << getPokeName() << ", HP: " << getHP() << ", A: " << getAttack() << ", D: " 
        << getDefense() << ", S: " << getSpeed() << ", M: " << getMax() << endl;
}

void Pokemon::heal() {
    hp = maxHP;
}