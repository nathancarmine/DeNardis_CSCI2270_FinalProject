#ifndef HANGMAN_H
#define HANGMAN_H
#pragma once              //Necessary preprocessor directives for following components
#include <string>

struct *node{
    std::string bodyPart;
    node* next;
    node* previous;
}

class Hangman {  //Declares a class called Hangman with private data members and public member functions

    private:
        std::string name;
        std::string wordsFile;
        int level;
        int totalTries;
        string bodyQueue[6];
        node* head;
        node* tail;

	public:
        Hangman();                //Default constructor
        virtual ~Hangman();
        std::string getName() const {return name;}           //Accessor methods or get functions
        std::string getWordsFile() const {return wordsFile;}
        int getLevel() const {return level;}
        int getTotalTries() const {return totalTries;}
        void loadDirections() const;                     //Function prototypes for game components
        void enterName();
        void chooseLevel();
        void loadWords();
        void scrambler();
        void results() const;
        void enqueueHangman();
        bool queueisFull();
};


#endif // HANGMAN_H
