//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Game Class - Header



#ifndef GAME_H
#define GAME_H

class Game
{
    private:
        Pokemon pokeDatabase[151];
        int usedIndex[151];
        int numUsed;
        Tile gameMap[31][22];
        std::vector<int> gymX;
        std::vector<int> gymY;
        std::vector<int> centerX;
        std::vector<int> centerY;
        std::vector<int> waterX;
        std::vector<int> waterY;
        std::vector<int> wildInitialX;
        std::vector<int> wildInitialY;
        Trainer Player;
        Trainer trainers[15];
        WildPokemon wildPokemon[20];
        
    public:
        Game();
        //Game(Pokemon[], Tile[][], Trainer, Trainer[], Pokemon[]);
        int getPlayerPokeEncounters();
        void incrementPlayerPokeEncounters();
        void setPlayerName(std::string);
        std::string getPlayerName();
        bool readPokemon(std::string);
        void printPokemonDatabase();
        void printPokemonAt(int);
        bool readMap(std::string);
        void printWholeMap();
        void printPlayerMap();
        void setPlayerPos(int, int);
        bool checkIndex(int);
        bool checkPosition(int, int);
        bool checkPositionV2(int, int, int);
        void spawnTrainers();
        void spawnWildPokemon();
        void printTrainers();
        void printWildPokemon();
        void createPlayer(std::string, int);
        void printStats();
        bool checkPlayerPosition();
        void movePlayer();
        bool checkCenter();
        int checkGym();
        void gymProcedure(int);
        void centerProcedure();
        int checkWild();
        void playerRest();
        void addWildPokeToParty(int);
        void printWildEncounter(int);
        void tryYourLuck();
        void moveWildPokemon();
        bool playerEscape(int, int);
        void wildBattle(int);
        void randomEvents();
        void teleportWild(int);
        void teleportPlayer();
        bool calculateAttackDamage(bool, int);
        bool calculateAttackDamageGym(bool, int);
        void transferParty(int);
};

#endif