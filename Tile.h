//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Map Class - Header

#ifndef TILE_H
#define TILE_H

class Tile
{
    private:
        int x, y;
        char type;
        bool playerAt;
        
    public:
        Tile();
        Tile(int, int, char, bool);
        void setX(int);
        void setY(int);
        void setType(char);
        void setPlayerAt(bool);
        int getX();
        int getY();
        char getType();
        bool getPlayerAt();
};

#endif
    
