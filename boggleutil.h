/*
 * Filename: boggleutil.h
 * Author: Hrach Beglaryan A09501980
 * Userid: hbeglary, A09501980
 * Description: Header file for boggleutil.cpp
 * Date: 3/13/14
 */
#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include <set>
#include <string>

#define OFFSET 97
#define MAXSIZE 26

using namespace std;

class Trie;	// Forward Declaration

/* Class which holds a single node for a Trie */
class TrieNode{
  public:
  
  TrieNode (char chr,bool used,bool end):chr(chr){
    END = end;
    USED = used;
    point = 0;
  }
  char chr;	// character to be inserted
  Trie* point;	// Pointer to Trie
  bool END;	// Boolean for for an end of character of word
  bool USED;	// Boolean flag if the word has been checked
};

////////////////////////////////////////////////////////////////////

/* Tree that is composed of an array of TrieNodes */
class Trie{

  public:
  TrieNode* nodes[MAXSIZE];  
/**
 * Constructor that creates array of TrieNodes
 */  
  Trie(){
    for(int i=0;i<MAXSIZE;i++){
      nodes[i] = new TrieNode((char)i+OFFSET,false,false);
    }
  }
/**
 * Desctuctor that will delete all nodes and sub-trees
 */
  ~Trie(){
    destroy(nodes);
    delete(nodes);
  }
  
  private:

/**
 * Deletes all nodes
 */
  static void destroy(TrieNode* nodes[MAXSIZE]){
    for(int i=0;i<MAXSIZE;i++){
      if(nodes[i]->USED==true){
	nodes[i]->USED=false;
	destroy(nodes[i]->point->nodes);
      }
      delete(nodes[i]);
    }
  }
};

//////////////////////////////////////////////////////////////////////////

class BoggleUtil{
  public:
/**
 * Method Name: insertSet
 * Description: inserts passed argument into our set
 * Param: A single string
 * Returns: None
 */  
  void insertSet(const string word);
/**
 * Method Name: insert
 * Description: Will insert passed word into passed trie
 * Param: two parameters:First is a pointer to a Trie; Second is a string.
 * Returns: None 
 */ 
  void insert(Trie* trie, string word);
/**
 * Method Name: search
 * Description: Will search for a word in a passed Trie
 * param: two parameters: One is a Trie pointer; Second is a string
 * Returns: boolean
 */  
  bool search(Trie* trie, string word);
/* Will store all valid words */  
  set<string> lexSet;
};
#endif
