/* CSCI2270 Final Project
 *
 * Authors: Michelle De Nardis and Rebecca Robb and Rory Teehan
 *
 * For the project description, please refer to README.txt in the project file.
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>   //Necessary in order to use srand
#include "Hangman.h" //Includes Hangman class header file.

using namespace std;

int main() 
{
	
	Hangman game;       //Instantiates object game of class Hangman.
	srand(time(NULL));      //Generates random integer each time game is played to choose random word from text file

	cout << "Welcome to the Hangman Game!" << endl;            //Prints message to console.
	game.loadDirections();                                     //Calls loadDirections function on object game, prints directions to console.
	cout << "Please enter your name to begin the game: ";
	game.enterName();                                          //Calls enterName function, allows user to enter their name.
	cout << endl;
	
	game.initializeGame(0); //calls initializeGame function which calls hangmanGame function and takes over running the game
	return 0;
}
