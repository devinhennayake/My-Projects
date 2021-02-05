/*****************************************
** File:    DecayList.cpp
** Project: CMSC 202 Project 3, Fall 2019
** Author:  Devin Hennayake
** Date:    10/29/19
** Section: 22
** E-mail:  devin7@umbc.edu
**
** This file contains the code for the DecayList.h header file
**
***********************************************/
#include "DecayList.h"

DecayList::DecayList(){
  m_head = nullptr;
  m_size = 0;
}

DecayList::~DecayList(){

  Node* node = m_head;
  while(m_head != nullptr){
    node = node->GetNext();
    delete node;
    node = m_head;
  }
  m_head = nullptr;
  m_size = 0;
}

int DecayList::GetSize(){
  m_size = 0;
  Node *temp = m_head;
  while(temp != nullptr){
    ++m_size;
    temp = temp->GetNext();
    }
  return m_size;
}

void DecayList::InvertValue(int index){

  Node *temp = m_head;
  int counter = 0;
  for(temp; temp != nullptr; temp=temp->GetNext()){

    if(counter == index)
      temp->ReplaceValue();
    counter++;
  }
}

bool DecayList::PrintDecayList(){
  
  Node *temp = m_head;
  
  while(temp != nullptr){

    if(temp->GetNext() == nullptr)
      cout << "|" << temp->GetValue() << "|->END" << endl;
    else
      cout << "|" << temp->GetValue() << "|->";
    temp = temp->GetNext();
  }
  
    cout << endl;
    return true;
}

bool DecayList::CheckEmpty(){

  if(m_head == nullptr)
    return true;
  else
    return false;
}

int DecayList::TraverseList(bool check){

  Node *temp = m_head;
  Node *second = temp->GetNext();
  Node *third = second->GetNext();
  int index = 0;
  int num_remove;
  m_size = GetSize();
  // sequence not possible
  if(m_size < NUM_CONSECUTIVE)
    return 0;
  else{
    while(third != nullptr){

      if(temp->GetValue() == check && second->GetValue() == check && third->GetValue() == check){
	num_remove = RemoveNodes(index,NUM_CONSECUTIVE);
	m_size -= num_remove;
      }
      temp = second;
      second = third;
      third = third->GetNext();
      index ++;
    }
  } 
}

int DecayList::RemoveNodes(int index, int NUM_CONSECUTIVE){
  Node* prev = nullptr;
  Node* current = m_head;
  Node* temp;
  int num_removed = 0;
  int i = 0;
  
  // get current to where index is
    while (i < index){
      if (current != nullptr){
	prev = current;
	current = current->GetNext();
      }
      else{
	// not enough elements in list to get to current
	return 0;
      }   
      ++i;
    }
    // perform deletion of next NUM_CONSECUTIVE
    i = 0;
    while (i < NUM_CONSECUTIVE){
      if (prev == nullptr){
	temp = m_head;
	m_head = m_head->GetNext();
	current = m_head;
	delete temp;
	++num_removed;
      }
      else if(current->GetNext() == nullptr){
	temp = m_head;
	m_head = nullptr;
	delete m_head;
	return ++num_removed;
      }
      else{
	// last element
	if (current->GetNext() ==nullptr){
	  temp = current;
	  prev->SetNext(nullptr);
	  delete temp;
	  return (++num_removed);
	}
	else{
	  temp = current;
	  prev->SetNext(current->GetNext()); 
	  delete temp;
	  ++num_removed;
	}
      }
      ++i;
    }
}

void DecayList::InsertEnd(Node* node){
  
  Node *temp = m_head;
  if(temp == nullptr)
    m_head = node;
  else{
  while(temp->GetNext() != nullptr){
     temp = temp->GetNext();
  }
    temp->SetNext(node);
  }
}
