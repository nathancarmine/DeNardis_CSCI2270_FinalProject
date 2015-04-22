#include "Hangman.h"
#include <cstdlib>    //Necessary preprocessor directives for following components
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> words; //These vectors are used in most of the functions below, hence global scope.

Hangman::Hangman() {
    totalTries = 0;
}

Hangman::~Hangman() {
    //dtor
}

/*This function prints the directions of the game to the console, keeps the main.cpp neat to define them here.*/
void Hangman::loadDirections() const {
	cout << "To play the game, choose a level ranging from 1 to 8 - the higher the level the greater the difficulty. ";
	cout << "To begin the game you must guess a letter. With each\nincorrect guess a body part will be added to the hangman's tree." << endl;
	cout << "You are allowed 5 incorrect guesses, but at 6 incorrect guesses you will lose\nthe game and be hung." << endl;
	cout << "Try and avoid the noose. Good Luck!" << endl << endl;

}

/*This function allows the user to enter their full name (first and last), the getline function captures the entire string as well
as white space; the data member name is assigned the string and prints the user's name to the console when called by the getName function.*/
void Hangman::enterName() {
	string n;
	getline(cin, n);
	name = n;
}

/*This function allows the user to choose a level from 1 to 8, each level is associated with a words text file (containing 10 words) and a hints
text file (containing 10 hints corresponding to the 10 words).  The while true loop was suggested by Thyago and is easier to implement for so
many levels. The last else if statement ensures that an infinite loop is not generated if the user enters a character rather than an integer. The
final else statement informs the user that they have entered an integer not between 1 and 8.
The data member level is assigned the int lev and prints the level number to the console when called by the getLevel function.*/
void Hangman::chooseLevel() {
	int lev;
	string s;
	while (true) {
	 	cin >> lev;
		level = lev;
	    if (level == 1) {
			wordsFile = "level_1_words.txt";
			break;
		}
		else if (level == 2) {
			wordsFile = "level_2_words.txt";
			break;
		}
		else if (level == 3) {
			wordsFile = "level_3_words.txt";
			break;
		}
		else if (level == 4) {
			wordsFile = "level_4_words.txt";
			break;
		}
		else if (level == 5) {
			wordsFile = "level_5_words.txt";
			break;
		}
		else if (level == 6) {
			wordsFile = "level_6_words.txt";
			break;
		}
		else if (level == 7) {
			wordsFile = "level_7_words.txt";
			break;
		}
		else if (level == 8) {
			wordsFile = "level_8_words.txt";
			break;
		}
		else if (cin.fail()) {
			cin.clear();
			getline(cin, s);
			cout << "There is no such level, please choose from the options listed." << endl;
			continue;
		}
		else {
			cout << "There is no such level, please choose from the options listed." << endl;
			continue;
		}
	}
}

/*This function opens the words text files, checks for errors, loads the words into a vector called words, and then closes the words text file.*/
void Hangman::loadWords() {
	ifstream input;
	input.open(wordsFile.c_str());

	if (input.fail()) {
		cout << "Could not open " << wordsFile;
		exit(1);
	}

	while (!input.eof()) {
		string s;
		input >> s;
		words.push_back(s);
	}

	input.close();
}


/*This function is the "meat" of the program. I couldn't figure out how to simplify it without messing up the entire game, so I'll describe each
step within the function.*/
void Hangman::scrambler() {

	for (int i=0; i<words.size(); i++) {  //This loop takes a word from the words vector and puts it into a string called letters,
		string letters;                   //thus each letter of the word occupies its own index of the string. Note that the rest of the code
		letters = words[i];               //is contained in the body of this for loop, which I found to be necessary for the game to operate proper
                                          //memory snapshot: word cat is placed in string {c, a, t}

        vector<string> lettersVector;                  //Here I declare a vector of letters and fill the vector with the letters
		for (int i=0; i<letters.size(); i++){   //of the word from the words vector above.
			lettersVector.push_back(letters.substr(i, 1));    //memory snapshot: integer vector created {c, a, t}
		}

		for (int i=0; i<letters.size(); i++) {
            cout<<"_";
		}

		cout << endl;
		string guess;

		int incorrectGuesses = 0; //Initializes local variables to record # of tries to guess letter

		while (guess != words[i]) {                 //while loop runs while user's guess is not the word

			cout<<"Guess: ";
			cin >> guess;                           //allows user to input a string guess
			//Following for loop for converting uppercase to lower case found at http://www.cplusplus.com/forum/beginner/613/.
			for (int i=0; i<guess.length(); i++) {  //allows user to enter upper or lowercase letters
				guess[i]=tolower(guess[i]);         //converts uppercase letters to lowercase letters
			}
            for (int i=0; i<letters.size(); i++){

                if (guess == lettersVector[i]){
                    cout<<"That's correct! Guess another letter or solve the word."<<endl;
                    int index = i;
                    for (int i=0; i<index; i++){
                        cout<<"_";
                    }
                    cout<<lettersVector[i];
                    for (int i=index+1; i<letters.size(); i++) {
                        cout<<"_";
                    }
                    cout<<endl;
                }
           }
		}


		//totalTries += tries;      //sum of tries used per level

	} //end of for loop body, for loop ends when last word in words text file is unscrambled
}

/*Function to print results based on final score.*/
void Hangman::results() const {
	if (totalTries == 0 || totalTries < 60)
		cout << "Keep trying, you can get a better score!" << endl;
	else if (totalTries == 100)
		cout << "You're a Word Scrambler master!" << endl;
	else if (totalTries < 100 && totalTries >= 80)
		cout << "Great job!" << endl;
	else
		cout << "Nice try!" << endl;
}
