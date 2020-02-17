//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Game Class - Implementation

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>   
#include <stdlib.h>     
#include <ctime>  
#include <math.h>

#include "Pokemon.h"
#include "WildPokemon.h"
#include "Tile.h"
#include "Trainer.h"
#include "Game.h"

using namespace std;

Game::Game() {
    for (int i = 0; i < 152; i++) {
        usedIndex[i] = 0;
    }
}

int Game::getPlayerPokeEncounters() {
    return Player.getWildPokemonEncounters();
}

void Game::incrementPlayerPokeEncounters() {
    Player.setWildPokemonEncounters(Player.getWildPokemonEncounters() + 1);
}

void Game::setPlayerName(string newName) {
    Player.setName(newName);
}

string Game::getPlayerName() {
    return Player.getName();
}

void splitPokemon(string sentence, char splitter, string tempArr[]) {
    string newString;
    int counter = 0;
    sentence += splitter;
    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] != splitter) { //add char to temp string if the char is not the splitter
            newString += sentence[i];
    }   else {
            if ((sentence[i] == splitter) and (sentence[i+1] == splitter)) { //if 2 splitters in a row delete the second one
                sentence.erase(i+1,1); 
            } 
            tempArr[counter] = newString;
            counter++;
            newString = "";
        }
    }
}

bool Game::readPokemon(string fileName) { 
    bool success = true;
    string tempArray[9];
    string line;
    ifstream inFile;
    inFile.open(fileName);
    int pokeCounter = 0;
    if (inFile.fail()) {
        success = false;
    } else {
        while (getline(inFile, line)) { //loop through every line of file
            splitPokemon(line, ',', tempArray); //split line into segments of each stat
            pokeDatabase[pokeCounter].setNum(stoi(tempArray[0])); //copy all stats
            pokeDatabase[pokeCounter].setPokeName(tempArray[1]);
            pokeDatabase[pokeCounter].setHP(stoi(tempArray[2]));
            pokeDatabase[pokeCounter].setMaxHP(stoi(tempArray[2]));
            pokeDatabase[pokeCounter].setBaseHP(stoi(tempArray[2]));
            pokeDatabase[pokeCounter].setAttack(stoi(tempArray[3]));
            pokeDatabase[pokeCounter].setBaseAttack(stoi(tempArray[3]));
            pokeDatabase[pokeCounter].setDefense(stoi(tempArray[4]));
            pokeDatabase[pokeCounter].setBaseDefense(stoi(tempArray[4]));
            pokeDatabase[pokeCounter].setSpeed(stoi(tempArray[5]));
            pokeDatabase[pokeCounter].setBaseSpeed(stoi(tempArray[5]));
            pokeDatabase[pokeCounter].setMax(stoi(tempArray[6]));
            pokeDatabase[pokeCounter].setType1(tempArray[7]);
            pokeDatabase[pokeCounter].setType2(tempArray[8]);
            pokeCounter++;
            tempArray[7] = "";
            tempArray[8] = "";
        }
    }
    inFile.close();
    return success;
}


void Game::printPokemonDatabase() {
    for (int i = 0; i < 151; i++) {
        cout << "Num: " << pokeDatabase[i].getNum() <<  " Name: " << pokeDatabase[i].getPokeName() << " HP: " <<  pokeDatabase[i].getHP() << " A: " << pokeDatabase[i].getAttack() << " D: "
        << pokeDatabase[i].getDefense() << " S: " << pokeDatabase[i].getSpeed() << " M: " << pokeDatabase[i].getMax() << endl;
    }
}

void Game::printPokemonAt(int i) { 
    cout << " Name: " << pokeDatabase[i].getPokeName() << " A: " << pokeDatabase[i].getAttack() << " D: "
        << pokeDatabase[i].getDefense() << " S: " << pokeDatabase[i].getSpeed() << " M: " << pokeDatabase[i].getMax() << " Type: " << pokeDatabase[i].getType1() << " " << pokeDatabase[i].getType2() << endl;
}

void splitMap(string sentence, char tempArr[]) {
    int splCounter = 0;
    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] != ',') {  
            tempArr[splCounter] = sentence[i]; 
            splCounter++;     
        }
    }
}

bool Game::readMap(string filename) {
    bool success = true;
    char tempArr[16];
    int lineCounter = 3;
    string line;
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        success = false;
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 22; j++) {
                gameMap[i][j].setType('X');
                gameMap[i][j].setX(i);
                gameMap[i][j].setY(j);
            }
        }
        while (getline(inFile, line)) {
            for (int j = 0; j < 3; j++) {
                gameMap[lineCounter][j].setType('X');
                gameMap[lineCounter][j].setX(lineCounter);
                gameMap[lineCounter][j].setY(j);
            }
            splitMap(line, tempArr);
            for (int i = 0; i < 16; i++) {
                gameMap[lineCounter][i+3].setType(tempArr[i]);
                gameMap[lineCounter][i+3].setX(lineCounter);
                gameMap[lineCounter][i+3].setY(i+3);
                if (tempArr[i] == 'w') {
                    waterX.insert(waterX.end(), lineCounter);
                    waterY.insert(waterY.end(), (i+3));
                } else if (tempArr[i] == 'G') {
                    gymX.insert(gymX.end(), lineCounter);
                    gymY.insert(gymY.end(), (i+3));
                } else if (tempArr[i] == 'C') {
                    centerX.insert(centerX.end(), lineCounter);
                    centerY.insert(centerY.end(), (i+3));
                }
            }
            for (int i = 19; i < 22; i++) {
                gameMap[lineCounter][i].setType('X');
                gameMap[lineCounter][i].setX(lineCounter);
                gameMap[lineCounter][i].setY(i);
            }
            lineCounter++;
        }
        for (int i = 28; i < 31; i++) {
            for (int j = 0; j < 22; j++) {
                gameMap[i][j].setType('X');
                gameMap[i][j].setX(i);
                gameMap[i][j].setY(j);
            }
        }
    }
    return success;
}

void Game::printWholeMap() {
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 22; j++) {
            cout << gameMap[i][j].getType();
        }
        cout << endl;
    }
}

void Game::printPlayerMap() {
    char printChar;
    cout << endl;
    for (int i = -3; i < 4; i++) { //display 3 tiles above and below player origin
        for (int j = -3; j < 4; j++) { //display 3 tiles to left and right of player origin
            if ((i == 0) and (j == 0)) {
                printChar = '@';
            } else {
                printChar = gameMap[(Player.getX() + i)][(Player.getY() + j)].getType();
                if (printChar == 'w') { //change tiles to correct display type
                    printChar = '~';
                } else if (printChar == 'p') {
                    printChar = '*';
                }
            }
            cout << printChar;
        }
        cout << endl;
    }
    cout << endl;
}

void Game::setPlayerPos(int newX, int newY) {
    Player.setX(newX);
    Player.setY(newY);
}

bool Game::checkIndex(int toCheck) {
    int temp = 0;
    bool retV = false;
    if (numUsed == 0) {
        retV = true;
    } else {
        for (int i = 0; i < numUsed; i++) {
            if (toCheck == usedIndex[i]) {
                
            } else {
                temp++;
            }
        }
        if (temp == numUsed) {
            retV = true;
        }
    }
    return retV;
}

void Game::spawnTrainers() {
    srand (time(NULL));
    bool valid;
    int index;
    numUsed = 0;
    string names[15] = { "John", "Mary", "Tom", "Boyce", "Misty", "Ashton", "Jack", "Ashley", 
                         "Lola", "Julia", "Brody", "Pete", "David", "Chris", "Joe" };
    for (int i = 0; i < 15; i++) {
        trainers[i].setName(names[i]);
        trainers[i].setX(gymX.at(i));
        trainers[i].setY(gymY.at(i));
        int numPoke = rand() % 6 + 1;
        for (int j = 0; j < numPoke; j++) {
            valid = false;
            while (valid == false) {
                index = rand() % 151;
                if (checkIndex(index) == true) {
                    usedIndex[numUsed] = index;
                    numUsed++;
                    valid = true;
                }
            }
            if (j == 0) {
                trainers[i].setActive(pokeDatabase[index]);
            } else { 
                trainers[i].addToParty(pokeDatabase[index]);
            }
        }
    }
}

void Game::printTrainers() {
    for (int i = 0; i < 15; i++) {
        cout << trainers[i].getName() << "'s active Pokemon: ";
        trainers[i].printActive();
        cout << endl;
        trainers[i].printParty();
        cout << "X: " << trainers[i].getX() << " Y: " << trainers[i].getY() << endl;
        cout << endl;
    }
}

bool Game::checkPosition(int theX, int theY) {
    bool retV = true;
    int temp = 0;
    for (int i = 0; i < gymX.size(); i++) {
        if ((theX == gymX.at(i)) and (theY == gymY.at(i))) {
            retV = false;
        } 
    }
    for (int i = 0; i < centerX.size(); i++) {
        if ((theX == centerX.at(i)) and (theY == centerY.at(i))) {
            retV = false;
        } 
    }
    for (int i = 0; i < waterX.size(); i++) {
        if ((theX == waterX.at(i)) and (theY == waterY.at(i))) {
            retV = false;
        } 
    }
    for (int i = 0; i < wildInitialX.size(); i++) {
        if ((theX == wildInitialX.at(i)) and (theY == wildInitialY.at(i))) {
            retV = false;
        } 
    }
    if ((theX == 15) && ((theY == 9) or (theY == 10) or (theY == 11) or (theY == 12))) {
        retV = false;
    }
    return retV;
}

void Game::spawnWildPokemon() {
    srand (time(NULL));
    bool valid;
    for (int i = 0; i < 20; i++) {
        valid = false;
        int index = rand() % 151;
        while (valid == false) {
            if (checkIndex(index) == true) {
                usedIndex[numUsed] = index;
                numUsed++;
                valid = true;
            } else {
                index = rand() % 151;
            }
        }
        wildPokemon[i].setHP(pokeDatabase[index].getHP());
        wildPokemon[i].setAttack(pokeDatabase[index].getAttack());
        wildPokemon[i].setDefense(pokeDatabase[index].getDefense());
        wildPokemon[i].setSpeed(pokeDatabase[index].getSpeed());
        wildPokemon[i].setPokeName(pokeDatabase[index].getPokeName());
        wildPokemon[i].setLevel(pokeDatabase[index].getLevel());
        wildPokemon[i].setMax(pokeDatabase[index].getMax());
        wildPokemon[i].setMaxHP(pokeDatabase[index].getMaxHP());
        wildPokemon[i].setBaseHP(pokeDatabase[index].getBaseHP());
        wildPokemon[i].setBaseAttack(pokeDatabase[index].getBaseAttack());
        wildPokemon[i].setBaseDefense(pokeDatabase[index].getBaseDefense());
        wildPokemon[i].setBaseSpeed(pokeDatabase[index].getBaseSpeed());
        wildPokemon[i].setType1(pokeDatabase[index].getType1());
        wildPokemon[i].setType2(pokeDatabase[index].getType2());
        wildPokemon[i].setAlive(true);
        int randX = rand() % 25 + 3;
        int randY = rand() % 16 + 3;
        valid = false;
        while (valid == false) {
            if (checkPosition(randX, randY) == true) {
                valid = true;
            } else {
                randX = rand() % 25 + 3;
                randY = rand() % 16 + 3;
            }
        }
        wildPokemon[i].setX(randX);
        wildPokemon[i].setY(randY);
        wildInitialX.insert(wildInitialX.end(), randX);
        wildInitialY.insert(wildInitialY.end(), randY);
    }
}

void Game::printWildPokemon() {
    for (int i = 0; i < 20; i++) {
        cout << wildPokemon[i].getPokeName() << "(" << wildPokemon[i].getX() << "," <<  wildPokemon[i].getY() << ")" << endl;
    }        
}

void Game::createPlayer(string newName, int theChoice) {
    Pokemon Starter;
    Player.setName(newName);
    Player.setX(15); 
    if (theChoice == 1) {
        Player.setY(9);
        Starter = pokeDatabase[0];
    } else if (theChoice == 2) {
        Player.setY(10);
        Starter = pokeDatabase[3];
    } else if (theChoice == 3) {
        Player.setY(11);
        Starter = pokeDatabase[6];
    } else if (theChoice == 4) {
        Player.setY(12);
        Starter = pokeDatabase[24];
    }
    Player.setActive(Starter);
    Player.setPokeballs(10);
    Player.addToPokedex(Starter);
}


void Game::printStats() {
    cout << "The sun is shining, " << Player.getName() << "!." << endl << "We have " << Player.getPokeballs() << " Pokeballs left, and your Pokemon are strong." << endl << endl;
    Player.printParty();
    cout << endl;
}



bool Game::checkPlayerPosition() {
    bool retV = true;
    int temp = 0;
    char theType;
    theType = gameMap[Player.getX()][Player.getY()].getType();
    if (theType == 'w') {
        retV = false;
    }
    if ((Player.getX() < 3) or (Player.getX() > 27) or (Player.getY() < 3) or (Player.getY() > 18)) {
        retV = false;
    }
    return retV;
}

void Game::movePlayer() {
    string direction;
    bool directInputValid = false;
    while (directInputValid == false) {
        cout << "Which direction would you like to travel: (N)orth, (S)outh, (E)ast, or (W)est?" << endl;
        getline(cin, direction);
        if ((direction == "N") or (direction == "n") or (direction == "North") or (direction == "north")) {
            Player.setX(Player.getX() - 1);
            directInputValid = checkPlayerPosition();
            if (directInputValid == false) {
                Player.setX(Player.getX() + 1);
            }
        } else if ((direction == "S") or (direction == "s") or (direction == "South") or (direction == "south")) {
            Player.setX(Player.getX() + 1);
            directInputValid = checkPlayerPosition();
            if (directInputValid == false) {
                Player.setX(Player.getX() - 1);
            }
        } else if ((direction == "E") or (direction == "e") or (direction == "East") or (direction == "east")) {
            Player.setY(Player.getY() + 1);
            directInputValid = checkPlayerPosition();
            if (directInputValid == false) {
                Player.setY(Player.getY() - 1);
            }
        } else if ((direction == "W") or (direction == "w") or (direction == "West") or (direction == "west")) {
            Player.setY(Player.getY() - 1);
            directInputValid = checkPlayerPosition();
            if (directInputValid == false) {
                Player.setY(Player.getY() + 1);
            }
        } else {
            cout << "Invalid input. Please input new direction." << endl;
        }
    }
}

bool Game::checkCenter() {
    bool atCenter = false;
    for (int i = 0; i < centerX.size(); i++) {
        if ((Player.getX() == centerX.at(i)) and (Player.getY() == centerY.at(i))) {
            atCenter = true;
        }
    }
    return atCenter;
}

int Game::checkGym() {
    int gymIndex = 99;
    for (int i = 0; i < gymX.size(); i++) {
        if ((Player.getX() == gymX.at(i)) and (Player.getY() == gymY.at(i))) {
            gymIndex = i;
        }
    }
    return gymIndex;
}

void Game::centerProcedure() {
    bool change;
    string input;
    bool inputValid = false;
    cout << "Welcome to the Pokemon Center! Your party has been fully healed." << endl;
    Player.healPokemon();
    if ((Player.getPartySize() == 5) && (Player.getPokedexSize() > 6)) {
        cout << "Would you like to switch out Poekemon in party? [Y/N]" << endl;
        while (inputValid == false) {
            getline(cin, input);
            if ((input == "Y") or (input == "y") or (input == "Yes") or (input == "yes"))  {
                change = true;
                inputValid = true;
            } else if ((input == "N") or (input == "n") or (input == "No") or (input == "no")) {
                change = false;
                inputValid = true;
            } else {
                cout << "Please input a valid response. [Y/N]" << endl;
            }
        }
        if (change == true) {
            Player.changeParty();
        }    
    }
    cout << "Thanks for stopping by! Good luck on your adventure!" << endl;
}

int Game::checkWild() {
    int index = 99;
    for (int i = 0; i < 20; i++) {
        if ((wildPokemon[i].getX() == Player.getX()) or (wildPokemon[i].getX() == (Player.getX()-1)) or (wildPokemon[i].getX() == (Player.getX()-2)) or (wildPokemon[i].getX() == (Player.getX()+1)) or (wildPokemon[i].getX() == (Player.getX()+2))) {
            if ((wildPokemon[i].getY() == Player.getY()) or (wildPokemon[i].getY() == (Player.getY()-1)) or (wildPokemon[i].getY() == (Player.getY()-2)) or (wildPokemon[i].getY() == (Player.getY()+1)) or (wildPokemon[i].getY() == (Player.getY()+2))) {
                index = i;
            }
        }
    }
    return index;
}

void Game::playerRest() {
    Player.setPokeballs(Player.getPokeballs()-1);
    Player.restPokemon();
}

void Game::addWildPokeToParty(int wildIndex) {
    Pokemon newPokemon;
    newPokemon.setHP(wildPokemon[wildIndex].getMaxHP());
    newPokemon.setAttack(wildPokemon[wildIndex].getAttack());
    newPokemon.setDefense(wildPokemon[wildIndex].getDefense());
    newPokemon.setSpeed(wildPokemon[wildIndex].getSpeed());
    newPokemon.setPokeName(wildPokemon[wildIndex].getPokeName());
    newPokemon.setLevel(wildPokemon[wildIndex].getLevel());
    newPokemon.setMax(wildPokemon[wildIndex].getMax());
    newPokemon.setMaxHP(wildPokemon[wildIndex].getMaxHP());
    newPokemon.setBaseHP(wildPokemon[wildIndex].getBaseHP());
    newPokemon.setBaseAttack(wildPokemon[wildIndex].getBaseAttack());
    newPokemon.setBaseDefense(wildPokemon[wildIndex].getBaseDefense());
    newPokemon.setBaseSpeed(wildPokemon[wildIndex].getBaseSpeed());
    newPokemon.setType1(wildPokemon[wildIndex].getType1());
    newPokemon.setType2(wildPokemon[wildIndex].getType2());
    newPokemon.setAlive(true);
    wildPokemon[wildIndex].setX(99);
    wildPokemon[wildIndex].setY(99);
    if (Player.getPartySize() < 5) {
        Player.addToParty(newPokemon);
        Player.addToPokedex(newPokemon);
    } else {
        cout << "Your party is full, so the Pokemon has been transferred to your Pokedex." << endl;
        Player.addToPokedex(newPokemon);
    }
}

void Game::printWildEncounter(int wildIndex) {
    cout << "You ran into a wild Pokemon!" << endl;
    cout << "Name: " << wildPokemon[wildIndex].getPokeName() << ", HP: " << wildPokemon[wildIndex].getHP() << ", A: " << wildPokemon[wildIndex].getAttack() << ", D: " 
        << wildPokemon[wildIndex].getDefense() << ", S: " << wildPokemon[wildIndex].getSpeed() << ", M: " << wildPokemon[wildIndex].getMax() << endl << endl;
}

void Game::tryYourLuck() {
    srand (time(NULL));
    int index = -1;
    for (int i = 0; i < 20; i++) {
        if ((wildPokemon[i].getX() == Player.getX()) or (wildPokemon[i].getX() == (Player.getX()-1)) or (wildPokemon[i].getX() == (Player.getX()-2)) or (wildPokemon[i].getX() == (Player.getX()+1)) or (wildPokemon[i].getX() == (Player.getX()+2)) or (wildPokemon[i].getX() == (Player.getX()+3)) or (wildPokemon[i].getX() == (Player.getX()-3))) {
            if ((wildPokemon[i].getY() == Player.getY()) or (wildPokemon[i].getY() == (Player.getY()-1)) or (wildPokemon[i].getY() == (Player.getY()-2)) or (wildPokemon[i].getY() == (Player.getY()+1)) or (wildPokemon[i].getY() == (Player.getY()+2)) or (wildPokemon[i].getY() == (Player.getY()+3)) or (wildPokemon[i].getY() == (Player.getY()-3))) {
                index = i;
            }
        }
    }
    if (index == -1) {
        cout << "No luck today..." << endl;
    } else {
        int chance = rand() % 2;
        if (chance == 0) {
            cout << "No luck today..." << endl;
        } else {
            cout << "How lucky! A wild " << wildPokemon[index].getPokeName() << " has joined your party." << endl;
            addWildPokeToParty(index);
        }
    }
}

bool Game::checkPositionV2(int theX, int theY, int index) {
    bool retV = true;
    int temp = 0;
    for (int i = 0; i < gymX.size(); i++) {
        if ((theX == gymX.at(i)) and (theY == gymY.at(i))) {
            retV = false;
        } 
    }
    for (int i = 0; i < centerX.size(); i++) {
        if ((theX == centerX.at(i)) and (theY == centerY.at(i))) {
            retV = false;
        } 
    }
    for (int i = 0; i < waterX.size(); i++) {
        if ((theX == waterX.at(i)) and (theY == waterY.at(i))) {
            retV = false;
        } 
    }
    for (int i = 0; i < 20; i++) {
        if (index == i) {
            
        } else {
            if ((theX == wildPokemon[i].getX()) and (theY == wildPokemon[i].getY())) {
                retV = false;
            }
        }
    }
    return retV;
}

void Game::moveWildPokemon() {
    srand (time(NULL));
    bool directInputValid;
    int direction;
    for (int i = 0; i < 20; i++) {
        directInputValid = false;
        if (wildPokemon[i].getX() != 99) {
            while (directInputValid == false) {
                direction = rand() % 4;
                if (direction == 0) { //north
                    wildPokemon[i].setX(wildPokemon[i].getX() - 1);
                    directInputValid = checkPositionV2(wildPokemon[i].getX(),wildPokemon[i].getY(), i);
                    if (directInputValid == false) {
                        wildPokemon[i].setX(wildPokemon[i].getX() + 1);
                    }
                } else if (direction == 1) { //south
                    wildPokemon[i].setX(wildPokemon[i].getX() + 1);
                    directInputValid = checkPositionV2(wildPokemon[i].getX(),wildPokemon[i].getY(), i);
                    if (directInputValid == false) {
                        wildPokemon[i].setX(wildPokemon[i].getX() - 1);
                    }
                } else if (direction == 2) { //east
                    wildPokemon[i].setY(wildPokemon[i].getY() + 1);
                    directInputValid = checkPositionV2(wildPokemon[i].getX(),wildPokemon[i].getY(), i);
                    if (directInputValid == false) {
                        wildPokemon[i].setY(wildPokemon[i].getY() - 1);
                    }
                } else if (direction == 3) { //west
                    wildPokemon[i].setY(wildPokemon[i].getY() - 1);
                    directInputValid = checkPositionV2(wildPokemon[i].getX(),wildPokemon[i].getY(), i);
                    if (directInputValid == false) {
                        wildPokemon[i].setY(wildPokemon[i].getY() + 1);
                    }
                }
            }
        }
    }
}

bool Game::playerEscape(int wildIndex, int escapeAttempts) {
    srand(time(NULL));
    int F, rando;
    bool success = false;
    if (wildPokemon[wildIndex].getSpeed() < Player.getActiveSpeed()) {
        success = true;
    } else {
        F = (((Player.getActiveSpeed()*32)/((wildPokemon[wildIndex].getSpeed()/4)%256)) + 30 * escapeAttempts);
        if (F > 255) {
            success = true;
        } else {
            rando = rand() % 255;
            if (rando < F) {
                success = true;
            }
        }
    }
    return success;
}

void Game::teleportWild(int wildIndex) {
    int randX = rand() % 25 + 3;
    int randY = rand() % 16 + 3;
    bool valid = false;
    while (valid == false) {
        if (checkPosition(randX, randY) == true) {
            valid = true;
        } else {
            randX = rand() % 25 + 3;
            randY = rand() % 16 + 3;
        }
    }
    wildPokemon[wildIndex].setX(randX);
    wildPokemon[wildIndex].setY(randY);
}

bool Game::calculateAttackDamage(bool playerAttack, int wildIndex) {
    srand(time(NULL));
    bool died = false;
    int randA, randD, damage;
    if (playerAttack == true) {
        randA = rand() % Player.getActiveAttack();
        randD = rand() % wildPokemon[wildIndex].getDefense();
        if (randA > randD) {
            damage = (randA - randD);
            cout << Player.getActiveName() << " dealt " << damage << " damage!" << endl;
            wildPokemon[wildIndex].setHP(wildPokemon[wildIndex].getHP()-damage);
            if (wildPokemon[wildIndex].getHP() <= 0) {
                died = true;
            }
        } else {
            cout << Player.getActiveName() << " dealt no damage!" << endl;
        }
    } else {
        randA = rand() % wildPokemon[wildIndex].getAttack();
        randD = rand() % Player.getActiveDefense();
        if (randA > randD) {
            damage = (randA - randD);
            cout << wildPokemon[wildIndex].getPokeName() << " dealt " << damage << " damage!" << endl;
            Player.setActiveHP(Player.getActiveHP()-damage);
            if (Player.getActiveHP() <= 0) {
                died = true;
            }
        } else {
            cout << wildPokemon[wildIndex].getPokeName() << " dealt no damage!" << endl;
        }
    }
    return died;
}

void Game::teleportPlayer() {
    int compare = 1000;
    int distance, shortestDistanceIndex;
    for (int i = 0; i < centerX.size(); i++) {
        distance = sqrt(((Player.getX()-centerX[i])^2)-((Player.getY()-centerY[i])^2));
        if (distance < compare) {
            compare = distance;
            shortestDistanceIndex = i;
        }
    }
    Player.setX(centerX[shortestDistanceIndex]);
    Player.setY(centerY[shortestDistanceIndex]);
    centerProcedure();
}

void Game::wildBattle(int wildIndex) {
    srand(time(NULL));
    int escapeAttempts = 0;
    int wildEscapeAttempts = 0;
    int rando;
    bool battleOver = false;
    bool died = false;
    bool wonBattle, inputValid, successfulEscape, playerAttack, successfulWildEsc;
    string input;
    while (battleOver == false) {
        inputValid = false;
        cout << endl;
        cout << "Your ACTIVE Pokemon is: " << endl;
        Player.printActive();
        cout << "WILD Pokemon: " << endl;
        wildPokemon[wildIndex].printPokeStats();
        cout << endl << "What do you want to do (pick 1, 2, or 3): " << endl << "1. Fight" << endl << "2. Switch Active Pokemon" << endl << "3. Run" << endl;
        while (inputValid == false) {
            getline(cin, input);
            if ((input == "1") or (input == "2") or (input == "3")) {
                inputValid = true;
            } else {
                cout << "Please choose a valid option (1, 2, or 3)." << endl;
            }
        }
        if (input == "1") { //fight
            int rando = rand() % 10; 
            if (rando < 6) { //wild pokemon attacks
                if (Player.getActiveSpeed() > wildPokemon[wildIndex].getSpeed()) {
                    playerAttack = true;
                } else {
                    playerAttack = false;
                }
                if (playerAttack == true) {
                    cout << Player.getActiveName() << " attacks first." << endl;
                    died = calculateAttackDamage(playerAttack, wildIndex);
                    if (died == true) { //wild Pokemon faints
                        cout << "The wild " << wildPokemon[wildIndex].getPokeName() << " has fainted. It's HP will be fully restored and then transferred to your party." << endl;
                        addWildPokeToParty(wildIndex);
                        Player.levelUpAt(1);
                        battleOver = true;
                    } else {
                        playerAttack = false;
                        died = calculateAttackDamage(playerAttack, wildIndex);
                        if (died == true) { //active pokemon faints
                            cout << Player.getActiveName() << " has fainted. " << wildPokemon[wildIndex].getPokeName() << " leveled up." << endl;
                            wildPokemon[wildIndex].levelUp();
                            Player.activeFaints();
                            cout << endl;
                            if (Player.getNumAlive() == 0) {
                                cout << "All the Pokemon in your party have fainted. You will be taken to the nearest Pokemon center." << endl;
                                teleportPlayer();
                                battleOver = true;
                            } else {
                                Player.changeActive();
                            }
                        }
                    }
                } else {
                    cout << wildPokemon[wildIndex].getPokeName() << " attacks first." << endl;
                    died = calculateAttackDamage(playerAttack, wildIndex);
                    if (died == true) { //active pokemon faints
                        cout << "Active pokemon faints" << endl;
                        wildPokemon[wildIndex].levelUp();
                        Player.activeFaints();
                        if (Player.getNumAlive() == 0) {
                                cout << "All the Pokemon in your party have fainted. You will be taken to the nearest Pokemon center." << endl;
                                teleportPlayer();
                                battleOver = true;
                            } else {
                                Player.changeActive();
                            }
                    } else {
                        playerAttack = true;
                        died = calculateAttackDamage(playerAttack, wildIndex);
                        if (died == true) { //wild pokemon faints
                            cout << "The wild " << wildPokemon[wildIndex].getPokeName() << " has fainted. It's HP will be fully restored and then transferred to your party." << endl;
                            addWildPokeToParty(wildIndex);
                            Player.levelUpAt(1);
                            battleOver = true;
                        }
                    }
                }
            } else { //wild pokemon flees
                wildEscapeAttempts++;
                successfulWildEsc = false;
                int F = (((wildPokemon[wildIndex].getSpeed()*32)/((Player.getActiveSpeed()/4)%256)) + 30 * escapeAttempts);
                if (F > 255) {
                    successfulWildEsc = true;
                } else {
                    rando = rand() % 255;
                    if (rando < F) {
                        successfulWildEsc = true;
                    }
                }
                if (successfulWildEsc == true) {
                    teleportWild(wildIndex);
                    cout << "The wild " << wildPokemon[wildIndex].getPokeName() << " has successfully escaped!" << endl;
                    battleOver = true;
                } else { //if flee is unsuccessful, wild pokemon joins players party
                    cout << "The wild " << wildPokemon[wildIndex].getPokeName() << " tried to escape and failed! It now joins our party." << endl;
                    addWildPokeToParty(wildIndex);
                    battleOver = true;
                }
            }
        } else if (input == "2") { //switch active
            Player.changeActive();
        } else if (input == "3") { //run
            escapeAttempts++;
            successfulEscape = playerEscape(wildIndex, escapeAttempts);
            if (successfulEscape == true) {
                cout << "Your escape was successful, and you will be teleported to the nearest Pokemon Center." << endl;
                battleOver = true;
            } else {
                cout << "Your escape was unsuccessful." << endl;
            }
        } else {
            cout << "Theres a problem if you're reading this, see Game::wildBattle" << endl;
        }
    }
}

void Game::randomEvents() {
    srand(time(NULL));
    int rand1 = rand() % 10; //chance for event 1
    int rand2 = rand() % 4; //chance for event 2
    int rand3 = rand() % 5; //chance for event 3
    int rand4 = rand() % 2; //chance for Pokeballs/Poffins in event 2
    int rand5 = rand() % Player.getPartySize(); //choose pokemon in event 3
    bool choiceValid;
    string choice;
    int numChoice;
    if ((rand1 >= 0) and (rand1 < 3)) {
        
    }
    if (rand2 == 0) {
        if (rand4 == 0) {
            Player.setPokeballs(Player.getPokeballs() + 2);
            cout << endl << "Great news! You've found some Pokeballs stashed away. You now have " << Player.getPokeballs() << " Pokeballs." << endl;
        } else if (rand4 == 1) {
            cout << endl << "Great news! You've found some Poffins, choose which Pokemon in your party to feed them to and level up." << endl;
            for (int i = 0; i <= Player.getPartySize(); i++) {
                cout << (i+1) << ". " << Player.getNameAt(i) << endl;
            }
            choiceValid = false;
            while (choiceValid == false) {
                getline(cin, choice);
                if ((choice == "1") or (choice == "2") or (choice == "3") or (choice == "4") or (choice == "5") or (choice == "6")) {
                    numChoice = stoi(choice);
                    if ((numChoice > 0) && (numChoice <= (Player.getPartySize()+1))) {
                        Player.levelUpAt(numChoice);
                        choiceValid = true;
                    } else {
                        cout << "Please input a VALID NUMBER." << endl;
                    }
                } else {
                    cout << "Please input a valid number." << endl;
                }
            }
        } else {
            cout << "Error! See Game::randomEvents" << endl;
        }
    }
    if (rand3 == 0) {
        Player.setHPAt(rand5, (Player.getHPAt(rand5)/2));
        cout << Player.getNameAt(rand5) << " has fallen ill and lost half its health. Visit a Pokemon Center to restore it." << endl;  
    }
}

bool Game::calculateAttackDamageGym(bool playerAttack, int gymIndex) {
    srand(time(NULL));
    bool died = false;
    int randA, randD, damage;
    if (playerAttack == true) {
        randA = rand() % Player.getActiveAttack();
        randD = rand() % trainers[gymIndex].getActiveDefense();
        if (randA > randD) {
            damage = (randA - randD);
            cout << Player.getActiveName() << " dealt " << damage << " damage!" << endl;
            trainers[gymIndex].setActiveHP(trainers[gymIndex].getActiveHP()-damage);
            if (trainers[gymIndex].getActiveHP() <= 0) {
                died = true;
            }
        } else {
            cout << Player.getActiveName() << " dealt no damage!" << endl;
        }
    } else {
        randA = rand() % trainers[gymIndex].getActiveAttack();
        randD = rand() % Player.getActiveDefense();
        if (randA > randD) {
            damage = (randA - randD);
            cout << trainers[gymIndex].getActiveName() << " dealt " << damage << " damage!" << endl;
            Player.setActiveHP(Player.getActiveHP()-damage);
            if (Player.getActiveHP() <= 0) {
                died = true;
            }
        } else {
            cout << trainers[gymIndex].getActiveName() << " dealt no damage!" << endl;
        }
    }
    return died;
}

void Game::transferParty(int gymIndex) {
    for (int i = 0; i < trainers[gymIndex].getPartySize(); i++) {
        if (Player.getPartySize() < 5) {
            cout << trainers[gymIndex].getPokemonAt(i).getPokeName() << " has been added to your party." << endl;
            Player.addToParty(trainers[gymIndex].getPokemonAt(i));
            Player.addToPokedex(trainers[gymIndex].getPokemonAt(i));
        } else {
            cout << "Your party is full, so " << trainers[gymIndex].getPokemonAt(i).getPokeName() << " has been transferred to your Pokedex." << endl;
            Player.addToPokedex(trainers[gymIndex].getPokemonAt(i));
        }
    } 
}

void Game::gymProcedure(int gymIndex) {
    string input;
    bool inputValid, playerWon, playerAttack, died;
    bool battleOver = false;
    cout << "Welcome to " << trainers[gymIndex].getName() << "'s Gym! Defeat them in battle to gain a badge." << endl;
    while (battleOver == false) {
        inputValid = false;
        cout << endl << "Your ACTIVE Pokemon is: " << endl;
        Player.printActive();
        cout << endl << "Opponent's ACTIVE Pokemon is: " << endl;
        trainers[gymIndex].printActive();
        cout << endl;
        cout << endl << "What do you want to do (pick 1 or 2):" << endl << "1. Fight" << endl << "2. Switch Active Pokemon" << endl;
        while (inputValid == false) {
            getline(cin, input);
            if ((input == "1") or (input == "2")) {
                inputValid = true;
            } else {
                cout << "Please input a valid number (1 or 2)." << endl;
            }
        }
        if (input == "1") { //fight
            if (Player.getActiveSpeed() > trainers[gymIndex].getActiveSpeed()) {
                playerAttack = true;
            } else {
                playerAttack = false;
            }
            if (playerAttack == true) {
                cout << Player.getActiveName() << " attacks first." << endl;
                died = calculateAttackDamageGym(playerAttack, gymIndex);
                if (died == true) { //opponents pokemon faints
                    cout << "The opponent's " << trainers[gymIndex].getActiveName() << " has fainted!" << endl;
                    Player.levelUpAt(1);
                    trainers[gymIndex].activeFaints();
                    if (trainers[gymIndex].getNumAlive() == 0) {
                        cout << "You have defeated all Pokemon in the opponents party. You have been awarded their entire party, a badge, 5 pokeballs, and 60 points. " << endl;
                        transferParty(gymIndex);
                        Player.wonGymBattle();
                        gymX[gymIndex] = 99;
                        gymY[gymIndex] = 99;
                        battleOver = true;
                    } else {
                        trainers[gymIndex].nextPokemon();
                    }
                } else {
                    playerAttack = false;
                    died = calculateAttackDamageGym(playerAttack, gymIndex);
                    if (died == true) { //active pokemon faints
                        cout << Player.getActiveName() << " has fainted. " << trainers[gymIndex].getActiveName() << " leveled up." << endl;
                        trainers[gymIndex].levelUpAt(1);
                        Player.activeFaints();
                        cout << endl;
                        if (Player.getNumAlive() == 0) {
                            cout << "All the Pokemon in your party have fainted. You will be taken to the nearest Pokemon center." << endl;
                            teleportPlayer();
                            battleOver = true;
                        } else {
                            Player.changeActive();
                        }
                    }
                }
            } else {
                cout << trainers[gymIndex].getActiveName() << " attacks first." << endl;
                died = calculateAttackDamageGym(playerAttack, gymIndex);
                if (died == true) { //active pokemon faints
                    cout << "Active pokemon faints." << endl;
                    trainers[gymIndex].levelUpAt(1);
                    Player.activeFaints();
                    if (Player.getNumAlive() == 0) {
                        cout << "All the Pokemon in your party have fainted. You will be taken to the nearest Pokemon center." << endl;
                        teleportPlayer();
                        battleOver = true;
                    } else {
                        Player.changeActive();
                    }
                } else {
                    playerAttack = true;
                    died = calculateAttackDamageGym(playerAttack, gymIndex);
                    if (died == true) { //opponent pokemon faints
                        cout << "The opponent's " << trainers[gymIndex].getActiveName() << " has fainted!" << endl;
                        Player.levelUpAt(1);
                        trainers[gymIndex].activeFaints();
                        if (trainers[gymIndex].getNumAlive() == 0) {
                            cout << "You have defeated all Pokemon in the opponents party. You have been awarded their entire party, a badge, 5 pokeballs, and 60 points. " << endl;
                            transferParty(gymIndex);
                            Player.wonGymBattle();
                            gymX[gymIndex] = 99;
                            gymY[gymIndex] = 99;
                            battleOver = true;
                        } else {  
                            trainers[gymIndex].nextPokemon();
                        }
                    }
                }
            }
        } else { //switch active
            Player.changeActive();
        }
    }
}

