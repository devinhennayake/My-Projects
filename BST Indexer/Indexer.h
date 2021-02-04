/*****************************************
** File:    Indexer.h
** Project: CMSC 341 Project 2, Summer 2020
** Author:  Devin Hennayake
** Date:    25 June 2020
** E-mail:  devin7@umbc.edu
**
** This is the header file for the Indexer class
**
***********************************************/

#ifndef INDEXER_H
#define INDEXER_H
#include "MyExceptions.h"
#include "Word.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <string>
#include <algorithm>

class Indexer{

public:
  Indexer();
  Indexer(string filterFile, string dataFile);
  void DoIndex();
  BinarySearchTree<Word> FileFilterReader(string filename);
  BinarySearchTree<Word> FileWordReader(string filename);
  void OutputResults();
  
private:

  BinarySearchTree<Word> _filteredBST;
  BinarySearchTree<Word> _indexedBST;
  string _filterfile;
  string _datafile;

};

#endif
