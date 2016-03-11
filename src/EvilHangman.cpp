//============================================================================
// Name        : EvilHangman.cpp
// Author      : Shea Styer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "map.h"
#include "vector.h"
#include "Hangman.h"
#include <vector>
using namespace std;

int main() {
	Vector <string> spots;
	spots.clear();
	Map<int, Vector<string>> wordLengths;
	Vector<string> temp;
	ifstream in("Text.txt");
	if (!in) {
		cerr << "Error opening input file!" << endl;
		return -1;
	}
	// get all strings; extra whitespace will be ignored
	ostringstream text;
	while (!in.eof()) {
		temp.clear();
		string s;
		in >> s;
		if (wordLengths.containsKey(s.length()))
		{
			wordLengths[s.length()].add(s);
		}
		else
		{
			temp.add(s);
			wordLengths.put(s.length(), temp);
		}
	}
	int record[] = { 0,0 };
	cout << "Welcome to Hang-man!" << endl;
	bool play;
	cout << "Would you like to play?\n[1] YES\n[2] NO" << endl;
	int playChoice = 0;
	cin >> playChoice;
	switch (playChoice)
	{
	case 1:
	{
		play = true;
		cout << "Lets have some fun! No cheating!" << endl;
		break;
	}
	case 2:
	{
		play = false;
		cout << "No don't go!" << endl;
		break;
	}
	default:
	{
		cout << "Invalid choice, cheaters don't get to play!" << endl;
		break;
	}
	}

	while (play)
	{
		int show = 0;
		int count = 0;
		hangMan game;
		cout << "Would you like to see the size of the current word family?\n[1] YES\n[2] NO" << endl;
		cin >> show;

		bool valid = false;
		do
		{
			cout << "What length of word would you like to use?" << endl;
			cin >> count;
			if (wordLengths.containsKey(count))
			{
				valid = true;
			}
			else
			{
				cout << "Not valid, try again. " << endl;
			}

		} while (!valid);
		game.setLen(count);
		spots.clear();
		for (int i = 0; i<count; i++)
		{
			spots.add("_");
		}
		game.setVec(spots);
		bool valid2 = false;
		cout << "How many guesses will you use?" << endl;
		int guess = 0;
		do
		{
			cin >> guess;
			if (guess > 0)
			{
				valid2 = true;
			}
			else
			{
				cout << "Not valid, try again. " << endl;
			}
		} while (!valid2);
		game.setGuesses(guess);

		if (show == 1)
		{
			game.setShowFam(true);
		}
		else
		{
			game.setShowFam(false);
		}
		game.setLetterWords(wordLengths.get(game.getLen()));
		bool whoWon = game.play();
		if (whoWon)
		{
			record[0]++;
		}
		else
		{
			record[1]++;
		}
		cout << "Would you like to play again?\n[1] YES\n[2] NO" << endl;
		cin >> playChoice;
		switch (playChoice)
		{
		case 1:
		{
			cout << "Think you can win this time?" << endl;
			play = true;
			break;
		}
		case 2:
		{
			cout << "Come play again soon!" << endl;
			cout << "Your final record is: \nWins: " << record[0] << "\nLosses: " << record[1] << endl;
			play = false;
			break;
		}
		default:
		{
			cout << "Thats not a valid option. We don't like cheating here." << endl;
			play = false;
			break;
		}
		}
	}
	return 0;
}
