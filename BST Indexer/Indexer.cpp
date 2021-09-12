/*****************************************
** File:    Indexer.cpp
** Author:  Devin Hennayake
**
** This contains the cpp code for Indexer.h
**
***********************************************/

#include "Indexer.h"

Indexer::Indexer(){}

Indexer::Indexer(string filterFile, string dataFile){

  _filterfile = filterFile;
  _datafile = dataFile;
}
void Indexer::DoIndex(){
  
  _filteredBST = FileFilterReader(_filterfile);
  _indexedBST = FileWordReader(_datafile);
  OutputResults();
}

BinarySearchTree<Word> Indexer::FileFilterReader(string filename){

  string word;
  ifstream inputStream(filename);
  int line = 0;
  while(getline(inputStream, word, '\n'))
    {
      Word* newWord = new Word(word, line);
       _filteredBST.insert(*newWord);
      line++;
      delete newWord;
    }
  inputStream.close();
  return _filteredBST;
}

BinarySearchTree<Word> Indexer::FileWordReader(string filename){

  // characters to leave out
  string exclusion {" -\t\r\n,.!?;:')(\""};

  string word, line;
  ifstream inputStream(filename);
  int lineNo = 1;

  
  while(getline(inputStream, line)){
    // used to get full word without extra characters
    std::size_t offset, end = 0;
    do{
      end = line.find_first_not_of(exclusion, end);
      if(end == string::npos)
	break;
      offset = line.find_first_of(exclusion, end);
      string word(line.substr(end, offset - end));
      // make word all lowercase
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      Word* newWord = new Word(word, lineNo);

      // if word is not in the filter list
      if(_filteredBST.contains(*newWord) == false)
	{
	  // if duplicate found
	  if(_indexedBST.contains(*newWord) == true){
	    *newWord = _indexedBST.getOriginal(*newWord);
	  }
	  else
	    _indexedBST.insert(*newWord);
	}
      
      end = offset++;
      delete newWord;
    }while(offset != string::npos);
    
    lineNo++;
  }
 
  inputStream.close();
  return _indexedBST;
}

void Indexer::OutputResults(){

  ofstream outputFile("indexResults.txt");
  _indexedBST.printTree(outputFile);  
   outputFile.close();
  ofstream filterFile("filterResults.txt");
  _filteredBST.printTree(filterFile);
  filterFile.close();
}
