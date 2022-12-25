#pragma once

#include <thread>
#include <mutex>
#include "File.h"

// Reads file and return a pointer to a new file
class FileReader : public File
{
private:
	const unsigned char SPACE_NUMBER = 32;
	const char* filePath;
	std::mutex mutex_;
	
public:
	FileReader(const char* filePath, std::shared_ptr<std::vector<std::string>> specialWords);
	~FileReader(void);
	bool isAvailable();
	void readFile();
	std::string getCalculations();
};