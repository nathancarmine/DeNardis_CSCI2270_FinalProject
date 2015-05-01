#ifndef HANGMAN_H
#define HANGMAN_H
#pragma once              //Necessary preprocessor directives for following components
#include <string>
#include <vector>


class Hangman {  //Declares a class called Hangman with private data members and public member functions

    private:
        std::string name;
        std::string wordsFile;
        int level;
        int score;
        std::string *bodyQueue;
        int queueHead;
        int queueTail;
        int queueSize;
       

	public:
        Hangman();                //Default constructor
        virtual ~Hangman();
        std::string getName() const {return name;}           //Accessor methods or get functions
        std::string getWordsFile() const {return wordsFile;}
        int getLevel() const {return level;}
        void loadDirections() const;                     //Function prototypes for game components
        void enterName();
        void chooseLevel();
        void loadWords();
        int hangmanGame(int);
        void results() const;
        void enqueueHangman();
        bool queueisFull();
        std::string dequeueHangman();
        bool queueisEmpty();
        void resetHangman();
        void initializeGame(int);
       
    

};

#endif // HANGMAN_H
