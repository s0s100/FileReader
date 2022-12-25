#include <fstream>
#include "FileReader.h"
#include "File.h"
#include <iostream>

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

	mutex_.lock();

	std::fstream stream(filePath);
	unsigned char newChar;
	std::string newWord;
	while (stream >> newChar) {
		if (newChar == SPACE_NUMBER) {
			addWord(newWord);
			newWord = "";
		}
		else {
			newChar = std::tolower(newChar);
			newWord += newChar;
		}
	}

	 mutex_.unlock();
}

std::string FileReader::getCalculations()
{
	std::cout << "Wtf am I? " << &filePath << std::endl;
	std::cout << "Wtf am I 2? " << std::string(filePath) << std::endl;

	std::string output;
	output = "File path: " + std::string(filePath) + "\n";
	output += File::getCalculations();

	return output;
}
