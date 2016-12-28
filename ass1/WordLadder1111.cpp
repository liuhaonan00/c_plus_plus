/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>

class StrInfo {

	public:
		// StrInfo(std::string str) {
		// 	currentStr = str;
		// }

		void setCertain(unsigned int cer) {
			certain = cer;
		}

		unsigned int getCertain() {
			return certain;
		}

		void setCurrentStr(std::string CurrentStr) {
			currentStr = CurrentStr;
		} 

		std::string getCurrentStr() {
			return currentStr;
		}

		void setPath(std::vector<std::string> Path) {
			path = Path;
		}

		std::vector<std::string> getPath() {
			return path;
		}

		int getLastChangePos() {
			return lastChangePos;
		}

		void setLastChangePos(int pos) {
			lastChangePos = pos;
		};

	private:
		unsigned int certain;
		std::string currentStr;
		std::vector<std::string> path;	
		int lastChangePos;
};

unsigned int difference(std::string word1, std:: string word2);
unsigned int set1(unsigned int num, int pos, int length); 
unsigned int set0(unsigned int num, int pos, int length); 
int checkBit(unsigned int num, int pos, int length);

int searchPath(std::string word, std::vector<std::string> path);
int searchQueue(std::string word, std::vector<StrInfo> queue);

int main() {

	// [TODO: fill in the code]
	Lexicon english("EnglishWords.dat");
	std::cout<<"Hello World"<<std::endl;

	std::cout<<"Enter start word (RETURN to quit): ";
	std::string startWord,endWord;
	std::cin>>startWord;
	std::cout<<"Enter destination word: ";
	std::cin>>endWord;

	// std::cout<<"Start: "<<startWord<<", "<<"end: "<<endWord<<std::endl;

	int stringLen;
	stringLen = startWord.length();

	if (stringLen != endWord.length()) {
		std::cerr<<"The length is not the same"<<std::endl;
		return 0;
	}

	// std::cout<<"The length is "<< stringLen<<std::endl;

	StrInfo strInfo;
	strInfo.setCurrentStr(startWord);
	std::vector<std::string> path(1, startWord);
	strInfo.setPath(path);
	// strInfo.setCertain((unsigned int)stringLen);

	// std::cout<<"CurrentStr: "<<strInfo.getCertain()<<" "<<strInfo.getCurrentStr()<<std::endl;

	// std::vector<std::string> p(1, startWord);
	// p.push_back(endWord);
	// std::cout<<"difference: "<<difference(startWord, endWord)<<std::endl;

	std::cout<<"Start calculation: "<<std::endl;
	std::vector<StrInfo> queue;
	int step = 0;
	queue.assign(1, strInfo);
	strInfo.setLastChangePos(-1);
	std::cout<<"Step "<<step++<<" Insert to queue: "<<strInfo.getCurrentStr()<<std::endl;

	int bestAnswer = 0;
	std::vector<std::vector<std::string>> solution;

	while (queue.size() != 0) {
		strInfo = queue.back();
		queue.pop_back();
		std::cout<<"Get and remove from queue: "<<strInfo.getCurrentStr()<<std::endl;
		std::string word = strInfo.getCurrentStr();
		std::string Word = word;
		for (int i = 0; i < stringLen; i++) {
			word = Word;
			std::cout<<"Current Word: "<<word<<std::endl;
			if (strInfo.getLastChangePos() == i) continue;
			for (char c = 'a'; c <= 'z'; c++) {
				word[i] = c;
				if (english.containsWord(word)) {
					path = strInfo.getPath();
					if (word == endWord) {
						path.push_back(word);
						if (bestAnswer == 0) {
							bestAnswer = path.size();
							solution.assign(1, path);
						} else if (bestAnswer >path.size()) {
							bestAnswer = path.size();
							solution.clear();
							solution.assign(1, path);
						} else if (bestAnswer == path.size()){
							solution.push_back(path);
						}
						std::cout<<"Answer: ";
						for (std::string answer : path) {
							std::cout<<answer<<" ";
						}
						std::cout<<std::endl;
						return 0;
						continue;
					}
					
					if (path.size() >= bestAnswer - 1 && bestAnswer != 0) continue;
					int pathContainsWord = searchPath(word, path); //TODO
					if (pathContainsWord == 1) {
						continue;
					}
					int queueContainsWord = searchQueue(word, queue);
					if (queueContainsWord == 1) {
						continue;
					}

					if (word == Word) continue;
					path.push_back(word);
					strInfo.setPath(path);
					strInfo.setCurrentStr(word);
					strInfo.setLastChangePos(i);
					if (queue.size() == 0) {
						queue.assign(1, strInfo);
						std::cout<<"Step "<<step++<<" Insert to queue: "<<strInfo.getCurrentStr()<<std::endl;
					} else {
						auto it = queue.begin();
						it = queue.insert(it, strInfo);
						std::cout<<"Step "<<step++<<" Insert to queue: "<<strInfo.getCurrentStr()<<std::endl;
					}
				}
			}
		}
		

	}





	return 0;
}

int searchPath(std::string word, std::vector<std::string> path) {
	// std::cout<< "FUNCTION size = "<<path.size()<<std::endl;
	for (std::string i : path) {
		// std::cout<< "FUNCTION:"<<i<<std::endl;
		if (i == word) return 1;
	}
	return 0;
}

int searchQueue(std::string word, std::vector<StrInfo> queue) {
	if (queue.size() == 0) return 0;
	for (StrInfo i : queue) {
		std::string currentWord = i.getCurrentStr();
		if (currentWord == word) return 1;
	}
	return 0;
}

unsigned int difference(std::string word1, std:: string word2) {
	unsigned int result = 0;
	int strLength = word1.length();
	for (int i = 0; i < strLength; i++) {
		if(word1.at(i) == word2.at(i)) {
			result = set1(result, i, strLength);
		} else {
			result = set0(result, i, strLength);
		}
	}

	return result;
}

unsigned int set1(unsigned int num, int pos, int length) {
	unsigned int i = 1;
	i = i<<(length - pos - 1);
	i = num | i;
	return i;
}

unsigned int set0(unsigned int num, int pos, int length) {
	unsigned int i = 1;
	i = i<<(length - pos - 1);
	i = ~i;
	i = num & i;
	return i;
}

int checkBit(unsigned int num, int pos, int length) {
	unsigned int i = num>>(length - pos - 1);
	return (int)i%2;
}
