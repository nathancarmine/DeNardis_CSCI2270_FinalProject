//edittingfdnsaikljfsaklnfdsa
#include "Hangman.h"
#include <cstdlib>    //Necessary preprocessor directives for following components
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> words; //These vectors are used in most of the functions below, hence global scope.

Hangman::Hangman() {
    totalTries = 0;
    queueSize = 6;
    bodyQueue = new string[queueSize];
    queueTail = 0;
    queueHead = 0;
}

Hangman::~Hangman() {
    delete []bodyQueue;
}

/*This function prints the directions of the game to the console, keeps the main.cpp neat to define them here.*/
void Hangman::loadDirections() const {
	cout << "\nDirections:" << endl;
	cout << "  -Choose a difficulty level - (1) Easy (2) Medium or (3) Hard" << endl;
	cout << "  -I will choose a word based on the difficulty you've chosen" << endl;
	cout << "  -Once I've chosen a word, you can guess a letter" << endl;
	cout << "  -For each incorrect guess I will add a body part to the hanged man" << endl;
	cout << "  -I'll keep track of how many words you guess correctly" << endl;
	cout << "  -The object is to see how many words you guess before I\n   complete my drawing (6 incorrect guesses)" << endl;
	cout << "\nGood Luck and try to avoid the noose!\n" << endl;
	/*
	cout << "When prompted you must guess a letter. With each incorrect guess a body part will be added to the hangman's tree." << endl;
	cout << "You are allowed 5 incorrect guesses, but at 6 incorrect guesses you will lose\nthe game and be hung." << endl;
	cout << "Try to avoid the noose. Good Luck!" << endl << endl;
	*/

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
/*
void Hangman::scrambler() {
//we need a while loop for this whole function so that when the word is completed it stops asking for guesses
	for (int i=0; i<words.size(); i++) {  //This loop takes a word from the words vector and puts it into a string called letters,
		string letters;                   //thus each letter of the word occupies its own index of the string. Note that the rest of the code
		letters = words[i];               //is contained in the body of this for loop, which I found to be necessary for the game to operate proper
                                          //memory snapshot: word cat is placed in string {c, a, t}

        vector<string> lettersVector;                  //Here I declare a vector of letters and fill the vector with the letters
		for (int i=0; i<letters.size(); i++){   //of the word from the words vector above.
			lettersVector.push_back(letters.substr(i, 1));    //memory snapshot: integer vector created {c, a, t}
		}

        vector<string> underscores;
		for (int i=0; i<letters.size(); i++) {
            underscores.push_back("_");
            cout<<underscores[i];
		}

		cout << endl;
		string guess;
        vector<string> hangman;
		int incorrectGuesses = 0; //Initializes local variables to record # of tries to guess letter

		while (guess != words[i]) {                 //while loop runs while user's guess is not the word

			cout<<"Guess a letter: ";
			cin >> guess;                           //allows user to input a string guess
			//Following for loop for converting uppercase to lower case found at http://www.cplusplus.com/forum/beginner/613/.
			for (int i=0; i<guess.length(); i++) {  //allows user to enter upper or lowercase letters
				guess[i]=tolower(guess[i]);         //converts uppercase letters to lowercase letters
			}

			//when the for loop is here it would check the letter for as many letters as in the word
			//and output "WRONG" x number of times
			int checking = 0;
			for (int i = 0; i < letters.size(); i++)
            {
                if (guess == lettersVector[i])
                {
                    checking++;
                    int index = i;
                    underscores[index] = lettersVector[i];
                }
            }
            if(checking > 0)
            {
                cout<<"You guessed a correct letter, keep going!"<<endl;
                int index = i;
                underscores[index] = lettersVector[i];
            }
            else if(checking <= 0)
            {
                cout <<"WRONG! That letter is not part of the word." << endl;
                while(!queueisEmpty())
                {
                    string bodypart = dequeueHangman();
                    for(int i=0; i <hangman.size(); i++)
                    {
                        hangman.push_back(bodypart);
                        cout << hangman[i] << endl;
                    }
                }
            }

            //this should be printed at the end of every guess no matter whether the guess was right or not
            for(int i=0; i<underscores.size(); i++)
            {
                cout<<underscores[i];
            }
            cout<<endl;  //adds an endline after the printout of the word
		}

		//totalTries += tries;      //sum of tries used per level

	} //end of for loop body, for loop ends when last word in words text file is unscrambled
}
*/
void Hangman::scrambler() {
//error now is that the loop checks every letter space against the guessed letter and counts prints wrong for each spot even if the guess was right
    resetHangman();

	for (int i=0; i<words.size(); i++) {  //This loop takes a word from the words vector and puts it into a string called letters,
		string letters;                   //thus each letter of the word occupies its own index of the string. Note that the rest of the code
		letters = words[i];               //is contained in the body of this for loop, which I found to be necessary for the game to operate proper
                                          //memory snapshot: word cat is placed in string {c, a, t}

        vector<string> lettersVector;                  //Here I declare a vector of letters and fill the vector with the letters
		for (int i=0; i<letters.size(); i++){   //of the word from the words vector above.
			lettersVector.push_back(letters.substr(i, 1));    //memory snapshot: integer vector created {c, a, t}
		}

        vector<string> underscores;
		for (int i=0; i<letters.size(); i++) {
            underscores.push_back("_");
            cout<<underscores[i];
		}

		cout << endl;
		string guess;
        vector<string> hangman;
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
                    underscores[index] = lettersVector[i];
                    for(int i=0; i<underscores.size(); i++){
                        cout<<underscores[i];
                    }
                    cout<<endl;
                }
                else
                {
                    //cout << guess << endl;
                    cout << "WRONG! The following body part has been added to your hangman: " << endl;
                    string bodypart = dequeueHangman();
                    cout << bodypart << endl;
                    hangman.push_back(bodypart);
                    cout << "Your hangman has the following body parts: " << endl;
                    for(int i=0; i < hangman.size(); i++)
                    {
                        cout << hangman[i] << endl;
                    }
                    if(queueisEmpty())
                    {
                        cout << "GAME OVER! You have been hung!" << endl;
                        cout << endl;
                        loadDirections();
                    }
                    break;
                }

           }
           for(int i = 0; i < guess.length(); i++)
           {

           }
		}


		//totalTries += tries;      //sum of tries used per level

	} //end of for loop body, for loop ends when last word in words text file is unscrambled
}

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

bool Hangman::queueisFull()
{
    if(queueTail == queueSize-1)
        return true;
    else
        return false;
}

bool Hangman::queueisEmpty()
{
    if(queueHead == queueTail)
        return true;
    else
        return false;
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

/*pseudo code for hangman figure
7x7 2-D array
Default Image:
    cout << " ____  " << endl;
    cout << " |  |  " << endl;
    cout << " |     " << endl;
    cout << " |     " << endl;
    cout << " |     " << endl;
    cout << " |     " << endl;
    cout << "_|_____" << endl;

Completed Image:
    cout << " ____  " << endl;
    cout << " |  |  " << endl;
    cout << " |  O  " << endl;
    cout << " | /|\\ " << endl;
    cout << " | / \\ " << endl;
    cout << " |     " << endl;
    cout << "_|_____" << endl;

Idea of implementation:
    array[x][y]
    for i = 0, i++{
        for j = 0 j++{
            cout array[i][j]
        }
    }

Need to figure out how to add the appropriate symbols in the correct spots;
I think it may be easiest to have predefined arrays that replace the existing arrays, for instance:
    first wrong guess, replace the third array with one that has a head in it;
    second wrong guess replace the fourth array with one that has a torso in it;
    third wrong guess replace the fourth array with one that has a torso and left arm;
    so-on.
Benefit is that we don't have to tell the array where to add body parts;
Downside is that we have to explicitly predefine each possible array combo;
*/

/*pseudo for scoring
-counter for each time the game is started; +1 once the man is hanged but the program is still rerun
    -this counter determines the size of the score-keeping array
-second counter that is +1 for every word that is completely guessed
    -this counter gets reset when the man is hanged
    -before the counter reset, the value gets stored in the array in the position equivalent to the first counter's value
-at the end of every game, the score is printed with some text congratulating the player
-at the end of every game after the first, the previous highest score is printed as well
    -if previous highest is greater than latest score, "slacker/motivational"-style comment printed out
    -if previous highest is less than the latest score, congratulatory comment printed out
SCORING COMPLETE
*/




