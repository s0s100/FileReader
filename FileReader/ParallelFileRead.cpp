#include <filesystem>
#include <iostream>
#include <thread>
#include <future>
#include "ParallelFileRead.h"

ParallelFileRead::ParallelFileRead(std::vector<std::string> specialWords) : specialWords(specialWords) {}

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

void ParallelFileRead::readFile(const char * path) {
	std::shared_ptr<std::vector<std::string>> specialWordsPointer = 
		std::make_shared<std::vector<std::string>>(specialWords);
	std::shared_ptr<FileReader> newFileReader = 
		std::make_shared<FileReader>(path, specialWordsPointer);

	newFileReader.get()->readFile();

	/*std::thread newThread(&FileReader::readFile, newFileReader.get());
	newThread.join();*/

	fileReaders.push_back(newFileReader);
}

void ParallelFileRead::readFolderFiles(const char* path) {
	std::vector<std::filesystem::path> filePaths = findReadableFiles(path);

	for (const auto& entry : filePaths) {
		std::cout << "Checking file: " << entry << std::endl;

		if (entry.extension().string() == "") {
			std::cout << "It is a folder" << std::endl;

			 readFolderFiles(entry.string().c_str());
		} else if (entry.extension().string() == REQUIRED_FORMAT) {
			std::cout << "It is a required format" << std::endl;

			 readFile(entry.string().c_str());
		}
		
		std::cout << std::endl;
	}
}

size_t ParallelFileRead::getFileCount() const {
	return fileReaders.size();
}

std::string ParallelFileRead::getFileCalculations() {
	std::string output = "";
	for (auto& fileReaderPointer : fileReaders) {
		output += fileReaderPointer.get()->getCalculations();
	}

	return output;
}