////////////////////////////////////////////////////////////
///     Chris Arsenault
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#include "hangmanClass.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

const std::vector<Picture> hangmanClass::_pictureList ={ Picture::ONE, //to easily go hrough the pictures for the gallows
                                                         Picture::TWO,
                                                         Picture::THREE,
                                                         Picture::FOUR,
                                                         Picture::FIVE,
                                                         Picture::SIX,
                                                         Picture::SEVEN
                                                       };

hangmanClass::hangmanClass() //prepares a new word
{
    addWords();
    shuffleWords();
}


hangmanClass::~hangmanClass()
{
}

void hangmanClass::addWords(){
    std::ifstream inFile("C:\\words.txt");
    if (!inFile.fail())
    {
        do{
            getline(inFile, phrase);
            phrases.push_back(phrase);		// loads a vector of prases
        }while (!inFile.eof());

        inFile.close();
    }
    else
    {
        std::cout << "Error opening file for write\n";
        exit(EXIT_FAILURE);
    }
}

void hangmanClass::shuffleWords()
{
    srand ( (unsigned int)time(NULL) );
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(phrases.begin(), phrases.end(), urng); //rands a new word form the list
}


std::string hangmanClass::showHiddenPhrase()
{
    return _underScores;
}

std::string hangmanClass::showPhrase()
{
    return _spaces;
}

std::string hangmanClass::newWord()
{
    phrase = phrases[0];

    for (auto p : phrase)						// make _underScores word
    {
        if (p == ' ')			    // checks for space
        {
            _underScores.append("  ");
        }
        else
        {
            _underScores.append("_ ");
        }
    }


    for (auto p : phrase)						// make word/phrase with _spaces
    {
        _spaces.push_back(p);
        _spaces.push_back(' ');
    }


    _correctGuesses[" "]++;

    return _underScores;
}


void hangmanClass::PrepareGame()
{
    //clears variables for next game
    _correctGuesses.clear();					// clears correct guesses
    badGuesses.clear();								// clears badGuesses
    _spaces = "";								// clears the spaces in the wordl
    _underScores = "";									// clears the underScores in the word
}

Picture hangmanClass::showGallows() //prints out a diffrent picture depending on how many wrong guesses you have
{

    switch (badGuesses.size())
    {
    case 0:\
        return Picture::ONE;
        break;
    case 1:
        return Picture::TWO;
        break;
    case 2:
        return Picture::THREE;
        break;
    case 3:
        return Picture::FOUR;
        break;
    case 4:
        return Picture::FIVE;
        break;
    case 5:
        return Picture::SIX;
        break;
    default:
        return Picture::SEVEN;
        break;
    }
}

void hangmanClass::processGuess(std::string guess)
{
    if(won() || lost()) //doesn't allow the user to enter stuff after the game is over
        return;

    int found = _spaces.find(guess);

    if (found != std::string::npos)
    {
        int found = _spaces.find(guess, 0); //checks if there is more than one of the same guessed letter in the word
        while (found != std::string::npos)
        {
            _underScores.replace(found, 1, guess); //replaces underscores with the correct char where it fits
            found = _spaces.find(guess, found + 1);
        }
        _correctGuesses[guess]++;
    }

    else //if it isn't a correct guess
    {
        badGuesses[guess]++;
    }
}


bool hangmanClass::won()
{
    for (auto c : phrase)
    {
        std::string s(1, c); // convert char to string (1 = first char in the string)
        auto it = _correctGuesses.find(s);
        if (it == _correctGuesses.end()) //if it can't find all the letters it will hit end of the guesses before it hits the end  of the phrase
        {
            return false;
        }
    }
    return true;
}

bool hangmanClass::lost()
{
    if (badGuesses.size() >= _MAXbadGuesses)
    {
        return true;
    }
    else
        return false;
}

bool hangmanClass::letterGuessed(std::string guess)
{
    auto itrMissed = badGuesses.find(guess);													// checks if you already guessed by iterator not equaling the end
    if (itrMissed != badGuesses.end())
    {
        return true;
    }

    auto itrCorrect = _correctGuesses.find(guess);
    if (itrCorrect != _correctGuesses.end())											    // if you already guessed it
    {
        return true;
    }

    return false;
}
