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

class Word{
public:
	void setLast(int last) {
		lastChanged = last;
	}
	int getlast() {
		return lastChanged;
	}

	void setCurWord(std::string cur_word) {
		curWord = cur_word;
	}
	std::string getCurWord() {
		return curWord;
	}

	void setPath(std::vector<std::string> Path) {
		path = Path;
	}
	std::vector<std::string> getPath() {
		return path;
	};


private:
	std::string curWord;
	std::vector<std::string> path;
	int lastChanged;
};

void printWordInfo(Word word);
void printQueue(std::vector<Word> queue);
bool checkPath(std::string wordStr, std::vector<std::string> path);
bool checkQueue(std::string wordStr, std::vector<Word> queue);

int main() {

	// [TODO: fill in the code]
	int step = 1;
	//Preparation 
	Lexicon english("EnglishWords.dat");
	Lexicon wordHistory;
	Lexicon wordThisStep;
	std::vector<Word> queue;
	
	std::vector<std::vector<std::string>> answer;
	std::string startWord,endWord;
	int bestAns = 0;
	int wordLen;

	//Input
	std::cout<<"Enter start word (RETURN to quit): ";
	std::cin>>startWord;
	std::cout<<"Enter destination word: ";
	std::cin>>endWord;


	//Initialize
	if (!wordHistory.isEmpty()) wordHistory.clear();
	if (!wordThisStep.isEmpty()) wordThisStep.clear();

	Word word;
	if (startWord.length() != endWord.length()) {
		return 0;
	}
	wordLen = startWord.length();
	std::vector<std::string> path;
	word.setCurWord(startWord);
	path.assign(1, startWord);
	word.setPath(path);
	word.setLast(-1);
	queue.assign(1, word);
	// std::vector<std::string> wordBuf;
	wordHistory.add(startWord);
	
	//find path
	while(queue.size() > 0) {
		word = queue.back();
		Word w = word; // used to insert to queue
		queue.pop_back();
		// printWordInfo(word);
		// printQueue(queue);
		// std::cout<<"Step "<<step++<<":"<<std::endl;
		for (int i = 0; i < wordLen ; i++) {
			if (word.getlast() == i) continue;
			std::string wordStr = word.getCurWord();
			// std::cout<<"Current str: "<<wordStr<<std::endl;
			
			for (char c = 'a'; c <= 'z' ; c++) {
				path = word.getPath();
				wordStr[i] = c;
				if (!english.containsWord(wordStr)) continue;

				//check path
				
				// if (!checkPath(wordStr, path))  continue;
				// if (!checkQueue(wordStr, queueHistory)) continue;

				//check word history
				if (wordHistory.containsWord(wordStr)) {
					if (!wordThisStep.containsWord(wordStr)) continue;
				}
				if (bestAns != 0 && bestAns <= (int)path.size()) continue;

				if (wordStr == endWord) {
					std::vector<std::string> solution = path;
					solution.push_back(wordStr);
					if (bestAns == 0 || (int)path.size() + 1 == bestAns) {						
						answer.push_back(solution);
						bestAns = solution.size();
					} else if (bestAns != 0 && (int)path.size() + 1 < bestAns) {
						answer.clear();
						answer.push_back(solution);
						bestAns = solution.size();
					} 
					// std::cout<<"Solution Found: ";
					// for (std::string str : solution) {
					// 	std::cout<<str<<" ";
					// } 
					// std::cout<<std::endl;
					// return 0;
					break;
				}

				w.setCurWord(wordStr);
				path.push_back(wordStr);
				w.setPath(path);
				w.setLast(i);

				//Insert to queue
				std::vector<Word>::iterator theIterator = queue.begin();
				queue.insert(theIterator, 1, w);
				
				// wordBuf.push_back(wordStr);
				wordHistory.add(wordStr);
				wordThisStep.add(wordStr);
				if (step < (int)path.size()) {
					
					wordThisStep.clear();
					// std::cout<<"Path length: "<<path.size()<<std::endl;
					step++;
				}

				// std::cout<<"Inserted to queue: "<<wordStr<<"    Path:";
				// for (std::string str : path) {
				// 	std::cout<<" "<<str;
				// }
				// std::cout<<std::endl;
				// printQueue(queue);
			}
		}

	}

	// std::cout<<"Best step = "<<bestAns<<std::endl;

	if (bestAns == 0) {
		std::cout<<"No ladder found."<<std::endl;
	} else {
		std::cout<<"Found ladder: ";
		for (std::vector<std::string> path : answer) {
			std::vector<std::string>::iterator it = path.begin();
			std::cout<<*it;
			it++;
			for (;it != path.end(); it++) {
				std::cout<<" "<<*it;
			}
			std::cout<<std::endl;
		}
	}










	// std::string word = "xx";
	// for (char c0 = 'a'; c0 <= 'z'; c0++) {
	// 	word[0] = c0;
	// 	for (char c1 = 'a'; c1 <= 'z'; c1++) {
	// 		word[1] = c1;
	// 		if (english.containsWord(word)) {
	// 		std::cout << word << std::endl;
	// 		}
	// 	}
	// }

	return 0;
}

void printWordInfo(Word word) {
	// std::cout<<"==============="<<std::endl;
	std::cout<<"Current word: "<<word.getCurWord()<<std::endl;
	std::vector<std::string> path = word.getPath();
	std::cout<<"Current Path length: "<<path.size()<<std::endl;
	for (std::string str : path) {
		std::cout<<str<<" ";
	}
	std::cout<<std::endl;
	// std::cout<<"==============="<<std::endl;
	
}

void printQueue(std::vector<Word> queue) {
	// std::cout<<"==============="<<std::endl;
	std::cout<<"Queue length: "<<queue.size()<<std::endl;
	std::cout<<"Queue str: ";
	for (Word word : queue) {
		std::cout<<word.getCurWord()<<" ";
	}
	std::cout<<std::endl;
	std::cout<<std::endl;
	// std::cout<<"==============="<<std::endl;
}

bool checkPath(std::string wordStr, std::vector<std::string> path) {
	if (path.size() == 0) return true;
	for (std::string str : path) {
		if (str == wordStr) return false;
	}
	return true;
}

bool checkQueue(std::string wordStr, std::vector<Word> queue) {
	if (queue.size() == 0) return true;
	for (Word word : queue) {
		std::string curWord = word.getCurWord();
		if (wordStr == curWord) return false;
	}
	return true;
}