/*
 * Filename: boggleplayer.cpp
 * Author: Hrach Beglaryan
 * Userid: hbeglary, A09501980
 * Description: Implements a lexicon to hold all possible words that can
 * 		be created against the set up boggle board that we have.  
 * 		Also creates a traversal that allows pathways by using 
 * 		the made lexicon trie and finds words based off of it.
 * Date: 3/14/14
 */

#include "boggleplayer.h"
#include <vector>
#include <string>
#include <set>
#include <ctype.h>
#include <iostream>
using namespace std;

BogglePlayer::BogglePlayer(){}

BogglePlayer::~BogglePlayer(){
  trie->~Trie();
}

void BogglePlayer::buildLexicon(const vector<string>& word_list){
  BogglePlayer::lexBuilt=true;	//bool to see if the lex was created
  vector<string> word = word_list;
  this->trie = new Trie();	// Creates a new trie
  string str[word_list.size()];
  for(std::vector<string>::iterator it=word.begin();it!=word.end();++it){
    BogglePlayer::util.insert(this->trie,*it); //insert method for words
    BogglePlayer::util.insertSet(*it);
  }
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, 
					       string** diceArray)
{
  BogglePlayer::rows = rows;
  BogglePlayer::cols = cols;
  BogglePlayer::boardBuilt=true; //bool to see if board was built
  board = diceArray; 		 //sets board
}
bool BogglePlayer::isInLexicon(const string& word_to_check){
  if(word_to_check.size()==0)//if size is 0 is not in lex
    return false;
  for(int i = 0 ;i<word_to_check.size();i++)//makes checks for spaces
    if((int)word_to_check[i]==32)
      return false;
  return util.search(this->trie,word_to_check);//searches for a lexicon
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, 
						  set<string>* words)
{
  //checks to see if the lex was built and board was initilized
  if(BogglePlayer::lexBuilt==false || BogglePlayer::boardBuilt==false)
    return false;
  for(set<string>::iterator it=util.lexSet.begin();it!=util.lexSet.end();++it){
    //checks to see if the word is of min length and is on the board
    if((*it).size()>=minimum_word_length && isOnBoard(*it).size()!=0){
      words->insert(*it);
    }
  }
  //checks to see if words is populated with valid words
  if(words->size()==0)
    return false;
  return true;
}

bool BogglePlayer::checkSection(string &word, int y, int x ){
  string ch = board[y][x]; // Set ch to the string in that block
  int placeCount = 0;	   // Keeps track of characters in word
  int i = 0;		   // used to iterate through our word
/* 
 * Traverse through word the characters with ch
 */  
  for(i = 0; i<word.size();i++){
/* If not equal than break out of for loop */    
    if(word[i] != tolower(ch[i]) )
      break;
    else	/* increment placeCount */
      placeCount++;
  }
/* Checks if the index is less than the size of ch */  
  if( i < ch.size() )
    return false;
  else{
    coord.push_back(y*cols+x);	// Add coordinate 
    word = word.substr(placeCount,word.size()); //Get Substring
    return true;
  }
}
bool BogglePlayer::findWord(int x,int y, string& word_to_check){
  string word = word_to_check;	// Copy of the parameter. Will be manipulated
  string word1 = word;
  
  int rows = BogglePlayer::rows;
  int cols = BogglePlayer::cols; 
  int i = 0;
  bool check;			// Retains return value of checkSection
  bool returnCheck =  false;	// Retains return value of recursion

/* 
 * If the word is empty that signifies that the word has been found because each
 * recursion will strip that characters that were found from the beginning of
 * the word.
 */ 
  if(word_to_check.size() == 0)
    return true;
/*
 * Will begin to check all the possible cases of the matching characters. There
 * are eight possible checks being done.
 */
  if(y+1<rows && word[i]==tolower((this->board[y+1][x])[i]) 
    && isInVector(coord,(y+1)*cols+x) && !returnCheck ){
    if(check = checkSection(word,y+1,x)){
      returnCheck = findWord(x,y+1,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop off last coordinate
      }
    }
  }
  
  if(0<=y-1  && word[i]==tolower((this->board[y-1][x])[i]) 
    	     && isInVector(coord,(y-1)*cols+x) && !returnCheck ){
    if(check = checkSection(word,y-1,x)){
      returnCheck = findWord(x,y-1,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop Off last coordinate
      }
    }
  }
  
  if(x+1<cols  && word[i]==tolower((this->board[y][x+1])[i]) 
    	       && isInVector(coord,(y)*cols+x+1)&& !returnCheck){
    if(check = checkSection(word,y,x+1)){
      returnCheck = findWord(x+1,y,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop Off last coordinate
      }
    }
  }
  
  if(0<=x-1 && word[i]==tolower((this->board[y][x-1])[i]) 
    	    && isInVector(coord,(y)*cols+x-1) && !returnCheck){
    if(check = checkSection(word,y,x-1)){
      returnCheck = findWord(x-1,y,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop off last coordinate
      }
    }
  }
  
  if(0<=y-1 && 0<=x-1 && word[i]==tolower((this->board[y-1][x-1])[i]) 
    	    && isInVector(coord,(y-1)*cols+x-1) && !returnCheck){
    if(check = checkSection(word,y-1,x-1) ){
      returnCheck = findWord(x-1,y-1,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop off last coordinate
      }
    }
  }
  
  if(0<=y-1 && x+1<cols  && word[i]==tolower((this->board[y-1][x+1])[i]) 
    	    && isInVector(coord,(y-1)*cols+x+1) && !returnCheck){ 
    if(check = checkSection(word,y-1,x+1)){
      returnCheck = findWord(x+1,y-1,word);
      if(!returnCheck){		// bad Return
	word = word1;		// Reset word
	coord.pop_back();	// pop off last coordinate
      }
    }
  }
  
  if(y+1<rows && x+1<cols && word[i]==tolower((this->board[y+1][x+1])[i]) 
    	      && isInVector(coord,(y+1)*cols+x+1) && !returnCheck){
    if(check = checkSection(word,y+1,x+1)){
      returnCheck = findWord(x+1,y+1,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop Off Last Coordinate
      }
    }
  }
  
  if(y+1<rows && 0<=x-1 && word[i]==tolower((this->board[y+1][x-1])[i])
    	      && isInVector(coord,(y+1)*cols+x-1) && !returnCheck){
    if(check = checkSection(word,y+1,x-1)){
      returnCheck = findWord(x-1,y+1,word);
      if(!returnCheck){		// Bad Return
	word = word1;		// Reset Word
	coord.pop_back();	// Pop off last coordinate
      }
    }
  }

/* 
 * This section is only reached if all the possible sections fail or the word is
 * found. If the word is found than returnCheck will be true and true will be
 * return. Else return false
 */
  if(returnCheck)
    return true;
  return false;
}

vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
  coord.clear(); 	// clear coordinates for new search
  string word;		// Lower case copy of word_to_check
  string word1;		// Will contain copy of word

/* Lower case the parameter and store in word */
  for(int i = 0;i<word_to_check.size();i++)
    word+=tolower(word_to_check[i]);
  
  word1=word;  // Copy
  
  int rows = BogglePlayer::rows;
  int cols = BogglePlayer::cols;
  int placeCount = 0;	// Keeps track of characters in word
  int index = 0;	// Will be used to iterate through our double array
  string  ch;		// Will contain the string in each block

/* Double for loop to traverse through the double array of strings */  
  for(int y=0;y<rows;y++){
    for(int x=0;x<cols;x++){
      ch = board[y][x];		// Set ch to equal string at block
      for(index = 0; index<word.size();index++){
	if(word[index] != tolower(ch[index]) )	// Break if not equal
	  break; 
	else
	  placeCount++;		// increment count
      }
/* Check for no matches found */      
      if(index !=  ch.size() ){	
	placeCount = 0;	// Reset placeCount
	coord.clear();	// Clear coordinates
      }
/* Potential match case */      
      else{
	coord.push_back(y*cols+x);	// Add coordinate 
	word = word.substr(placeCount,word.size());	// Get Substring
	placeCount = 0;		// Reset placeCount
	if(findWord(x,y,word))	// Call findWord, if true than return
	  return coord;
	else{
	  word = word1;		// Reset word 
	  coord.clear();	// clear coordinates again
	}
      }
    }
  }  
  return coord; //Returns empty coordinates at the end of loops
}
bool BogglePlayer::isInVector(vector<int> pathway, int value){
/* 
 * Iterates through vector and checks if the position on the boggleboard has
 * been accessed
 */  
  for(vector<int>::iterator it = pathway.begin(); it!=pathway.end();++it){
    if(value==*it)
      return false;
  }
  return true;
}

void BogglePlayer::getCustomBoard(string** &new_board,unsigned int *rows, 
						      unsigned int *cols){
  *rows = 20;
  *cols = 23;

   

  string row0[] = {"c","f","a","j","g","h","f","d","b","f","d","j","i","c","g","f","c","a","j","d","b","g","e"};
  string row1[] = {"g","j","e","h","a","h","i","i","g","a","g","f","b","f","j","b","b","a","e","a","h","e","g"};
  string row2[] = {"b","e","f","g","b","c","b","j","d","i","a","f","j","d","d","e","f","f","d","i","c","e","j"};
  string row3[] = {"f","j","a","f","a","b","d","a","f","i","f","e","a","g","b","g","i","h","d","c","d","i","c"};
  string row4[] = {"c","g","h","a","c","c","b","e","a","f","c","j","e","b","a","b","g","a","c","d","j","g","j"};
  string row5[] = {"f","d","j","f","g","h","c","j","h","b","j","c","i","b","b","f","e","h","d","h","d","h","h"};
  string row6[] = {"i","d","b","b","d","b","a","g","i","e","j","a","i","i","i","j","e","a","f","a","d","e","e"};
  string row7[] = {"d","d","c","g","e","c","g","e","i","c","b","d","d","i","g","h","d","b","c","f","h","d","i"};
  string row8[] = {"g","e","h","d","g","j","c","g","a","i","a","c","g","b","e","h","a","d","f","j","h","j","a"};
  string row9[] = {"b","c","e","j","d","a","g","a","j","f","g","a","i","a","d","g","f","h","g","e","g","b","i"};
  string row10[]= {"g","c","d","c","b","j","f","b","j","b","b","f","g","a","g","j","e","c","c","e","a","d","a"};
  string row11[]= {"e","c","d","g","i","h","c","b","h","a","c","b","h","h","f","d","b","i","b","h","a","c","g"};
  string row12[]= {"c","f","c","a","j","i","i","a","i","d","c","h","h","b","f","a","f","a","h","b","e","f","d"};
  string row13[]= {"a","i","c","c","a","g","g","f","j","c","f","i","e","i","e","b","d","b","b","f","f","d","f"};
  string row14[]= {"d","i","j","b","i","i","e","c","e","b","g","f","e","h","c","h","e","j","e","b","d","b","i"};
  string row15[]= {"c","b","j","i","e","c","g","b","a","d","a","i","e","h","j","i","g","e","a","c","a","e","j"};
  string row16[]= {"g","d","i","j","i","b","g","a","f","j","d","d","c","i","c","b","j","f","b","g","e","g","h"};
  string row17[]= {"d","c","g","h","g","e","i","j","j","a","f","d","c","e","h","j","c","d","j","e","d","g","e"};
  string row18[]= {"d","d","a","g","c","a","g","b","d","a","a","d","i","a","d","a","e","a","d","i","b","g","f"};
  string row19[]= {"d","d","g","g","a","c","e","i","d","c","g","d","f","g","e","b","a","f","h","a","i","b","i"};


  string *new_board1[] = {row0,row1,row2,row3,row4,row5,row6,row7,row8,row9,row10,row11,row12,row13,row14,row15,
  			  row16,row17,row18,row19};
  new_board = new string*[20];
  for(int i = 0;i<20;i++)
    new_board[i] = new string[23];


  for(int i = 0;i< 20;i++){
    for(int j=0;j< 23;j++){
      new_board[i][j] = new_board1[i][j];
    }
  }


}
  
