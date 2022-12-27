#include "File.h"

File::File(std::shared_ptr<std::vector<std::string>> specialWords) : 
	specialWords(specialWords) {}

File::~File(void) {}

bool File::compare(std::pair<std::string, int>& pair1, 
	std::pair<std::string, int>& pair2) {

	if (pair1.first.length() > pair2.first.length()) {
		return true;
	}

	return false;
}

void File::addWord(std::string newWord) {	
	auto foundPair = wordMap.find(newWord);
	if (foundPair != wordMap.end()) {
		foundPair->second++;
	}
	else {
		wordMap.insert({newWord, 1});
	}
}

std::string File::findMinWord() const {
	int minWordLength = std::numeric_limits<int>::max();
	int curWordLength;
	std::string result = "";

	for (auto it = wordMap.begin(); 
		it != wordMap.end(); it++) {

		curWordLength = (int) it->first.length();
		if (curWordLength < minWordLength) {
			minWordLength = curWordLength;
			result = it->first;
		}
	}

	return result;
}
std::string File::findMaxWord() const {
	int maxWordLength = std::numeric_limits<int>::min();
	int curWordLength;
	std::string result = "";

	for (auto it = wordMap.begin(); 
		it != wordMap.end(); it++) {

		curWordLength = (int) it->first.length();
		if (curWordLength > maxWordLength) {
			maxWordLength = curWordLength;
			result = it->first;
		}
	}

	return result;
}

int File::totalWordCount() const {
	int result = 0;

	for (auto it = wordMap.begin(); 
		it != wordMap.end(); it++) {

		result += it->second;
	}

	return result;
}

int File::specificWordCount(std::string word) const {
	if (wordMap.count(word)) {
		auto wordPair = wordMap.find(word);
		return wordPair->second;
	}
	
	// No such word so 0 is returned
	return 0;
}

std::string File::getCalculations() const {
	// Calculate required data
	std::string minWord = findMinWord();
	std::string maxWord = findMaxWord();
	int wordCount = totalWordCount();

	std::vector<int> specialWordResult(specialWords.get()->size());
	size_t specialWordSize = specialWords.get()->size();

	for (unsigned int i = 0; i < specialWordSize; i++) {
		auto& word = specialWords.get()->at(i);
		specialWordResult.at(i) = specificWordCount(word);
	}

	// Add to output
	std::string output;
	output = "Min word: " + minWord + "\n";
	output += "Max word: " + maxWord + "\n";
	output += "Total word count: " + std::to_string(wordCount) + "\n";

	// Print result for each special word
	for (unsigned int i = 0; i < specialWordSize; i++) {
		output += specialWords.get()->at(i) + " encountered: "
			+ std::to_string(specialWordResult.at(i)) + "\n";
	}

	return output;
}

void File::emptyWordMap() {
	wordMap.clear();
}