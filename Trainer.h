//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Trainer Class - Header

#include "Pokemon.h"

#ifndef TRAINER_H
#define TRAINER_H

class Trainer
{
    private:
        std::string name;
        int pokeballs, points, badges, wildPokemonEncounters, x, y;
        Pokemon activePokemon;
        std::vector<Pokemon> party;
        std::vector<Pokemon> pokedex;
        
    public:
        Trainer();
        Trainer(std::string, int, int, int, int, Pokemon, vector<Pokemon>); 
        void setName(std::string);
        void setPokeballs(int);
        void setPoints(int);
        void setBadges(int);
        void setWildPokemonEncounters(int);
        void setX(int);
        void setY(int);
        void setPosition(int, int);
        std::string getName();
        int getPokeballs();
        int getPoints();
        int getBadges();
        int getWildPokemonEncounters();
        int getX();
        int getY();
        void setActive(Pokemon);
        void addToParty(Pokemon);
        void addToPokedex(Pokemon);
        void levelUpAt(int);
        void printActive();
        void printParty();
        void changeActive();
        void changeParty();
        void restPokemon();
        void healPokemon();
        int getPartySize();
        int getActiveSpeed();
        int getActiveAttack();
        int getActiveDefense();
        int getActiveHP();
        std::string getActiveName();
        void setActiveHP(int);
        void activeFaints();
        int getPokedexSize();
        int getNumAlive();
        int getHPAt(int);
        std::string getNameAt(int);
        void setHPAt(int, int);
        void wonGymBattle();
        Pokemon getPokemonAt(int);
        void nextPokemon();
};

#endif

