//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Trainer Class - Implementation

#include <iostream>
#include <string>
#include <vector>

#include "Trainer.h"

using namespace std;

Trainer::Trainer() {
    wildPokemonEncounters = 0;
    pokeballs = 0;
    badges = 0;
    points = 0;
}

Trainer::Trainer(string newName, int newPokeballs, int newBadges, int newX, int newY, Pokemon newActive, vector<Pokemon> newParty) {
    points = 0;
    wildPokemonEncounters = 0;
    name = newName;
    pokeballs = newPokeballs;
    badges = newBadges;
    x = newX;
    y = newY;
    activePokemon = newActive;
    if (newParty.size() > 0) {
        for (int i = 0; i < newParty.size(); i++) {
            party.at(i) = newParty.at(i);
        }
    }
}

void Trainer::setName(std::string newName) {
    name = newName;
}

void Trainer::setPokeballs(int newPokeballs) {
    pokeballs = newPokeballs;
}

void Trainer::setPoints(int newPoints) {
    points = newPoints;
}
        
void Trainer::setBadges(int newBadges) {
    badges = newBadges;
}

void Trainer::setWildPokemonEncounters(int newWildPokeEncounter) {
    wildPokemonEncounters = newWildPokeEncounter;
}

void Trainer::setX(int newX) {
    x = newX;
}

void Trainer::setY(int newY) {
    y = newY;
}

void Trainer::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}


string Trainer::getName() {
    return name;
}

int Trainer::getPokeballs() {
    return pokeballs;
}

int Trainer::getPoints() {
    return points;
}

int Trainer::getBadges() {
    return badges;
}

int Trainer::getWildPokemonEncounters() {
    return wildPokemonEncounters;
}

int Trainer::getX() {
    return x;
}

int Trainer::getY() {
    return y;
}

void Trainer::setActive(Pokemon newActive) {
    activePokemon.setHP(newActive.getHP());
    activePokemon.setAttack(newActive.getAttack());
    activePokemon.setDefense(newActive.getDefense());
    activePokemon.setSpeed(newActive.getSpeed());
    activePokemon.setPokeName(newActive.getPokeName());
    activePokemon.setLevel(newActive.getLevel());
    activePokemon.setMax(newActive.getMax());
    activePokemon.setMaxHP(newActive.getMaxHP());
    activePokemon.setBaseHP(newActive.getBaseHP());
    activePokemon.setBaseAttack(newActive.getBaseAttack());
    activePokemon.setBaseDefense(newActive.getBaseDefense());
    activePokemon.setBaseSpeed(newActive.getBaseSpeed());
    activePokemon.setType1(newActive.getType1());
    activePokemon.setType2(newActive.getType2());
    activePokemon.setAlive(true);
}

void Trainer::addToParty(Pokemon newMember) {
    party.insert(party.end(), newMember);
}

void Trainer::printActive() {
    activePokemon.printPokeStats();
}

void Trainer::printParty() {
    cout << "Name: " << activePokemon.getPokeName() << " (ACTIVE), HP: " << activePokemon.getHP() << ", A: " << activePokemon.getAttack() << ", D: " 
        << activePokemon.getDefense() << ", S: " << activePokemon.getSpeed() << ", M: " << activePokemon.getMax() << endl;
    for (int i = 0; i < party.size(); i++) {
        party[i].printPokeStats();
    }
}

void Trainer::levelUpAt(int index) {
    if (index == 1) {
        activePokemon.levelUp();
        cout << "Congratulations, " << activePokemon.getPokeName() << " is now level " << activePokemon.getLevel() <<  "." << endl;
    } else {
        party[index-2].levelUp();
        cout << "Congratulations, " << party[index-2].getPokeName() << " is now level " << party[index-2].getLevel() <<  "." << endl;
    }
}

void Trainer::addToPokedex(Pokemon newMember) {
    pokedex.insert(pokedex.end(), newMember);
}

void Trainer::changeActive() {
    string choice;
    int newOne;
    int livingIndex[6];
    bool inputValid = false;
    int liveCounter = 0;
    for (int i = 0; i < party.size(); i++) {
        if (party.at(i).isAlive()) {
            livingIndex[liveCounter] = i;
            liveCounter++;
        }
    }
    cout << "Choose a new active Pokemon from your party." << endl;
    for (int i = 1; i <= liveCounter; i++) {
        cout << i << ". " << party.at(livingIndex[i-1]).getPokeName() << endl;
    }
    while (inputValid == false) {
        getline(cin, choice);
        if ((choice == "1") or (choice == "2") or (choice == "3") or (choice == "4") or (choice == "5")) {    
            newOne = stoi(choice);
            if ((newOne > 0) and (newOne <= liveCounter)) {
                party.push_back(activePokemon);
                activePokemon = party.at(livingIndex[newOne-1]);
                party.erase(party.begin()+livingIndex[newOne-1]);
                cout << "Active Pokemon has been updated to: " << activePokemon.getPokeName() << endl;
                inputValid = true;
            } else {
                cout << "Please input a valid number." << endl;
            }
        } else {
            cout << "Please input a valid number." << endl;
        }
    }
}

void splitLine(string sentence, char splitter, string tempArr[]) {
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

int Trainer::getNumAlive() {
    int numAlive = 0;
    if (activePokemon.isAlive() == true) {
        numAlive++;
    }
    for (int i = 0; i < 5; i++) {
        if (party[i].isAlive() == true) {
            numAlive++;
        }
    }
    return numAlive;
}

void Trainer::changeParty() {
    bool inputValid;
    string tempArr[6];
    int picks[6];
    int pickIndex, activeChoice;
    string input, input2;
    bool input2Valid;
    cout << "Please choose the 6 Pokemon you wish to carry, by number. (1 4 6 9 13 2)" << endl;
    for (int i = 0; i < pokedex.size(); i++) {
        cout << (i + 1) << ". " << pokedex[i].getPokeName() << endl;
    }
    getline(cin, input);
    splitLine(input, ' ', tempArr);
    cout << "Now pick one to be your ACTIVE Pokemon." << endl;
    for (int j = 0; j < 6; j++) {
        picks[j] = stoi(tempArr[j]);
        cout << (j + 1) << ". " << pokedex[picks[j]-1].getPokeName() << endl;
    }
    input2Valid = false;
    while (input2Valid == false) {
        getline(cin, input2);
        if ((input2 == "1") or (input2 == "2") or (input2 == "3") or (input2 == "4") or (input2 == "5") or (input2 == "6")) {
            activeChoice = stoi(input2);
            pickIndex = (activeChoice-1);
            input2Valid = true;
        } else {
            cout << "Invalid input. Please choose a number 1-6." << endl;
        }
    }
    party.erase(party.begin(), party.begin() + 5);
    for (int i = 0; i < 6; i++) {
        if (i == pickIndex) {
            setActive(pokedex[picks[pickIndex]-1]);
        } else {
            addToParty(pokedex[picks[i]-1]);
        }
    }
}

void Trainer::restPokemon() {
    if (activePokemon.getHP() < activePokemon.getMaxHP()) {
        activePokemon.setHP(activePokemon.getHP()+1);
    }
    for (int i = 0; i < party.size(); i++) {
        if (party[i].getHP() < party[i].getMaxHP()) {
            party[i].setHP(party[i].getHP()+1);
        }
    }
}

void Trainer::healPokemon() {
    if (activePokemon.getHP() < activePokemon.getMaxHP()) {
        activePokemon.setHP(activePokemon.getMaxHP());
        activePokemon.setAlive(true);
    }
    for (int i = 0; i < party.size(); i++) {
        if (party.at(i).getHP() < party.at(i).getMaxHP()) {
            party.at(i).setHP(party.at(i).getMaxHP());
            party.at(i).setAlive(true);
        }
    }
}

int Trainer::getPartySize() {
    return party.size();
}

int Trainer::getActiveSpeed() {
    return activePokemon.getSpeed();
}

int Trainer::getActiveAttack() {
    return activePokemon.getAttack();
}
int Trainer::getActiveDefense() {
    return activePokemon.getDefense();
}
int Trainer::getActiveHP() {
    return activePokemon.getHP();
}
string Trainer::getActiveName() {
    return activePokemon.getPokeName();
}
void Trainer::setActiveHP(int newHP) {
    activePokemon.setHP(newHP);
}

void Trainer::activeFaints() {
    activePokemon.setAlive(false);
    activePokemon.setHP(0);
}

int Trainer::getPokedexSize() {
    return pokedex.size();
}

int Trainer::getHPAt(int index) {
    int retV;
    if (index == 0) {
        retV = activePokemon.getHP();
    } else {
        retV = party[index-1].getHP();
    }
    return retV;
}

string Trainer::getNameAt(int index) {
    string retV;
    if (index == 0) {
        retV = activePokemon.getPokeName();
    } else {
        retV = party[index-1].getPokeName();
    }
    return retV;
}

void Trainer::setHPAt(int index, int value) {
    if (index == 0) {
        activePokemon.setHP(value);
    } else {
        party[index-1].setHP(value);
    }
}

void Trainer::wonGymBattle() {
    badges += 1;
    pokeballs += 5;
    points += 60;
}

Pokemon Trainer::getPokemonAt(int index) {
    if (index == 0) {
        return activePokemon;
    } else {
        return party[index-1];
    }
}

void Trainer::nextPokemon() {
    if (getNumAlive() == 0) {
        cout << "ERROR none alive. See Trainer::nextPokemon()." << endl;
    } else {
        for (int i = 0; i < getPartySize(); i++) {
            if (party[i].isAlive()) {
                addToParty(activePokemon);
                setActive(party[i]);
                party.erase(party.begin()+i);
            }
        }
    }
}