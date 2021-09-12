/*****************************************
** File:    Decay.cpp
** Author:  Devin Hennayake
**
** This file contains the code for the Decay.h header file
**
***********************************************/
#include "Decay.h"

Decay::Decay(){m_file="";}

Decay::~Decay(){
  EmptyLists();
}

void Decay::EmptyLists(){
  
  for(unsigned int i=0; i < m_list.size(); i++){
    delete m_list.at(i);
  }
  cout << "All lists have been cleared" << endl;
}
void Decay::LoadFile(){

  fstream file;
  char value;
  cout << "What is the name of the file?" << endl;
  cin >> m_file;
  Node* node;
  DecayList* decay = new DecayList();
  
  file.open(m_file.c_str());
  // check if real file
  if(!file.is_open())
    cout << "Invalid file" << endl;
  else{
  while(file >> value){
    if(value != ';'){
      if(value == '1'){
	node = new Node(true);
	decay->InsertEnd(node);
      }
      if(value == '0'){
	node = new Node(false);
	decay->InsertEnd(node);
      }
    }
    else{
      // insert a linked list
      m_list.push_back(decay);
      decay = new DecayList();
    }
  }
  file.close();
  }
}
void Decay::ChooseList(){

  if(m_list.empty())
    cout << "Load a list first" << endl;
  else{
  int userInput;
  do{
    cout << "Which Decay scenario do you want to experience?" << endl; 
    cout << "1. List 1 (3 nodes)" << endl;
    cout << "2. List 2 (6 nodes)" << endl;
    cout << "3. List 3 (30 nodes)" << endl;
    cout << "4. Quit" << endl;
    cin >> userInput;
    switch(userInput){
    case 1:
      RunSimulation(0);
      break;
    case 2:
      RunSimulation(1);
      break;
    case 3:
      RunSimulation(2);
      break;
    case 4:
      cout << "Thank you for using the Decay Simulation" << endl;
      break;
    default:
      cout << "Invalid Choice" << endl;
    }
  }while(userInput != 4);
  }
}
void Decay::CreateRandomList(){
  
  int userInput, value;
  
    Node* node;
    DecayList* decay = new DecayList();

    cout << "How large a list would you like?" << endl;
    cin >> userInput;
    // can't be 0 or less
    while(userInput < 1){
      cout << "How large a list would you like?" << endl;
      cin >> userInput;
    }
    userInput *= 3;
    
    for(int i=0; i<userInput; i++){
      // random 0 or 1
      value = (rand() % 2);
      node = new Node(value);
      decay->InsertEnd(node);
    }
    m_list.push_back(decay);
    RunSimulation(m_list.size() - 1);

}

void Decay::RunSimulation(int index){

  int selection, count;
  int size = m_list.at(index)->GetSize();
  cout << "The sequence has been initialized" << endl;
  bool empty = false;
  while(empty != true){
    do{
      m_list.at(index)->PrintDecayList();
      cout << endl;
      cout << "Which node to change?" << endl;
      for(int i=0; i<size; i++){
	cout << " " << i+1 << "   ";
      }
      cout << endl;
      cin >> selection;
    }while(selection > size || selection < 0); 

    m_list.at(index)->InvertValue(selection - 1);
    count = m_list.at(index)->TraverseList(true);
    empty = m_list.at(index)->CheckEmpty();
  }
  cout << "All nodes from that list have been removed" << endl;
  EmptyLists();
}
void Decay::Start(){
  //bool value;
  int userInput;
  cout << endl;
  cout << "Welcome to Decay" << endl;
  do{
    cout << "1. Load File" << endl;
    cout << "2. Simulate Loaded File" << endl;
    cout << "3. Simulate Random List" << endl;
    cout << "4. Quit" << endl;
    cin >> userInput;
    switch(userInput){
    case 1:
      LoadFile();
      break;
    case 2:
      ChooseList();
      break;
    case 3:
      CreateRandomList();
      break;
    case 4:
      cout << "Thank you for using the Decay Simulator." << endl;
      EmptyLists();
      break;
    default:
      cout << "Invalid Choice" << endl;
    }
  }while(userInput != 4);
}
   
