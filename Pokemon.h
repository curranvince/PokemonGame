//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Pokemon Class - Header

#ifndef POKEMON_H
#define POKEMON_H

class Pokemon
{
    private:
        std::string pokeName, type1, type2;
        int num, hp, maxHP, attack, defense, speed, max, level;
        int baseHP, baseAttack, baseDefense, baseSpeed;
        bool alive;
        
    public:
        Pokemon();
        Pokemon(int, std::string, int, int, int, int, int, std::string, std::string);
        void setNum(int);
        void setPokeName(std::string);
        void setHP(int);
        void setMaxHP(int);
        void setBaseHP(int);
        void setAttack(int);
        void setBaseAttack(int);
        void setDefense(int);
        void setBaseDefense(int);
        void setSpeed(int);
        void setBaseSpeed(int);
        void setMax(int);
        void setLevel(int);
        void setType1(std::string);
        void setType2(std::string);
        void setAlive(bool);
        std::string getPokeName();
        int getNum();
        int getHP();
        int getMaxHP();
        int getBaseHP();
        int getAttack();
        int getBaseAttack();
        int getDefense();
        int getBaseDefense();
        int getSpeed();
        int getBaseSpeed();
        int getMax();
        int getLevel();
        std::string getType1();
        std::string getType2();
        void levelUp();
        bool isAlive();
        void faint();
        void printPokeStats();
        void heal();
};

#endif