#ifndef _LLAMA_H_
#define _LLAMA_H_

/* File: Llama.h

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   You may add public and private data members to the Llama class.

   You may add public and private member functions to the Llama class.

*/


#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;


class LlamaUnderflow : public std::out_of_range {

   public:

   LlamaUnderflow(const string& what) : std::out_of_range(what) { }

} ;


template <class T, int LN_SIZE>
class Llama {

public:
  
   Llama() ;
   Llama(const Llama<T,LN_SIZE>& other) ;   // copy constructor
   ~Llama() ;

  
  
  int size() ; 
   void dump() ;
   void push(const T& data) ;
   T pop() ;

  
   void dup() ;    //  (top) A B C D -> A A B C D
   void swap() ;   //  (top) A B C D -> B A C D 
   void rot() ;    //  (top) A B C D -> C A B D


   T peek(int offset) const ;


   // overloaded assignment operator
   //
   const Llama<T,LN_SIZE>& operator=(const Llama<T,LN_SIZE>& rhs) ;

  void clearData(); // deletes stack
  void buildStack(const Llama<T,LN_SIZE>& other); // creates new stack

private:
  
  LlamaNode<T,LN_SIZE> *_top; // top of stack
  int _size; // array size for an individual node
  int _stackCount; // # of nodes
  int _total; // total size
  int _popCount = 0; // # of items popped
  bool _extra; // true if extra node exists
  bool _popCheck = false; // used for dup() swap() and rot()

} ;


#include "Llama.cpp"


#endif
