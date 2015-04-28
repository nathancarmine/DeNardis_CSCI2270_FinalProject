# DeNardis_CSCI2270_FinalProject

Project Summary:
We are creating the game Hangman as our final project.  When the game begins the user will be prompted for their name and then asked to choose a level. Based on the level chosen a text file of words will be read in and stored in a vector. The queue data structure will be used to enqueue the words: head, body, right arm, left arm, right leg, left leg in a separate function. 
The first word will be randomly generated from the text file corresponding to the chosen level as a series of underscores (characters) corresponding to each letter of the word.  The user will then be prompted to guess a letter. If the letter is correct it will replace the corresponding underscore character. If the letter is incorrect the first
word of the queue will be dequeued and printed to the screen.  The user will than be prompted for the next letter
and so on until they either solve the word or are hanged.
The user will earn 10 points for each correct guess and lose 10 points for each incorrect guess.

How to Run:
Clone the program to your computer using the appropriate clone URL. Once all program files are properly stored on your computer including the text files, run the program in the terminal by typing the following command: 
g++ -std=c++11 main.cpp Hangman.cpp   then type   ./a.out  to run the program.
Or
Build a new project in the VM and add a Hangman class.  Copy and past the contents of the main.cpp, Hangman.cpp, and Hangman.h files into your corresponding files.  Copy the 4 text files into your project file next to the main.cpp.  Run the program using the VM.

Dependencies:
None

System Requirements:
Built using Windows and the Oracle VM, should work on Mac though.

Group Members:
Rebecca Robb (tabularasa7), Michelle De Nardis (mdenardis), and Rory Teehan (a4nacation).

Contributers:
Online forums like stack exchange.

Open issues/bugs:
All known bugs were fixed, but I'm sure some unknown bugs exist.



