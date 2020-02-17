//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Map Class - Implementation 

#include <iostream>
#include <fstream>

#include "Tile.h"

using namespace std;

Tile::Tile() {
    
}

Tile::Tile(int newX, int newY, char newType, bool newPlayerAt) {
    x = newX;
    y = newY;
    type = newType;
    playerAt = newPlayerAt;
}

void Tile::setX(int newX) {
    x = newX;
}

void Tile::setY(int newY) {
    y = newY;
}

void Tile::setType(char newType) {
    type = newType;
}

void Tile::setPlayerAt(bool newPlayerAt) {
    playerAt = newPlayerAt;
}

int Tile::getX() {
    return x;
}

int Tile::getY() {
    return y;
}

char Tile::getType() {
    return type;
}

bool Tile::getPlayerAt() {
    return playerAt;
}
