/*****************************************************************************
 ** File: Lqueue.h
 ** Project: CMSC 202 Projects 5, Spring 2019
 ** Author: Trevor Hughes
 ** Date: 5/2/19
 ** Sectoin: Thurs 8:10
 ** E-mail: thughes1@umbc.edu
 **
 ** This file contains the linked list and some other functions that
 ** involve the linked list and help the other files
 ** This program reads a file of books and lets the user chose them
 ** to add to to their readlist. They can then sort the books
 ** in their readlist by price
 ***************************************************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#ifndef LQUEUE_H
#define LQUEUE_H

template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor
  T& GetData(); //Node Data Getter
  void SetData( const T& data ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  T m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator= (const Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node.
  //                Requires a Lqueue
  // Postconditions: If the bool = false, adds to front else adds a new node to the
  //                 end of the lqueue.
  void Push(const T&, bool);
  // Name: Pop
  // Preconditions: Lqueue with at least one node.
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();
  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();
  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);
  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement Lqueue here


//---------------------------------------------------------------------------
// Name: Lqueue() (Linked List Queue) - Default Constructor
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
//---------------------------------------------------------------------------
template<class T>
Lqueue<T>::Lqueue(){

  // creates a linked list and sets size to 0
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

//---------------------------------------------------------------------------
// Name: ~Lqueue - Destructor
// Preconditions: There is an existing lqueue with at least 1 node
// Postconditions: an lqueue is deallocated
//---------------------------------------------------------------------------
template<class T>
Lqueue<T>::~Lqueue(){

  // create a pointer pointing to m_head
  Node<T> *holder = m_head;

  //runs while the pointer is not at the end of linked list
  while (holder != nullptr){

    // sets holder = to next node and delete what holder was
    Node<T> *remove = holder;
    holder = holder->GetNext();
    delete remove;
  }
}

//----------------------------------------------------------------------------
// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of an existing Lqueue
//                Requires an Lqueue
// Postconditions: Copy of existing Lqueue
//----------------------------------------------------------------------------
template<class T>
Lqueue<T>::Lqueue(const Lqueue& source){

  // initially sets size to 0
  m_size = 0;

  //runs if there is only one node in list
  if(source.m_head == nullptr){
    m_head = nullptr;
    m_tail = nullptr;
  }

  // if there is more than one node
  else{

    //creates a new node with the first data the sources first data
    m_head = new Node<T>(source.m_head->GetData());

    Node<T> *holder = m_head; // points to current m_head
    Node<T> *sourceHead = source.m_head->GetNext(); // points to where other m_head points
    Node<T> *test = sourceHead; // points to where other m_head points

    //runs while it is not at the end of the old linked list
    while(test != nullptr){

      // adds to the end of the current linked list
      holder->SetNext(new Node<T>(test->GetData()));
      test = test->GetNext();
      holder = holder->GetNext();

      //adds one to size
      m_size ++;
    }

    //sets last node = to nullptr
    holder->SetNext(nullptr);

    // sets m_tail = to last node
    m_tail = holder;
  }
}

//------------------------------------------------------------------------------
// Name: operator= (Overloaded Assignment Operator
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires an Lqueue
// Postconditions: Copy of existing Lqueue
//------------------------------------------------------------------------------
template<class T>
Lqueue<T>& Lqueue<T>::operator=(const Lqueue& source){
  Node<T> *holder  = m_head;  // node pointer points to m_head

  // runs while not at last node
  while(holder != nullptr){

    // removes the old linked list
    Node<T> *remove = holder;
    holder = holder->GetNext();
    delete remove;
  }

  // sets the size = to 0
  m_size = 0;

  // checks if linked list has more than 1 node
  if(source.m_head == nullptr){
    m_head = nullptr;
    m_tail = nullptr;
  }

  // if it has more than 1 node
  else{

    // creates new node = to old node
    m_head = new Node<T>(source.m_head->GetData());
    Node<T> *holder = m_head; // pointer to m_head
    Node<T> *sourceHead = source.m_head->GetNext(); // pointer to old m_head
    Node<T> *test = sourceHead; // pointer to old m_head

    // runs while not at last node
    while(test != nullptr){

      // sets new Node = to old one
      holder->SetNext(new Node<T>(test->GetData()));
      test = test->GetNext();
      holder = holder->GetNext();

      // adds one to size
      m_size ++;
    }

    // sets last node = nullptr
    holder->SetNext(nullptr);

    //sets tail = last node
    m_tail = holder;
  }
  return *this;
}

//-----------------------------------------------------------------------------------
// Name: Push
// Preconditions: Takes in data. Creates new Node
//                Requires an Lqueue
// Postconditions: If the bool = false, adds to front else adds a node to the
//                 end of the lqueue.
//----------------------------------------------------------------------------------
template<class T>
void Lqueue<T>::Push(const T& source, bool t){
  Node<T> *tempPtr = new Node<T>(source); // sets new linked list = to old one

  // runs if old linked list was empty
  if(IsEmpty()){
    m_head = tempPtr;
    m_tail = tempPtr;
  }

  // if it wants it added to front
  else if(t == 0){
    tempPtr -> SetNext(m_head);
    m_head = tempPtr;
  }

  // if it wants it added to the back
  else if(t == 1){
    m_tail -> SetNext(tempPtr);
    m_tail = tempPtr;
  }

  // adds one to size
  m_size++;
}

//-----------------------------------------------------------------------------------
// Name: Pop
// Preconditions: Lqueue with at least one node
// Postconditions: Removes first node in the lqueue, returns data from the first node
//-----------------------------------------------------------------------------------
template<class T>
T Lqueue<T>::Pop(){
  T data = m_head->GetData(); // = data in first node

  // if linked list is empty
  if(IsEmpty()){
    return data;
  }
  Node<T> *temp = m_head; // pointer to m_head

  // change head to second node
  m_head = m_head->GetNext();

  // deallocates first node and decreases size
  delete temp;
  m_size --;

  // returns data from first node
  return data;
}

//--------------------------------------------------------------------------------
// Name: Display
// Preconditions: Ouputs the Lqueue
// Postconditions: Displays the data in each node of the lqueue
//--------------------------------------------------------------------------------
template<class T>
void Lqueue<T>::Display(){
  Node<T> *temp; // itterates through linked list
  temp = m_head;

  // while not at end of linked list
  while(temp != nullptr)
    {

      //prints out the data with arrows
      cout << temp->GetData() << "->";
      temp = temp->GetNext();
    }
  cout << "END" << endl;
}

//---------------------------------------------------------------------------------
// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
//----------------------------------------------------------------------------------
template<class T>
T Lqueue<T>::Front(){

  //returns data from m_head
  return m_head->GetData();
}

//---------------------------------------------------------------------------------
// Name: IsEmpty
// Preconditions: Requires an lqueue
// Postconditions: Returns if the lqueue is empty
//----------------------------------------------------------------------------------
template<class T>
bool Lqueue<T>::IsEmpty(){

  // if linked list is empty return true
  if(m_head == nullptr){
    return true;
  }

  // if not return false
  else{
    return false;
  }
  return true;
}

//-----------------------------------------------------------------------------------
// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
//------------------------------------------------------------------------------------
template<class T>
int Lqueue<T>::GetSize(){

  // returns size of linked list
  return m_size;
}

//----------------------------------------------------------------------------------
// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the node at the index with the node prior to it
//----------------------------------------------------------------------------------
template<class T>
void Lqueue<T>::Swap(int num){
  Node<T> *temp1 = m_head; // pointer to head
  Node<T> *temp2 = m_head; // pointer to head
  Node<T> *temp3 = m_head; // pointer to head

  // if they chose the first node
  if(num == 0){
  }

  // if second node was chosen
  else if(num == 1){
    temp1 = temp1->GetNext();
    Node<T> *holder1 = temp1->GetNext(); // points to what the second node is pointing to

    //switches the first and second nodes
    temp2->SetNext(holder1);
    temp1->SetNext(temp2);

    // changes head to the node in front
    m_head = temp1;
  }

  // if num chosen is greater than 1
  else{

    // if num does not equal 1 changes value so it gets the right node
    if(num > 2){
      num = num*2 - 1;
    }

    // runs until you get the right nodes
    for(int i = 0; i < num - 1; i++){
      temp3 = temp2;
      temp2 = temp3->GetNext();
      temp1 = temp2->GetNext();
      i++;
    }
    Node<T> *holder1 = temp1->GetNext(); // holds what temp1 is pointing to
    Node<T> *holder3 = temp3->GetNext(); // holds what temp3 is pointing to

    //switches the nodes
    temp1->SetNext(holder3);
    temp2->SetNext(holder1);
    temp3->SetNext(temp1);
  }

  // if you changed the tail sets tail to last node
  if(temp2->GetNext() == nullptr){
    m_tail = temp2;
  }
}

//----------------------------------------------------------------------------------
// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
//----------------------------------------------------------------------------------
template<class T>
void Lqueue<T>::Clear(){
  Node<T> *tempPtr1 = m_head; // sets pointer to head
  Node<T> *tempPtr2 = nullptr; // creates pointer

  // while linked list is not at the last node
  while(tempPtr1 != nullptr){

    // deletes all of the nodes
    tempPtr2 = tempPtr1->GetNext();
    delete tempPtr1;
    tempPtr1 = tempPtr2;
  }

  // changes size to 0
  m_size = 0;
}

//-----------------------------------------------------------------------------------
// Name: TestHeadTail
// Preconditions: Requires a lqueue
// Postconditions: Returns the value of the head and the tail
//-----------------------------------------------------------------------------------
template<class T>
void Lqueue<T>::TestHeadTail(){

  // prints out the data in the head and tail of list
  cout << "head " << m_head->GetData() << " and tail " << m_tail->GetData() << endl;
}

//-----------------------------------------------------------------------------------
// Name: operator<< (Overloaded << operator)
// Preconditions: Requiers a lqueue
// Postconditions: returns an ostream with the data of each node on a different line
//-----------------------------------------------------------------------------------
template<class U>
ostream& operator<<(ostream& output, const Lqueue<U>& source){
  Node<U> *test1 = source.m_head; // sets pointer to head

  // runs while not at last node
  while(test1 != nullptr){

    // gets data and then prints it out
    U data = test1->GetData();
    output << data << endl;

    // goes to next node
    test1 = test1->GetNext();
  }
  return output;
}

//------------------------------------------------------------------------------------
// Name: Overloaded[] operator
// Preconditions: Lqueue exists
// Postconditions: Returns object from lqueue using []
//------------------------------------------------------------------------------------
template<class T>
T& Lqueue<T>::operator[](int x){
  Node<T> *temp = m_head; // pointer to head

  // runs for as long as asked or until at last node
  for(int i = 0; i < x and temp!= nullptr; i++){
    temp = temp->GetNext();
  }

  // returns data from that node
  return temp->GetData();
}

#endif
//****************************************************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10, 1);
  newLQ1.Push(11, 1);
  newLQ1.Push(12, 1);
  newLQ1.Push(13, 1);
  cout << endl;

  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ1;
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;

  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;

  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;

  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;

  return 0;
  }
*/
