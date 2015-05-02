#include "Hangman.h"
#include <iostream>
#include <cstdlib>    //Necessary preprocessor directives for following components
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

Hangman::Hangman()  //constructor to initialize queue
{
    queueSize = 7;
    bodyQueue = new string[queueSize];  //queue is used for the body parts of the hangman
    queueTail = 0;
    queueHead = 0;
}

Hangman::~Hangman()  //destructor deletes queue
{
    delete []bodyQueue;
}

/*
Function prototype:
void Hangman::loadDirections() const

Function description:
This function prints the directions of the game to the console, keeps the main.cpp neat to define them here.

Example:
Hangman game;
game.loadDirections

Pre-conditions: none
Post-conditions: none
*/
void Hangman::loadDirections() const
{
	cout << "\nDirections:" << endl;
	cout << "  -Choose a difficulty level - (1) Easy (2) Medium or (3) Hard" << endl;
	cout << "  -I will choose a word based on the difficulty you've chosen" << endl;
	cout << "  -Once I've chosen a word, you can guess a letter" << endl;
	cout << "  -For each incorrect guess I will add a body part to the hanged man" << endl;
	cout << "  -I'll keep track of how many words you guess correctly" << endl;
	cout << "  -The object is to see how many words you guess before I complete\n   my drawing (6 incorrect guesses)" << endl;
	cout << "  -You will earn 10 points for each correct guess and lose 10 points for each\n   incorrect guess" << endl;
	cout << "\nGood Luck and try to avoid the noose!\n" << endl;
}


/*
Function prototype:
void Hangman::initializeGame()

Function description:
This function initializes the game levels and loads the words from the word files.

Example:
Hangman game;
game.initializeGame();

Pre-conditions: none
Post-conditions: words vector is filled with words from particular level, new game is started with function call to hangmanGame
*/
void Hangman::initializeGame()
{
    score = 0;
    words.clear();  //clears the words vector so new words can be loaded with each new game
    cout << "Hello " << name << ", please choose a level to begin." << endl;           //Calls getName function which prints user's name to console.
	cout << "Choose a difficulty level - ";
	chooseLevel();                                                                          //Calls chooseLevel function which allows user to select level, level is assigned appropriate text files.
	cout << endl;
    //loadWords();    //Calls loadWords function which loads words text file into vector.

	cout << "Guess a letter for this Level " << level << " word." << endl;    //Calls getLevel function which prints level integer to console.

	hangmanGame();  //Calls the hangmanGame function which essentially runs the entire game.

}

/*This function allows the user to enter the name they wish to be referred to as. The getline function captures the entire string as well
as white space; the data member name is assigned the string and prints the user's name to the console when called by the getName function.*/
void Hangman::enterName()
{
	string n;
	getline(cin, n);
	name = n;
}

/*
Function prototype:
void Hangman::chooseLevel()

Function description:
This function allows the user to choose a difficulty level from 1 to 3, each level is associated with a words text file (containing 10 words).
The data member level is assigned the int lev and prints the level number to the console when called by the getLevel function.

Example:
Hangman game;
game.chooseLevel();

Pre-conditions: called in initializeGame function
Post-conditions: picks appropriate text file based on level chosen, must be called before loadWords function (and it is in the initializeGame function).
*/
void Hangman::chooseLevel()
{
	int lev = 0;
	string s;
	while(lev == 0) {
        cout << "(1) Easy (2) Medium or (3) Hard: ";
		getline(cin, s);
		if(s == "1" || s == "2" || s == "3") {
			lev = atoi(s.c_str());
			level = lev;
			switch(lev) {
				case 1:
					words = {"ring", "dent", "home", "acute", "ghost", "dance", "candy", "state", "moment", "friend"};
					break;
				case 2:
					words = {"bird", "short", "grand", "arrow", "price", "frost", "vision", "danger", "modern", "hustle"};
					break;
				case 3:
					words = {"climb", "silver", "escape", "bucket", "shadow", "attack", "decode", "pistol", "whisper", "incline"};
					break;
			}
		}
		else
			cout << "There is no such level, please choose from the options listed." << endl;
	}
}


/*
Function prototype:
void Hangman::hangmanGame()

Function description:
This function is the entire game, each line is described throughout the function

Example:
Hangman game;
game.hangmanGame();

Pre-conditions: called in initializeGame function, must be called after chooseLevel and loadWords functions
Post-conditions: runs entire game and calls other functions, calls initializeGame when game is over
*/
void Hangman::hangmanGame()
{

    bool dead = false;  //boolean to see if the player guessed too many incorrect guesses
    bool winner = false;  //boolean to see if the player has guessed the word correctly or not
    resetHangman();
    while(!dead || !winner)  //while the player hasn't lost but also hasn't won
    {
        //for (int i=0; i<words.size(); i++){  //This loop takes a word from the words vector and puts it into a string called letters,
            int randomInt;
            randomInt = rand() % 10 + 1;   //generates a random integer between 1 and 10
            string letters;                   //declares a string to store randomly chosen word from text file
            letters = words[randomInt];         //each letter of the word occupies its own index of the string, memory snapshot: word cat is placed in string {c, a, t}

            vector<char> lettersVector;  //declare a vector of letters and fill the vector with the letters of the word from the words vector

            for (int i=0; i<letters.size(); i++)
            {
                lettersVector.push_back(letters[i]);    //memory snapshot: string vector created {c, a, t}
            }

            vector<string> underscores;  //vector for the blank spaces representing the incomplete part(s) of the word
            for (int i=0; i<letters.size(); i++)
            {
                underscores.push_back("_");
                cout<<underscores[i]<<" ";
            }
            cout << endl;
            cout << endl;

            string guess;  //this is the cin letter of the player's guess; gets overwritten with every new guess
            vector<char> correctGuesses;  //vector to hold correct guesses
			vector<char> allGuesses;
            vector<string> hangman;  //vector to hold body parts added to tree
			bool endgame = false;

            while (!endgame)  //while loop runs while user's guess is not the completed word
            {
                cout<<"Guess: ";
				getline(cin, guess);
				char guessChar = guess[0];
				guessChar=tolower(guessChar);

				if(isalpha(guessChar) && (find(allGuesses.begin(), allGuesses.end(), guessChar) == allGuesses.end()))
				{	
					allGuesses.push_back(guessChar);
					bool correct = false;  //boolean to check if letter is correct or incorrect

					for (int i=0; i<letters.size(); i++)  //takes the player's guess and checks it against every letter in the word
					{
						int index = 0;
						if (guessChar == lettersVector[i])   //if guess is a letter in the lettersVector
						{
							cout<<"That's correct! ";
							index = i;                         //index is recorded
							underscores[index] = lettersVector[i];  //and in the underscore vector the corresponding underscore is replaced with the letter
							correctGuesses.push_back(guessChar);   //the letter is added to the correctGuesses vector
							correct = true;                //correct is set to true
							score += 10;       //score recorded

							for(int i=0; i<underscores.size(); i++)  //prints underscores with letters guessed correctly
							{
								cout<<underscores[i]<<" ";
							}
							cout<<endl;
							cout<<endl;

							if(correctGuesses.size() == letters.size())  //condition if all letters guessed correctly, sets winner bool to true
							{
								cout << "You WIN! Your final score is: " << score << endl;
								if (score <= 0)
									cout << "Keep trying, you can get a better score!" << endl;
								else if (score > 0)
									cout << "You're a Hangman master!" << endl;
								cout << endl;
								winner = true;
								endgame = true;
								initializeGame();
							}
						}
					}
					if(correct == false)  //if incorrect letter is guessed
					{

						string bodypart = dequeueHangman();  //then body part is dequeued and printed to console
						cout << "WRONG! The " << bodypart << " was added to your hangman." << endl;
						cout << endl;
						hangman.push_back(bodypart);  //body part added to hangman vector to keep track of body parts on gallows
						cout << "Your hangman has the following body parts: ";

						for(int i=0; i < hangman.size(); i++)  //prints body parts in hangman vector
						{
							if(i>0)
								cout<<", ";
							cout << hangman[i];
						}
						cout << endl;

						cout<<"Letters guessed: ";
						for(int i=0; i < allGuesses.size(); i++)  //prints body parts in hangman vector
						{
							if(i>0)
								cout<<", ";
							cout << allGuesses[i];
						}
						cout << endl;
						cout << endl;
						score -= 10;

						if(queueisEmpty())  //if the body parts queue is empty then the user has used up their 6 guesses and is hung
						{
							cout << "GAME OVER! You have been hung!" << endl;
							cout << " ____  " << endl;
							cout << " |  |  " << endl;
							cout << " |  O  " << endl;
							cout << " | /|\\ " << endl;
							cout << " | / \\ " << endl;
							cout << " |     " << endl;
							cout << "_|_____" << endl;
							cout << endl;
							cout << "Your final score is: " << score << endl;
							if (score <= 0)
								cout << "Keep trying, you can get a better score!" << endl;
							else if (score > 0)
								cout << "You're a Hangman master!" << endl;
							cout << endl;
							dead = true;
							endgame = true;
							initializeGame();
						}
					}
				}
				else
				{
					cout<<"Invalid input or character already guessed"<<endl;
					cout<<"Letters guessed: ";
					for(int i=0; i < allGuesses.size(); i++)  //prints body parts in hangman vector
					{
						if(i>0)
							cout<<", ";
						cout << allGuesses[i];
					}
					cout << endl;
				}
            }
        //} //end of for loop body, for loop ends when last word in words text file is unscrambled
    }

}

/*
Function prototype:
void Hangman::enqueueHangman()

Function description:
Function places the body parts of the hangman in a queue to be dequeued if an incorrect guess is made.

Example:
Hangman game;
game.enqueueHangman();

Pre-conditions: called in resetHangman function
Post-conditions: loads body parts from body text file into queue
*/
void Hangman::enqueueHangman()
{
    string body = "head,body,right arm,left arm,right leg,left leg";
    istringstream bodyText(body); //converts string "body" to stream "bodyText" for getline

    //int i = 0;
    while(!queueisFull())
    {
        getline(bodyText, body, ',');
        bodyQueue[queueTail] = body;
        queueTail++;
    }
}

/*
Function prototype:
void Hangman::dequeueHangman()

Function description:
Dequeues strings containing body parts of hangman.

Example:
Hangman game;
game.dequeueHangman();

Pre-conditions: called in hangmanGame function when user guesses incorrect letter
Post-conditions: body part removed from queue
*/
string Hangman::dequeueHangman()
{
    string dequeueText;
    if(queueHead == queueSize-1)
    {
        queueHead = 0;
    }
    else
    {
        dequeueText = bodyQueue[queueHead];
        bodyQueue[queueHead] = " ";
        queueHead++;
    }
    return dequeueText;
}

/*
Function prototype:
void Hangman::queueisFull()

Function description:
Checks if queue is full.

Example:
Hangman game;
game.queueisFull();

Pre-conditions: called in enqueueHangman function
Post-conditions: none
*/
bool Hangman::queueisFull()
{
    if(queueTail == queueSize-1)
        return true;
    else
        return false;
}

/*
Function prototype:
void Hangman::queueisEmpty()

Function description:
Checks if queue is empty

Example:
Hangman game;
game.queueisEmpty();

Pre-conditions: called in hangmanGame function, if queue is empty user has lost the game
Post-conditions: none
*/
bool Hangman::queueisEmpty()
{
    if(queueHead == queueTail)
        return true;
    else
        return false;
}

/*Reference for code: http://www.cplusplus.com/forum/general/91788/*/
/*
Function prototype:
void Hangman:resetHangman()

Function description:
Resets the queue for a new game if the user correctly guesses the word

Example:
Hangman game;
game.resetHangman();

Pre-conditions: called in hangmanGame function
Post-conditions: refreshes the queue
*/
void Hangman::resetHangman()
{
    bodyQueue[0] = '\0';
    queueHead = 0;
    queueTail = 0;

    while(!queueisFull())
    {
       enqueueHangman();
    }
}
