/*
* Hangman.cpp
*
*  Created on: Mar 4, 2016
*      Author: sheastyer
*/
#include "Hangman.h"
#include <iostream>
#include "set.h"
#include <vector>



using namespace std;
hangMan::hangMan()
{
	len = 0;
	showFam = false;
	guesses = 0;
	Vector<string> current;
}
hangMan::hangMan(int sz, bool sF, int g, Vector<string> vec, Vector<string> lw)
{
	len = sz;
	showFam = sF;
	guesses = g;
	current = vec;
	letterWords = lw;
}

void hangMan::setLen(int z)
{
	len = z;
}

int hangMan::getLen()
{
	return len;
}
void hangMan::setShowFam(bool x)
{
	showFam = x;
}

void hangMan::setGuesses(int g)
{
	guesses = g;
}

void hangMan::setVec(Vector<string> vec)
{
	current = vec;
}

void hangMan::setLetterWords(Vector <string> lW)
{
	letterWords = lW;
}

ostream& operator<<(ostream& out, const vector<int> v) {
	out << "{";
	for (auto x : v) cout << x << ",";
	out << "}";
	return out;
}

bool hangMan::play()
{
	Map <vector<int>, Vector<string>> families;
	Set<char> chosenLetters;
	Set<char> possibleLetters = { 'a','b','c','d','e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	vector<int> lastWord;
	while (guesses>0)
	{
		printGame(hangMan(len, showFam, guesses, current, letterWords), chosenLetters);
		bool guessed = false;
		string guess;
		do {
			cout << "Please make a guess" << endl;
			cin >> guess;
			if (guess.length()>1 || !possibleLetters.contains(guess[0]))
			{
				cout << "That is an invalid guess." << endl;
				continue;
			}
			if (chosenLetters.contains(guess[0]))
			{
				cout << "You have already guessed that!" << endl;
			}
			else
			{
				guesses--;
				guessed = true;
				chosenLetters.add(guess[0]);
			}
		} while (!guessed);

		vector<int> constEmpty;
		vector<int> tempKeyVec;
		Vector<string> tempValueVec;
		tempValueVec.clear();
		constEmpty.clear();
		families.clear();
		families.put(constEmpty, tempValueVec);
		vector<int> largestKey;
		int largest = 0; 
		for (int word = 0; word<letterWords.size(); word++)
		{
			tempValueVec.clear();
			tempKeyVec.clear();
			for (int i = 0; i<letterWords[word].length(); i++)
			{
				if (letterWords[word][i] == guess[0])
				{
					tempKeyVec.push_back(i);
				}
			}
			if (families.containsKey(tempKeyVec))
			{
				families[tempKeyVec].add(letterWords[word]);
			}
			else
			{
				tempValueVec.add(letterWords[word]);
				families.put(tempKeyVec, tempValueVec);
			}

				if (largest < families[tempKeyVec].size())
				{
					largest = families[tempKeyVec].size();
					largestKey.clear();
					for (int s = 0; s < tempKeyVec.size(); s++)
						{
						largestKey.push_back(tempKeyVec[s]);
						}
				}
		}
		if (largestKey != constEmpty)
		{
			cout << "Thats a letter!" << endl;
			for (int z = 0; z < largestKey.size(); z++)
			{
				current[largestKey[z]] = guess;
			}
		}
		else
		{
			cout << "Thats not a letter, sorry :(" << endl;
		}

		int counter = 0;
		for (int p = 0; p<current.size(); p++)
		{
			if (current[p] == "_")
			{
				counter++;
			}
		}
		letterWords.clear();
		letterWords += families[largestKey];
		if (counter == 0)
		{
			cout << "FINISHED WORD: " << current << endl;
			cout << "Wow you beat the computer! Congratulations!" << endl;
			return true;
		}
		lastWord = largestKey;
	}
	cout << "You're out of turns :(" << endl;
	cout << "You finished at: " << current.toString() << endl;
	cout << "The word was " << families[lastWord][0] << endl;
	return false;
}

void hangMan::printGame(hangMan g, Set<char> chosenOnes)
{
	cout << "Guesses Remaining: " << g.guesses << endl << endl;
	if (g.showFam == true)
	{
		cout << "Current word family count: " << g.letterWords.size() << endl;
	}
	for (int i = 0; i < g.current.size(); i++)
	{
		cout << current[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "Previously Guessed: " << chosenOnes << endl;
}
