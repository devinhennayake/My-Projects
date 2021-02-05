/*****************************************
** File:    Node.cpp
** Project: CMSC 202 Project 3, Fall 2019
** Author:  Devin Hennayake
** Date:    10/29/19
** Section: 22
** E-mail:  devin7@umbc.edu
**
** This file contains the code for the Node.h header file
**
***********************************************/
#include "Node.h"

Node::Node(){
  m_next = nullptr;}

Node::~Node(){
  
  m_next = nullptr;
}

Node::Node(bool value){
  m_value = value;
  m_next = nullptr;
}

void Node::ReplaceValue(){

  if(m_value == true)
    m_value = false;
  else
    m_value = true;
}

void Node::SetNext(Node* next){

  if(next == nullptr)
    m_next = nullptr;
  else
    m_next = next;
}

Node* Node::GetNext(){
  return m_next;
}

bool Node::GetValue(){
  return m_value;
}
