/******************************************************************
 ** File: Book.cpp
 ** Project: CMSC 202 Projects 5, Spring 2019
 ** Author: Trevor Hughes
 ** Date: 5/1/19
 ** Section: Thurs, 8:10 pm
 ** E-mail: thughes1@umbc.edu
 **
 ** This file contains the information of a book that can be used
 ** in several different way.
 ** This program reads in a file of books and then the user gets
 ** the choice to add books to their read list and sort them
 ** by price.
 **
 **
 *****************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

#include "Book.h"

using namespace std;

//----------------------------------------------------------------
// Name: Book - Default Constructor
// Precondition: None
// Postcondition: Creates a default book
//----------------------------------------------------------------
Book::Book(){
}

//-----------------------------------------------------------------
// Name: Book - Overloaded Constructor
// Precondition: requires title, author, rank and price(in dollars)
// Postcondition: Creates a book based on passed parameters
//-----------------------------------------------------------------
Book::Book(string title, string author, int rank, double price){

  // sets the private variables to what is passed in
  m_title = title;
  m_author = author;
  m_rank = rank;
  m_price = price;
}

//------------------------------------------------------------------
// Name: getTitle - Accessor
// Precondition: Book exists
// Postcondition: Returns the title of the book
//------------------------------------------------------------------
string Book::getTitle()const{
  return m_title;
}


//------------------------------------------------------------------
// Name: getAuthor() - Accessor
// Precondition: Book exists
// Postcondition: Returns the name of the author
//------------------------------------------------------------------
string Book::getAuthor()const{
  return m_author;
}

//------------------------------------------------------------------
// Name: getRank - Accessor
// Precondition: Book exists
// Postcondition: Returns the rank of the book
//------------------------------------------------------------------
int Book::getRank()const{
  return m_rank;
}

//------------------------------------------------------------------
// Name: getPrice() - Accessor
// Precondition: Book exists
// Postcondition: Returns the price of the book
//------------------------------------------------------------------
double Book::getPrice()const{
  return m_price;
}

//------------------------------------------------------------------
// Name: setTitle(string) - Mutator
// Precondition: Book exists
// Postcondition: Sets the title of the book
//------------------------------------------------------------------
void Book::setTitle(string title){
  m_title = title;
}

//------------------------------------------------------------------
// Name: setAuthor(string) - Mutator
// Precondition: Book exists
// Postcondition: Sets the author of the book
//------------------------------------------------------------------
void Book::setAuthor(string author){
  m_author = author;
}

//------------------------------------------------------------------
// Name: setRank(int) - Mutatotr
// Precondition: Book exists
// Postcondition: Sets the rank of the book
//------------------------------------------------------------------
void Book::setRank(int rank){
  m_rank = rank;
}

//------------------------------------------------------------------
// Name: setPrice(double) - Mutator
// Precondition: Book exists
// Postcondition: Sets the price of the book
//------------------------------------------------------------------
void Book::setPrice(double price){
  m_price = price;
}

//------------------------------------------------------------------
// Overloaded << - Prints the details of a book
// Preconditions: all variables are set valid
// Postconditions: returns an ostream with details
//------------------------------------------------------------------
ostream &operator<<(ostream& output, Book& book){
  string title;  // holds the title of the book
  string author; // holds the author of the book
  int rank;      // holds the rank of the book
  double price;  // holds the price of the book

  //sets the variables equal to the books information
  title = book.getTitle();
  author = book.getAuthor();
  rank = book.getRank();
  price = book.getPrice();

  //prints the information out in the correct format
  output << setw(3) << right << rank << "." << setw(41) << title << setw(25) << author << setw(5) << " " << fixed << setprecision(2) << "($" << left << price <<  ")";
  return output;
}

//------------------------------------------------------------------
// Overloaded < - comapres the price of the book
// Preconditions: all variables are set valid
// Postconditions: returns true if lhs price is less than rhs price
//------------------------------------------------------------------
bool operator< (Book const & lhs, Book const & rhs){

  //checks if the second books price is greater than the first books
  if(lhs.m_price < rhs.m_price){
    return true;
  }

  //if the first book price was higher
  else{
    return false;

  }
}
