//CS1300 Fall 2019
//Author: Vincent Curran
//Recitation: Tues @2 w/ Anuj
//Project 3 Driver

#include "Pokemon.h"
#include "WildPokemon.h"
#include "Trainer.h"
#include "Tile.h"
#include "Game.h"

using namespace std;
 
int main() {
   string playerName;
   int startChoice = 0;
   int wildIndex;
   string turnChoice;
   bool validStartChoice = false;
   bool turnChoiceValid = false;
   bool gameActive = true;
   bool wonWildBattle;
   cout << "Welcome to Pokemon!" << endl << endl << "Please state your name: ";
   getline(cin, playerName);
   cout << endl << "Welcome, " << playerName << "! Before you can begin your adventure, please choose a starting Pokemon, courtesy of the Professor." << endl << "Please choose one of the following Pokemon (by number): " << endl;
   cout << "1. Bulbasur" << endl << "2. Charmander" << endl << "3. Squirtle" << endl << "4. Pikachu" << endl;
   while (validStartChoice == false) {
      cin >> startChoice;
      if ((startChoice > 0) && (startChoice <= 4)) {
         validStartChoice = true;
      } else {
         cout << "Invalid choice." << endl;
      }
   }
   Game myGame;
   myGame.readMap("pokeMap.txt");
   myGame.readPokemon("pokemon.txt");
   myGame.spawnTrainers();
   myGame.spawnWildPokemon();
   myGame.createPlayer(playerName, startChoice);
   cout << endl << endl;
   while (gameActive == true) {
      turnChoiceValid = false;
      myGame.printPlayerMap();
      myGame.printStats();
      cout << "Please choose from the following options: " << endl << endl << "1. Travel" << endl << "2. Rest" << endl << "3. Try your luck" << endl << "4. Quit the game" << endl;
      while (turnChoiceValid == false) {
         getline(cin, turnChoice);
         if ((turnChoice == "1") or (turnChoice == "2") or (turnChoice == "3") or (turnChoice == "4")) {
            turnChoiceValid = true;
         }
      }
      if (turnChoice == "1") {
         myGame.movePlayer();
         bool atACenter = myGame.checkCenter();
         if (atACenter == true) {
            myGame.centerProcedure();
         } else {
            int gymIndex = myGame.checkGym();
            if (gymIndex != 99) {
               myGame.gymProcedure(gymIndex);
            } else {
               wildIndex = myGame.checkWild();
               if (wildIndex == 99) { //no wild pokemon
               
               } else { //have an encounter
                  myGame.printWildEncounter(wildIndex);
               if ((myGame.getPlayerPokeEncounters() == 0) or (myGame.getPlayerPokeEncounters() == 1)) {
                  cout << endl << "This was one of your first two encounters, so the wild Pokemon has been added to your party." << endl;
                  myGame.addWildPokeToParty(wildIndex);
               } else { //battle with wildpokemon at wildindex
                  myGame.wildBattle(wildIndex);
               }
               myGame.incrementPlayerPokeEncounters();
               }
            }
         }
         myGame.moveWildPokemon();
         myGame.randomEvents();
      } else if (turnChoice == "2") {
         myGame.playerRest();
         myGame.moveWildPokemon();
         myGame.randomEvents();
      } else if (turnChoice == "3") {
         myGame.tryYourLuck();
         myGame.moveWildPokemon();
         myGame.randomEvents();
      } else if (turnChoice == "4") {
         cout << "You Quit!" << endl;
         gameActive = false;
      } else {
         
      }
   }
}