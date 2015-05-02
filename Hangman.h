#ifndef HANGMAN_H
#define HANGMAN_H
#pragma once              //Necessary preprocessor directives for following components
#include <string>
#include <vector>


class Hangman {  //Declares a class called Hangman with private data members and public member functions

	public:
        Hangman();                //Default constructor
        virtual ~Hangman();
        std::string getName() const {return name;}           //Accessor methods or get functions
        int getLevel() const {return level;}
        void loadDirections() const;                     //Function prototypes for game components
        void enterName();
        void chooseLevel();
        void loadWords();
        void hangmanGame();
        void results() const;
        void enqueueHangman();
        bool queueisFull();
        std::string dequeueHangman();
        bool queueisEmpty();
        void resetHangman();
        void initializeGame();
	
    private:
		std::vector<std::string> words;
        std::string name;
        int level;
        int score;
        std::string *bodyQueue;
        int queueHead;
        int queueTail;
        int queueSize;

};

#endif // HANGMAN_H
