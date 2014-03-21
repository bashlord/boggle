/**
 * Filename: boggleplayer.h
 * Author: Hrach Harry Beglaryan
 * Userid: hbeglary
 * Description: Header file for boggleplayer.cpp
 * Date: 3/13/14
 */
#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "boggleutil.h"
#include "iboggleplayer.h"
#include <set>
#include <string>
#include <vector>
using namespace std;
class BogglePlayer: public IBogglePlayer{
  
  public:
/**
 * Name:BogglePlayer
 * Description: Default constructor
 */  
  BogglePlayer();
/**
 * Name: buildLexicon
 * Description:Will build our trie that contains all the 
 * valid words.
 * Preconditions: Must have a valid set of strings
 * Postconditions: None
 * Param: a sets of strings
 * returns:None
 */
  virtual void buildLexicon(const vector<string>& word_list);
/**
 * Name: setBoard
 * Description: Sets the vales of our board from passed arguements.
 * Preconditions:Must have board setup to populate
 * Postcondition: sets bourdBuilt bool to true
 * param: 3 parameters:The first two are our board size of rows and cols
 * and the third is a double pointer string
 * Returns: None
 */   
  virtual void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
/**
 * Name: getAllValidWords
 * Description: Populates the set of strings being passed in with all
 * valid words on our board.
 * Precondition: Lexicon must have been built and board must have 
 * been set
 * Postcondtion: None
 * Returns: bool
 */  
  virtual bool getAllValidWords(unsigned int minimum_word_length,set<string>* words);
/**
 * Name: inInLexicon
 * Description: Checks if a given word is in our lexicon trie
 * Precondition: String passed in must not be empty or contain
 * and spaces
 * Postcondition: None
 * Param: String that will be checked
 * Returns: bool
 */
  bool isInLexicon(const string& word_to_check);
/**
 * Name: isOnBoard
 * Description: Checks if given word is on our board
 * Precondition: setBoard must of been called 
 * Postcondition: None
 * Param: String that will be checked
 * Returns: vector<int> that contains coordinates
 */ 
  virtual vector<int> isOnBoard(const string& word_to_check);
/**
 * Name:getCustomboard
 * Description: Does nothing
 * Returns: None
 */  
  void getCustomBoard(string** &new_board,unsigned int *rows, unsigned int *cols);
/**
 * Name: isInVector
 * Description: Checks if a given value is contained in given vector<int>
 * Preconditino:None
 * Poscondition:None
 * Param: vecot<int> and integer
 * Returns: bool
 */  
  virtual bool isInVector(vector<int> pathway,int value);
/**
 * Name: findWord
 * Description: Will be used to find a given word recursively
 * Param: 4 argumenets: First two are coordinates;Second is the string
 * that will be check; and third is count for the current character on
 * string
 * Returns: integer
 */   
  bool findWord(int x, int y, string& word_to_check);

/**
 * Function Name: checkSection
 * Description: This function will check an array element and see if any 
 * 		matches are found.
 * Parameters:
 * 	word -- address of the string we are checking for
 * 	y -- y coordinate
 * 	x -- x coordinate
 * Return: boolean
 * 	true -- if passes
 * 	false -- if fails
 */
  bool checkSection(string &word,int y,int x);
  
  BoggleUtil util;
  Trie* trie;		// Tree where out lexicon will be stored in
  int rows;		// NUmber of rows our array will have
  int cols;		// Number of columns our array will have
  bool lexBuilt;	
  bool boardBuilt;
  vector<int> coord;	// coordinates will be stored in here 
  string** board;	// Dynamic two dimensional array for our board
/**
 * Name: ~BogglePlayer
 * Description: Desctructor
 */  
  ~BogglePlayer();
};
#endif
