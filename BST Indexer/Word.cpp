/*****************************************
** File:    Word.cpp
** Project: CMSC 341 Project 2, Summer 2020
** Author:  Devin Hennayake
** Date:    25 June 2020
** E-mail:  devin7@umbc.edu
**
** This file contains the cpp code for Word.h
**
***********************************************/

#include "Word.h"

Word::Word(){}

Word::Word(string inWord, int lineNumber){

  count = 1;
  wordText = inWord;
  lineNumbers.push(lineNumber);
}

void Word::CountWord(int lineNumber){
  
  count++;
  lineNumbers.push(lineNumber);
}

int Word::GetCount(){ return count; }

string Word::GetWord(){ return wordText; }

string Word::PrintQueue(){

  string output; 
    while(!lineNumbers.empty())
    {
      output.append(to_string(lineNumbers.front()));
      // append line numbers to a single string to return
      output.append(" ");
      lineNumbers.pop();
    }
    return output;
}

bool Word::operator<(Word &RHS){

  // returns -1 if word comes before RHS
  // returns 1 if word comes after RHS
  int result = wordText.compare(RHS.wordText);
  
  if(result < 0)
    return true;
  else
    return false;
}

bool Word::operator==( Word &RHS){

  // returns 0 if words are equivalent
  int result = wordText.compare(RHS.wordText);
  if(result == 0)
    return true;
  else
    return false;
}

Word Word::operator=(Word &RHS){

  // self-assignment check
  if(this != &RHS){
    RHS.count++;
    count += RHS.count;
    RHS.lineNumbers.push(lineNumbers.front());
    lineNumbers = RHS.lineNumbers;
    wordText = RHS.wordText;
  }
  return *this;
}

ostream& operator<<(ostream& out, Word& inWord){

  string lines;
  lines = inWord.PrintQueue();
  out << inWord.GetWord() << "............" << inWord.GetCount() << ": " << lines;
  return out;
}
