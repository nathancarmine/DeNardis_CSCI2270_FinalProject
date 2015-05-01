void Hangman::initializeGame(int _count)
{	
	
	while(_count < 1)
	{
    score = 0;
    words.clear();  //clears the words vector so new words can be loaded with each new game
    cout << "Hello " << getName() << ", please choose a level to begin." << endl;           //Calls getName function which prints user's name to console.
	cout << "Choose a difficulty level - ";
	chooseLevel();                                                                          //Calls chooseLevel function which allows user to select level, level is assigned appropriate text files.
	cout << endl;
    loadWords();    //Calls loadWords function which loads words text file into vector.

	cout << "Guess a letter for this Level " << getLevel() << " word." << endl;    //Calls getLevel function which prints level integer to console.
	hangmanGame(_count);
	_count++;
	if(_count == 1)
		{
			string again;
			cout << endl;
			cout << "Play again? (Yes, No)" << endl;
			cout << endl;
			cin >> again;
			if((again == "yes") || (again == "Yes"))
			{
				_count--;
			}
			else
			{
				cout<< endl;
				cout << "Thanks for playing!" << endl;
				return;
			}		
		}
	}
}

int Hangman::hangmanGame(int loop_count)
{
	
    bool dead = false;  //boolean to see if the player guessed too many incorrect guesses
    bool winner = false;  //boolean to see if the player has guessed the word correctly or not
    resetHangman();
    while((!dead || !winner) && (loop_count == 0)) //while the player hasn't lost but also hasn't won
    {
        //for (int i=0; i<words.size(); i++){  //This loop takes a word from the words vector and puts it into a string called letters,
            int randomInt;
            randomInt = rand() % 10 + 1;   //generates a random integer between 1 and 10
            string letters;                   //declares a string to store randomly chosen word from text file
            letters = words[randomInt];         //each letter of the word occupies its own index of the string, memory snapshot: word cat is placed in string {c, a, t}

            vector<string> lettersVector;  //declare a vector of letters and fill the vector with the letters of the word from the words vector

            for (int i=0; i<letters.size(); i++)
            {
                lettersVector.push_back(letters.substr(i, 1));    //memory snapshot: string vector created {c, a, t}
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
            vector<string> correctGuesses;  //vector to hold correct guesses
            vector<string> hangman;  //vector to hold body parts added to tree

            while (guess != words[randomInt])  //while loop runs while user's guess is not the completed word
            {
                cout<<"Guess: ";
                cin >> guess;
                cout<<endl;
                cin.clear();

                for (int i=0; i<guess.length(); i++)  //converts every input to lowercase
                {
                    guess[i]=tolower(guess[i]);
                }

                bool correct = false;  //boolean to check if letter is correct or incorrect
                for (int i=0; i<letters.size(); i++)  //takes the player's guess and checks it against every letter in the word
                {
                    int index = 0;
                    if (guess == lettersVector[i])   //if guess is a letter in the lettersVector
                    {
                        cout<<"That's correct! ";
                        index = i;                         //index is recorded
                        underscores[index] = lettersVector[i];  //and in the underscore vector the corresponding underscore is replaced with the letter
                        correctGuesses.push_back(guess);   //the letter is added to the correctGuesses vector
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
                            loop_count++;
                            return loop_count;
                          
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
                        cout << hangman[i] << ", ";
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
                        {
                            cout << "Keep trying, you can get a better score!" << endl;
                            
						}
                        else if (score > 0)
                        {
                            cout << "You're a Hangman master!" << endl;
                            
						}
						
					
					
                    loop_count++;
                    return loop_count;			
                   
					
					
                    }
                   
                }
              
            }
          
        //} //end of for loop body, for loop ends when last word in words text file is unscrambled
    }


}
