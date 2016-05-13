////////////////////////////////////////////////////////////
///     Chris Arsenault
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#ifndef HANGMANCLASS_H
#define HANGMANCLASS_H
#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

enum class Picture { ONE,
                     TWO,
                     THREE,
                     FOUR,
                     FIVE,
                     SIX,
                     SEVEN
                   };

class hangmanClass
{
public:
    hangmanClass();								// opens words.txt and gets phrases
    ~hangmanClass();

    void PrepareGame();							// initializes the game

    void processGuess(std::string guess);

    char getCharResponse();						// get sthe char response

    Picture showGallows();
    std::string showHiddenPhrase();
    std::string showPhrase();

    std::string newWord();

    void shuffleWords();
    void addWords();
    bool letterGuessed(std::string guess);

    bool won();
    bool lost();

private:
    std::string phrase;							// holds the current word
    std::vector <std::string> phrases;			// holds the words

    static const int _MAXbadGuesses = 6;		// allowed badGuesses

    std::map<std::string, int> _correctGuesses;	// correct guesses
    std::map<std::string, int> badGuesses;			// missed letters
    std::string _underScores;							// to print the correct amount of _'s
    std::string _spaces;							// prints the paces if there are multiple words to be guessed

    static const std::vector<Picture> _pictureList; //vector of the enum
};


#endif // HANGMANCLASS_H
