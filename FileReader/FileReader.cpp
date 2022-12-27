#include <fstream>
#include <iostream>
#include "FileReader.h"

FileReader::FileReader(const char* filePath, std::shared_ptr<std::vector<std::string>> specialWords) :
	File(specialWords) , filePath(filePath) {}

FileReader::~FileReader(void) {}

bool FileReader::isAvailable() {
	std::fstream stream(filePath);
	bool result = stream.good();
	stream.close();

	return result;
}

void FileReader::readFile() {
	if (!isAvailable()) {
		throw std::runtime_error("File is not available!");
		return;
	}

	mutexLock.lock();

	emptyWordMap();
	 
	// Parse the document
	std::fstream stream(filePath);
	unsigned char newChar;
	std::string newWord;
	while (stream >> std::noskipws >> newChar) {
		if (newChar == SPACE_NUMBER) {
			if (newWord != "") {
				addWord(newWord);
				newWord = "";
			}
		}
		else {
			newChar = std::tolower(newChar);
			newWord += newChar;
		}
	}

	if (newWord != "") {
		addWord(newWord);
	}

	mutexLock.unlock();
}

// Also prints current progress and waits if required
void FileReader::testReadFile(std::string threadName) {
	if (!isAvailable()) {
		throw std::runtime_error("File is not available!");
		return;
	}

	std::string ouputTrying = threadName + " trying access! \n";
	std::cout << ouputTrying;

	mutexLock.lock();

	std::string ouputGranted = threadName + " accessed! \n";
	std::cout << ouputGranted;

	// Wait for a while
	// std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	// First empty word map
	emptyWordMap();

	// Parse the document
	std::fstream stream(filePath);
	unsigned char newChar;
	std::string newWord;
	while (stream >> std::noskipws >> newChar) {
		if (newChar == SPACE_NUMBER) {
			if (newWord != "") {
				addWord(newWord);
				newWord = "";
			}
		}
		else {
			newChar = std::tolower(newChar);
			newWord += newChar;
		}
	}

	if (newWord != "") {
		addWord(newWord);
	}

	std::string ouputExitTrying = threadName + " trying exit! \n";
	std::cout << ouputExitTrying;
	
	mutexLock.unlock();

	std::string ouputExited = threadName + " exited! \n";
	std::cout << ouputExited;
}

std::string FileReader::getCalculations()
{
	std::string output;
	output = "File path: " + std::string(filePath) + "\n";
	output += File::getCalculations();

	return output;
}
