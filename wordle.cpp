#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

//example input: -i-- dn

// Add prototypes of helper functions here
void wordleHelper(
	string s,
	const string& floating,
	size_t x,
	const set<string>& dict,
	set<string>& words); 


// Definition of primary wordle function
set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> words;
		if(in.empty()){ //null case
			return words;
		}

		string s=in; //copy

		wordleHelper(s,floating,0,dict,words);
		return words;
}

// Define any helper functions here
void wordleHelper( //1 letter recursion
	string s,
	const string& floating,
	size_t x, //index
	const set<string>& dict,
	set<string>& words)
{
	//no more floating letters
	if(floating.empty()){
		while(x!=s.size() && s[x]!='-'){ //find next dash
			x++;
		}
	
		if(x==s.size()){ //end of word
			if(dict.find(s)!=dict.end()){ //valid word
				words.insert(s);
			}
			return;
		}

		else{
			for(size_t i=0; i<26; i++){ //fill remaining with alphabet
					string newS = s; //copy
					newS[x]='a'+i;
					wordleHelper(newS,floating,x+1,dict,words);
			}
		}
		return;
	}
	
	//more floating letters
	string newF = floating.substr(0,floating.size()-1);
	for(size_t i=0; i<s.size(); i++){
		if(s[i]=='-'){
			string newS = s; //copy
			newS[i]=floating[floating.size()-1];
			wordleHelper(newS,newF,0,dict,words);
		}
	}
}

