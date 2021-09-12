// File: Llama.cpp
// Author: Devin Hennayake
// Description: .cpp file for Llama.h

#ifndef _LLAMA_CPP_
#define _LLAMA_CPP_
#include "Llama.h"

template <class T, int LN_SIZE>
Llama<T,LN_SIZE>::Llama(){

  _top = new LlamaNode<T,LN_SIZE>;
  _size = 0;
  _total = 0;
  _stackCount = 1;
  _extra = false;
}

template <class T, int LN_SIZE>
Llama<T,LN_SIZE>::Llama(const Llama<T,LN_SIZE>& other){
  buildStack(other);
}

template <class T, int LN_SIZE>
Llama<T,LN_SIZE>::~Llama(){
  clearData();
}

template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::clearData(){

  LlamaNode<T,LN_SIZE> *temp = _top;
  LlamaNode<T,LN_SIZE> *next;

  while(temp != nullptr)
    {
      next = temp->m_next;
      delete temp;
      temp = next;
    }
  temp = nullptr;
  delete _top;
  _top = nullptr;
}
template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::buildStack(const Llama<T,LN_SIZE>& other){

  _top = new LlamaNode<T,LN_SIZE>;
  _size = 0;
  _total = 0;
  _stackCount = 1;
  _extra = false;
  int length = other._stackCount;
  LlamaNode<T,LN_SIZE> *temp = other._top;
  int index = 0;
  int arrInd = 0;
  T array[length * LN_SIZE] = {};
  int start = 0;
  while(index < length)
    {
      for(int i=LN_SIZE-1; i != -1; i--){
        start++;
        if(start >= 2){
          array[arrInd] = temp->arr[i];
	  arrInd++;
        }
      }
      temp = temp->m_next;
      index++;
    }
  // push values from array
  for(int i=other._total; i != 0; i--)
    push(array[i]);
}

template <class T, int LN_SIZE>
int Llama<T,LN_SIZE>::size(){ return _total; }

template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::dump(){

  cout << "***** Llama Stack Dump *****" << endl;
  cout << "LN_SIZE = " << LN_SIZE << endl;
  cout << "# of items in the stack = " << _total << endl;
  cout << "# of nodes created = " << _top->newCount << endl;
  cout << "# of nodes destroyed = " << _top->deleteCount << endl;

  if(_extra == false)
    cout << "This stack does not have an extra node" << endl;
  else
    cout << "This stack has an extra node: " << _top <<  endl;

  cout << "Stack contents, top to bottom" << endl;

  LlamaNode<T,LN_SIZE> *curr = _top;
  int index = 0;
  int count = -1;
  while(index < _stackCount)
    {
      cout << "---- " << curr << " ----" << endl;
      
      for(int i=LN_SIZE-1; i != -1; i--)
	{
	  // determine starting index
	  if(count > _popCount)
	    cout << curr->arr[i] << endl;	
	  else
	    count++;
	}
      
      curr = curr->m_next;
      index++;
    }
  cout << "----- bottom of stack -----" << endl;
  cout << endl;
}

template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::push(const T& data){

  // adding extra node
  if( _size + 1 > LN_SIZE / 2 && _extra == false)
    {
      LlamaNode<T,LN_SIZE> *temp = new LlamaNode<T,LN_SIZE>();    
      temp->m_next = _top;
      _top = temp;
      _extra = true;
      _stackCount++;
    }

  if(_size < LN_SIZE / 2)
    _extra = false;

  // push top
  if(_size < LN_SIZE && _extra == false)
    _top->arr[_size] = data;

  // push with the extra node
  else if(_size < LN_SIZE && _extra == true)
    _top->m_next->arr[_size] = data;

  // pushing into new node
  if(_size >= LN_SIZE){
    _size = 0;
    _top->arr[_size] = data;
    _extra = false;
  }
  _popCount--;
  if(_popCount < 0)
    _popCount = 0;
  _size++;
  _total++;
}

template <class T, int LN_SIZE>
T Llama<T,LN_SIZE>::pop(){

  try{
    if(_total == 0)
      throw(LlamaUnderflow ("stack is empty"));
    
    LlamaNode<T,LN_SIZE> *temp = _top; 
    T value;
    _size--;
    if(_size < 0){
      _size = LN_SIZE - 1;
      if(_extra == false)
	_extra = true;
    }
    if(_extra == true)
      {
	if(_size < LN_SIZE / 2)
	  {
	    // removing node
	    _top = _top->m_next;
	    delete temp;
	    _extra = false;
	    _stackCount--;
	    value = _top->arr[_size];
	  }
	else
	  value = _top->m_next->arr[_size];
      }
    else if (_extra == false)
      value = _top->arr[_size];

    // ignore count for swap() dup() and rot()
    if(_popCheck == false)
      _popCount++;
    
    _total--;
    return value;
  } catch (LlamaUnderflow &e) {
    cerr << "*****\n" ;
    cerr << "Llama Stack error: " << e.what() << endl;
    cerr << "*****\n" ;
  }
}
template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::dup(){

  T value;
  try{
    if(_total == 0)
      throw(LlamaUnderflow("stack is empty"));
  if(_top != nullptr && _extra == true){
    if(_size < LN_SIZE / 2)
      value = _top->m_next->arr[_size-1];
 
  }
  else if (_top != nullptr && _extra == false)
    value = _top->arr[_size-1];
  push(value);
  } catch (LlamaUnderflow &e) {
    cerr << "*****\n" ;
    cerr << "Llama Stack error: " << e.what() << endl;
    cerr << "*****\n" ;
  }
}

template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::rot(){

  // underflow exception
  T value, value2, value3;
  try {
    if(_total < 3)
      throw(LlamaUnderflow ("not enough contents in stack"));
    _popCheck = true;
    value = pop();
    value2 = pop();
    value3 = pop();
    _popCheck = false;
    push(value2);
    push(value);
    push(value3);

  } catch (LlamaUnderflow &e) {
    cerr << "*****\n" ;
    cerr << "Llama Stack error: " << e.what() << endl;
    cerr << "*****\n" ;
  }
}
template <class T, int LN_SIZE>
void Llama<T,LN_SIZE>::swap(){

  // underflow exception
  try{
    if(_total < 2)
      throw(LlamaUnderflow ("not enough contents in stack"));
  _popCheck = true;
  T value, value2;
  value = pop();
  value2 = pop();
  _popCheck = false;
  push(value);
  push(value2);
  } catch (LlamaUnderflow &e) {
    cerr << "*****\n" ;
    cerr << "Llama Stack error: " << e.what() << endl;
    cerr << "*****\n" ;
  }
}

template <class T, int LN_SIZE>
T Llama<T,LN_SIZE>::peek(int offset) const{

  // exception
  try{
    if(_total < offset)
      throw(LlamaUnderflow ("out of range"));

    LlamaNode<T,LN_SIZE> *curr = _top;
    int index = 0;
    int display = 0;
    T value;
    int count = -1;
    while(index < _stackCount)
      {
	
	for(int i=LN_SIZE-1; i != -1; i--)
	  {
	    // popped values
	    if(count > _popCount){
	      display++;
	      if(display-1 == offset){
		value = curr->arr[i];
		index = _stackCount;
	      }
	    }
	    else
	      count++;
	  }
	curr = curr->m_next;
	index++;
      }
  
  return value;
  } catch (LlamaUnderflow &e) {
    cerr << "*****\n" ;
    cerr << "Llama Stack error: " << e.what() << endl;
    cerr << "*****\n" ;
  }
}

template <class T, int LN_SIZE>
const Llama<T,LN_SIZE>& Llama<T,LN_SIZE>:: operator=(const Llama<T,LN_SIZE>& rhs){

  // self assignment check
  if(&rhs != this)
    {
      // check if empty
      if(rhs._top == nullptr)
	_top = nullptr;
      else
	{
	  clearData();
	  buildStack(rhs);
	}
      return *this;
    }
}

#endif
