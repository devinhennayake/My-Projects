/*****************************************
** File:    Word.h
** Project: CMSC 341 Project 2, Summer 2020
** Author:  Devin Hennayake
** Date:    25 June 2020
** E-mail:  devin7@umbc.edu
**
** This is the header file for the Word class
**
***********************************************/

#ifndef WORD_H
#define WORD_H
#include <queue>
#include "BinarySearchTree.h"


class Word{

public:

  Word();
  Word(string inWord, int lineNumber);
  void CountWord(int lineNumber);
  int GetCount();
  string GetWord();
  string PrintQueue();
  bool operator<(Word &RHS);
  Word operator=( Word &RHS);
  bool operator==( Word &RHS);
  friend ostream& operator<<(ostream& out, Word& inWord);

private:

  int count;
  queue<int> lineNumbers;
  string wordText;

};

#endif
