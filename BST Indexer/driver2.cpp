#include <iostream>
#include <string>
#include "Indexer.h"
#include "Word.h"

using namespace std;

int main(){
  
  Indexer *index = new Indexer("gsl.txt", "input1.txt");
  index->DoIndex();
  index->OutputResults();
  delete index;
  
  return 0;
}
