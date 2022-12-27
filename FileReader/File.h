#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "Options.h"

// Stores data from read file as a sorted map
class File
{
private:
	// Stores data about each mentioned word and their quantity
	std::unordered_map<std::string, int> wordMap;
	std::shared_ptr<std::vector<std::string>> specialWords;

	// Used to sort word counter hash map by word length
	bool compare(std::pair<std::string, int>& pair1, 
		std::pair<std::string, int>& pair2);

	// Implementation of the file tasks
	std::string findMinWord() const;
	std::string findMaxWord() const;
	int totalWordCount() const;
	int specificWordCount(std::string word) const;

protected:
	void addWord(std::string newWord);
	void emptyWordMap();
	virtual std::string getCalculations() const;

public:
	File(std::shared_ptr<std::vector<std::string>> specialWords);
	~File(void);	
};

