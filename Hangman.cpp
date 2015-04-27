#include "Hangman.h"
#include <iostream>
#include <cstdlib>    //Necessary preprocessor directives for following components
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> words; //These vectors are used in most of the functions below, hence global scope.

Hangman::Hangman()
{
    totalTries = 0;
    queueSize = 7;
    bodyQueue = new string[queueSize];
    queueTail = 0;
    queueHead = 0;
}

Hangman::~Hangman()
{
    delete []bodyQueue;
}

/*This function prints the directions of the game to the console, keeps the main.cpp neat to define them here.*/
void Hangman::loadDirections() const
{
	cout << "\nDirections:" << endl;
	cout << "  -Choose a difficulty level - (1) Easy (2) Medium or (3) Hard" << endl;
	cout << "  -I will choose a word based on the difficulty you've chosen" << endl;
	cout << "  -Once I've chosen a word, you can guess a letter" << endl;
	cout << "  -For each incorrect guess I will add a body part to the hanged man" << endl;
	cout << "  -I'll keep track of how many words you guess correctly" << endl;
	cout << "  -The object is to see how many words you guess before I\n   complete my drawing (6 incorrect guesses)" << endl;
	cout << "\nGood Luck and try to avoid the noose!\n" << endl;
}

/*This function initializes the game levels and loads the words from the word files.*/
void Hangman::initializeGame()
{
    Hangman::tries += 1;
    cout << "Hello " << getName() << ", please choose a level to begin." << endl;           //Calls getName function which prints user's name to console.
	cout << "Choose a difficulty level - ";
	chooseLevel();                                                                          //Calls chooseLevel function which allows user to select level, level is assigned appropriate text files.
	cout << endl;
    loadWords();    //Calls loadWords function which loads words text file into vector.

	cout << "Guess a letter for this Level " << getLevel() << " word." << endl;    //Calls getLevel function which prints level integer to console.

	scrambler();  //Calls the scrambler function which essentially runs the entire game.

}

/*This function allows the user to enter the name they wish to be referred to as. The getline function captures the entire string as well
as white space; the data member name is assigned the string and prints the user's name to the console when called by the getName function.*/
void Hangman::enterName()
{
	string n;
	getline(cin, n);
	name = n;
}

/*This function allows the user to choose a difficulty level from 1 to 3, each level is associated with a words text file (containing 10 words).
The data member level is assigned the int lev and prints the level number to the console when called by the getLevel function.*/
void Hangman::chooseLevel()
{
	int lev;
	string s;
	while (true) {
        cout << "(1) Easy (2) Medium or (3) Hard: ";
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
void Hangman::loadWords()
{
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

void Hangman::scrambler()
{
    int score = 0;
    bool dead = false;  //boolean to see if the player guessed too many incorrect guessed
    bool winner = false;  //boolean to see if the player has guessed the word correctly or not
    resetHangman();
    while(!dead || !winner)  //while the player hasn't lost but also hasn't won
    {
        //for (i; i<words.size(); i++)  //This loop takes a word from the words vector and puts it into a string called letters,
        //{
            string letters;                   //each letter of the word occupies its own index of the string.
            letters = words[tries];               //memory snapshot: word cat is placed in string {c, a, t}

            vector<string> lettersVector;  //declare a vector of letters and fill the vector with the letters of the word from the words vector
            for (int i=0; i<letters.size(); i++)
            {
                lettersVector.push_back(letters.substr(i, 1));    //memory snapshot: integer vector created {c, a, t}
            }

            vector<string> underscores;  //vector for the blank spaces representing the incomplete part(s) of the word
            for (int i=0; i<letters.size(); i++)
            {
                underscores.push_back("_");
                cout<<underscores[i];
            }

            cout << endl;
            string guess;  //this is the cin letter of the player's guess; gets overwritten with every new guess
            vector<string> hangman;
            int incorrectGuesses = 0;  //Initializes local variables to record # of tries to guess letter

            while (guess != words[tries])  //while loop runs while user's guess is not the completed word
            {
                cout<<"Guess: ";
                cin >> guess;
                cin.clear();

                for (int i=0; i<guess.length(); i++)  //converts every input to lowercase
                {
                    guess[i]=tolower(guess[i]);
                }
                bool correct = false;
                for (int i=0; i<letters.size(); i++)  //takes the player's guess and checks it against every letter in the word
                {
                    int index = 0;
                    if (guess == lettersVector[i])
                    {
                        cout<<"That's correct! ";
                        index = i;
                        underscores[index] = lettersVector[i];
                        correct = true;
                        score += 10;

                        for(int i=0; i<underscores.size(); i++)
                        {
                            cout<<underscores[i];
                        }
                        cout<<endl;
                        if(i == letters.size()-1)  //condition if all letters guessed correctly, sets winner bool to true
                        {
                            cout << "You WIN!" << endl;
                            cout << endl;
                            winner = true;
                            initializeGame();
                        }
                    }

                }
                if(correct == false)//ERROR: condition will only run properly for first letter in word correct, else condition will always be called, even if guess is correct
                {
                    //cout << guess << endl;
                    string bodypart = dequeueHangman();
                    cout << "WRONG! The " << bodypart << " was added to your hangman." << endl;
                    hangman.push_back(bodypart);
                    cout << "Your hangman has the following body parts: " << endl;

                    for(int i=0; i < hangman.size(); i++)
                    {
                        cout << hangman[i] << endl;
                    }

                    if(queueisEmpty())
                    {
                        cout << "GAME OVER! You have been hung!" << endl;
                        cout << " ____  " << endl;
                        cout << " |  |  " << endl;
                        cout << " |  O  " << endl;
                        cout << " | /|\\ " << endl;
                        cout << " | / \\ " << endl;
                        cout << " |     " << endl;
                        cout << "_|_____" << endl;
                        cout << "Your final score is: " << score << endl;
                        cout << "Your highest score is: " << score_keeper(score) << endl;
                        dead = true;
                        initializeGame();
                    }
                }
            }
        //} //end of for loop body, for loop ends when last word in words text file is unscrambled
    }

}

/*Function places the body parts of the hangman in a queue to be dequeued if
an incorrect guess is made.*/
void Hangman::enqueueHangman()
{
    string body;
    ifstream bodyFile("body.txt");

    int i = 0;
    while(!queueisFull())
    {
        getline(bodyFile, body, ',');
        bodyQueue[queueTail] = body;
        queueTail++;
    }
}

/*Dequeues strings containing body parts of hangman*/
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

/*Checks if queue is full*/
bool Hangman::queueisFull()
{
    if(queueTail == queueSize-1)
        return true;
    else
        return false;
}

/*Checks if queue is empty*/
bool Hangman::queueisEmpty()
{
    if(queueHead == queueTail)
        return true;
    else
        return false;
}

/*Function to print results based on final score.*/
void Hangman::results() const
{
	if (totalTries == 0 || totalTries < 60)
		cout << "Keep trying, you can get a better score!" << endl;
	else if (totalTries == 100)
		cout << "You're the master at Hangman!" << endl;
	else if (totalTries < 100 && totalTries >= 80)
		cout << "Great job!" << endl;
	else
		cout << "Nice try!" << endl;
}

void Hangman::resetHangman()
{
    int i = 0;
    while(!queueisEmpty())
    {
        bodyQueue[i] = " ";
        queueHead++;
        i++;
    }

    while(!queueisFull())
    {
       enqueueHangman();
    }
}

//the problem with displaying the highest is that it's not searching for the highest. I almost had an iteration function that worked,
//but I learned about max_element and that should be the better solution. Do you know how max_element works?
int Hangman::score_keeper(int score)
{
    //tries is the index for the all_scores array to store the past and last scores
    //score is the last score that needs to be added to the array
    int highest = 0;
    if(all_scores.begin() != all_scores.end())
        highest = *max_element(all_scores.begin(), all_scores.end());
    else
        highest = score;
    //find the highest score
    return highest;
}
