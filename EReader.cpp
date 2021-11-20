/*************************************************************************
 ** File: EReader.cpp
 ** Project: CMSC 202 Project 5, Spring 2019
 ** Author: Trevor Hughes
 ** Date: 5/2/19
 ** Section: Thurs 8:10
 ** E-mail: thughes1@umbc.edu
 **
 ** This file contains the main menu and all of the functions that the main
 ** menu can run.
 ** This program reads ina file and adds books to a vector. The user can then
 ** add books to their read list and sort it based on price
 **
 **
 ************************************************************************/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include "EReader.h"

#include "Book.h"
#include "Lqueue.h"

using namespace std;

const int BOOK_AMOUNT = 150;

//-------------------------------------------------------------------
// Name: EReader - Default Constructor
// Preconditions: None
// Postcondition: Creates a new EReader
//-------------------------------------------------------------------
EReader::EReader(){
}

//-------------------------------------------------------------------
// Name: EReader - Overloaded Constructor
// Preconditions: None
// Postcondition: Creates a new EReadear and passes the book filename
//-------------------------------------------------------------------
EReader::EReader(string filename){

  // calls function to load the file
  LoadCatalog(filename);
}

//-------------------------------------------------------------------
// Name: ~EReader - Destructor
// Preconditions: None
// Postconditions: Deletes all previously allocated memory
//-------------------------------------------------------------------
EReader::~EReader(){
  int num = m_bookCatalog.size(); // holds the size of the vector of all books

  //runs through the vector and deletes all of the pointers
  for(int i = 0; i < num; i++){
    delete m_bookCatalog[i];
  }
}

//-------------------------------------------------------------------
// Name: LoadCatalog(string filename)
// Preconditions: Requires filename
// Postconditions: Loads the fule into the m_bookCatalog (as boooks)
//-------------------------------------------------------------------
void EReader::LoadCatalog(string filename){
  ifstream myFile;   // ifstream object to help open file
  string title;      // holds the title of the book
  string author;     // holds the author of the book
  string scoreString;// gets the score of the book in a string
  string priceString;// gets the price of the book in a string
  int score;         // holds the score of the book in an int
  double price;      // holds the price of the book in a double;

  //opens the file
  myFile.open(filename);

  //runs the loop while the file still has info
  while(getline(myFile, title, ',')){

    //reads the file info into strings
    getline(myFile, author, ',');
    getline(myFile, scoreString, ',');
    getline(myFile, priceString);

    //changes the variable type to int and double
    score = stoi(scoreString);
    price = stod(priceString);

    //creates a new book and adds it to the vector of books
    Book *book = new Book(title, author, score, price);
    m_bookCatalog.push_back(book);
  }
  cout << "Catalog populated with 150 books." << endl;

  //closes the file
  myFile.close();
}

//--------------------------------------------------------------------
// Name: MainMenu
// Preconditions: None
// Postconditions: Manages the application and the menu
//--------------------------------------------------------------------
void EReader::MainMenu(){
  int input; // holds the users choice
  do{

    //prints out all of the users options
    cout << "\nWhat would you like to do?" << endl;
    cout << "1. Display All Books" << endl;
    cout << "2. Add Book to Readlist" << endl;
    cout << "3. Display Readlist" << endl;
    cout << "4. Sort Readlist by Price" << endl;
    cout << "5. Quit" << endl;

    //asks for the users choice
    cin >> input;
  }

  //keeps asking until the user chooses an actual choice
  while(input < 1 or input > 5);

  // runs different function depending on what was chosen
  switch(input){

    //if user chose 1
  case 1:

    //Displays books then runs menu function again
    DisplayBooks();
    MainMenu();
    break;

    // if user chose 2
  case 2:

    //adds book to the read list and runs menu function again
    AddBook();
    MainMenu();
    break;

    // if the user choses 3
  case 3:

    //Displays read list and runs the menu function again
    DisplayReadlist();
    MainMenu();
    break;

    // if they user choses 4
  case 4:

    // sorts read list my price and runs the menu function again
    SortReadlist();
    MainMenu();
    break;

    // if the user choses 5
  case 5:

    // prints a message and ends the reccursion loop.
    cout << "Thank you for using the UMBC E-Reader" << endl;
    break;
  }
}

//---------------------------------------------------------------------------
// Name: DisplayBooks
// Preconditions: Displays all 150 books
// Postconditions: Lists all books (numbered)
//---------------------------------------------------------------------------
void EReader::DisplayBooks(){

  // prints out every book in the bookCatalog vector
  for(int i = 0; i < BOOK_AMOUNT; i++){
    cout << *m_bookCatalog[i] << endl;
  }
}

//----------------------------------------------------------------------------
// Name: DisplayReadList
// Preconditions: None (can be empty)
// Postconditions: Displays the readlist
//----------------------------------------------------------------------------
void EReader::DisplayReadlist(){

  // prints out the read list
  cout << m_readList;
}

//-----------------------------------------------------------------------------
// Name: AddBook
// Preconditions: m_bookCatalog is populated
// Postconditions: Displays the current list and adds a book to
//                 the m_readList
//-----------------------------------------------------------------------------
void EReader::AddBook(){
  int answer; // holds the users answer
  do{

    // dispays book and asks the user to chose one to add to read list
    cout << "Choose the book you would like to add to your reading list" << endl;
    DisplayBooks();
    cout << "Enter the number of the book you would like to add: " << endl;
    cin >> answer;
  }

  // makes sure that the choice is an actual book
  while(answer <= 0 or answer > BOOK_AMOUNT);
  string title;  // holds the title of the book
  string author; //holds the author of the book
  int rank;      // holds the rank of the book
  double price;  // holds the price of the book

  // creates a new book pointer of the chosen book
  Book *book = m_bookCatalog[answer - 1];

  // sets all of the book sinformation
  title = book->getTitle();
  author = book->getAuthor();
  rank = m_readList.GetSize() + 1;
  price = book->getPrice();

  //ads the new book to the end of the readList linked list
  m_readList.Push(Book(title, author, rank, price), 1);
}

//------------------------------------------------------------------------------
// Name: SortReadList
// Preconditions: Requires Readlist
// Postconditions: Users the overloaded < operator in the Book to sort
//                 the prices from high to low in the m_readList
//------------------------------------------------------------------------------
void EReader::SortReadlist(){
  int test = 1; // holds an int to see if something in the list was changed

  // runs through all of the points while something was changed in the list
  for(int i = 0; i < m_readList.GetSize() and test == 1; i++){

    // changes the test back to 0 to check for a change
    test = 0;

    // runs through the entire list and swaps the nodes needed
    for(int i = 0; i < m_readList.GetSize() - 1; i++){

      // if a node after is less than the node before
      if(m_readList[i + 1] < m_readList[i]){
      }

      // if a node after is greater than the node before
      else{

 //swaps the two nodes places
 m_readList.Swap(i+1);

 // shows the a change was made
 test = 1;
      }
    }
  }

  // changes all of the rank of the books to numericle order
  for(int i = 0; i < m_readList.GetSize(); i++){
    m_readList[i].setRank(i+1);
  }

  // prints out completion message
  cout << "Done Sorting List" << endl;
}
