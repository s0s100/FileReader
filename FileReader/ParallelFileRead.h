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
	void readFile(const char* path);

public:
	ParallelFileRead(std::vector<std::string> specialWords);
	~ParallelFileRead(void);
	size_t getFileCount() const;
	void readFolderFiles(const char* path);
	std::string getFileCalculations();
};

