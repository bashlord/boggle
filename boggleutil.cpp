/*
 * Filename: boggleutil.cpp
 * Author: Hrach Beglaryan
 * Userid: hbeglary, A09501980
 * Description: Contains the insert and search functions for
 * 		the trie traversal
 * Date: 3/13/14
 */

#include "boggleutil.h"
#include <set>
#include <string>
#include <ctype.h>

#define ASCII_VALUE 97

using namespace std;


void BoggleUtil::insertSet(const string word){
  lexSet.insert(word);//inserted word into the lex
}

void BoggleUtil::insert(Trie* trie,string word){
  if(word.length()==0)
    return;
  int i =0;
  while(word[0] != trie->nodes[i]->chr){
    i++; 
  }
  if(trie->nodes[i]->USED==false){//turns on the used flag
    trie->nodes[i]->USED=true;
    if(word.length()==1)
      trie->nodes[i]->END=true;//turns on the end word flag
    trie->nodes[i]->point = new Trie();
  }
  insert(trie->nodes[i]->point,word.substr(1,word.length() ) ) ; //recurses
}

bool BoggleUtil::search(Trie* trie,string word){
  string str = word;
  bool done = false;
  TrieNode** nodes1 = trie->nodes;
  int index = word[0] - ASCII_VALUE;
  while( !done ){
/* Check to see if index is marked as used */
    if( nodes1[index]->USED == true ){
/* Reached end of word and index is and END index: return true */
      if(str.length() == 1 && nodes1[index]->END == true)
        return true;
/* Reached end of word and not an END index */
      else if( str.length() == 1 )
        return false;
/* Keep interating */
      nodes1 = nodes1[index]->point->nodes;
      str = str.substr(1,str.length());
      index = str[0] - ASCII_VALUE;
    }
    else
      return false;
  }
}
