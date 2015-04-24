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

int main() {
	Hangman game;           //Instantiates object game of class Game.
	srand(time(NULL));      //Scrambles the words differently each time the game is played.

	cout << "Welcome to the Hangman Game!" << endl;            //Prints message to console.
	game.loadDirections();                                     //Calls loadDirections function on object game, prints directions to console.
	cout << "Please enter your name to begin the game: ";
	game.enterName();                                          //Calls enterName function, allows user to enter their name.
	cout << endl;

	cout << "Hello " << game.getName() << ", please choose a level to begin." << endl;           //Calls getName function which prints user's name to console.
	cout << "Choose a difficulty level - ";
	game.chooseLevel();                                                                          //Calls chooseLevel function which allows user to select level, level is assigned appropriate text files.
	cout << endl;

	game.loadWords();    //Calls loadWords function which loads words text file into vector.

	cout << "Guess a letter for this Level " << game.getLevel() << " word." << endl;    //Calls getLevel function which prints level integer to console.

	game.scrambler();  //Calls the scrambler function which essentially runs the entire game.

	cout << "Congratulations " << game.getName() << ", you've finished the game!" << endl;            //Again prints the user's name with message.
	//cout << "You used a total of " << game.getTotalTries() << " tries. You're score is " << game.getTotalScore() << "." << endl;  //Calls getTotalTries which prints the total number of tries for the whole game
	                                                                                                                              //and getTotalScore which prints final score to the console.
	//game.results();  //Calls results function which prints final statement based on score.

}
