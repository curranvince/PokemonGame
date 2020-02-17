//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Wild Pokemon Class - Header

#include "Pokemon.h"

#ifndef WILDPOKEMON_H
#define WILDPOKEMON_H

class WildPokemon : public Pokemon
{
    private:
        int x;
        int y;
        
    public:
        WildPokemon();
        WildPokemon(int, std::string, int, int, int, int, int, std::string, std::string, int, int);
        void setX(int);
        void setY(int);
        int getX();
        int getY();
};

#endif