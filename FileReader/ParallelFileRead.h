#pragma once

#include <vector>
#include <filesystem>
#include "FileReader.h"

class ParallelFileRead
{
private:
	const char* REQUIRED_FORMAT = ".txt";
	std::vector<std::string> specialWords;
	std::vector<std::shared_ptr<FileReader>> fileReaders;

	std::vector<std::filesystem::path> findReadableFiles(const char* path);
	void addFileReader(const char* path);

public:
	ParallelFileRead(std::vector<std::string> specialWords);
	~ParallelFileRead(void);
	// Get the number of the required files found
	size_t getFileCount() const;
	// Find all files of required format and fill file reader array
	void findAllFiles(const char* path);
	// Get reading result for each file found
	std::string getFileCalculations();
	// Read files and store the data in the file reader
	void readFiles();
	void toLowerCase(std::vector<std::string>& words);
};

