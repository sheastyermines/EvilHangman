/*
* Hangman.h
*
*  Created on: Mar 4, 2016
*      Author: sheastyer
*/

#ifndef HANGMAN_H_
#define HANGMAN_H_
#include <string>
#include "vector.h"
#include "set.h"
using namespace std;
class hangMan
{
public:
	hangMan();
	hangMan(int sz, bool sF, int g, Vector<string> vec, Vector<string> lW);
	bool play();
	void printGame(hangMan g, Set<char> ch);
	void setLen(int z);
	int getLen();
	void setShowFam(bool x);
	void setGuesses(int g);

	void setVec(Vector <string> vec);
	void setLetterWords(Vector <string> lW);
private:
	bool showFam;
	int len;
	int guesses;
	Vector<string> current;
	Vector<string> letterWords;
};

#endif /* HANGMAN_H_ */#pragma once
