#include <iostream>
#include "ParallelFileRead.h"

ParallelFileRead::ParallelFileRead(std::vector<std::string> specialWords) : specialWords(specialWords) {
	toLowerCase(this->specialWords);
}

ParallelFileRead::~ParallelFileRead(void) {}

std::vector<std::filesystem::path> ParallelFileRead::findReadableFiles(const char* path) {
	std::vector<std::filesystem::path> foundObjects;
	try {
		auto pathIterator = std::filesystem::directory_iterator(path);
		for (const auto& entry :
			std::filesystem::directory_iterator(path)) {
			auto newPath = entry.path();

			foundObjects.push_back(newPath);
		}
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	return foundObjects;
}

void ParallelFileRead::addFileReader(const char * path) {
	std::shared_ptr<std::vector<std::string>> specialWordsPointer = 
		std::make_shared<std::vector<std::string>>(specialWords);
	std::shared_ptr<FileReader> newFileReader = 
		std::make_shared<FileReader>(path, specialWordsPointer);
	fileReaders.push_back(newFileReader);
}

void ParallelFileRead::readFiles() {
	std::vector<std::thread> threads;
	for (auto& fileReaderPointer : fileReaders) {
		std::thread newThread(&FileReader::readFile,fileReaderPointer.get());
		threads.push_back(std::move(newThread));
	}

	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void ParallelFileRead::findAllFiles(const char* path) {
	std::vector<std::filesystem::path> filePaths = findReadableFiles(path);

	for (const auto& entry : filePaths) {

		if (entry.extension().string() == "") {

			 findAllFiles(entry.string().c_str());
		} else if (entry.extension().string() == REQUIRED_FORMAT) {

			 addFileReader(entry.string().c_str());
		}
	}
}

size_t ParallelFileRead::getFileCount() const {
	return fileReaders.size();
}

std::string ParallelFileRead::getFileCalculations() {
	std::string output = "";
	for (auto& fileReaderPointer : fileReaders) {
		output += "-------------------------\n";
		output += fileReaderPointer.get()->getCalculations();
		output += "-------------------------\n";
	}

	return output;
}

void ParallelFileRead::toLowerCase(std::vector<std::string>& words) {
	for (std::string& word : words) {
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}
