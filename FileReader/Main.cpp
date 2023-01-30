#include <iostream>
#include "ParallelFileRead.h"

// Reads arguments from the main function and created parallel file 
// reader to access files in the folder
int consoleRead(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    // Get path
    const char * folderPath = argv[1];
    
    // Get special words
    std::vector<std::string> specialWords;
    for (unsigned int i = 2; i < argc; i++) {
        specialWords.push_back(argv[i]);
    }

    ParallelFileRead parallelFileReader(specialWords);
    parallelFileReader.findAllFiles(folderPath);

    parallelFileReader.readFiles();

    std::cout << "Number of files found: " << parallelFileReader.getFileCount() << std::endl;
    std::cout << parallelFileReader.getFileCalculations() << std::endl;

    return 0;
}

// Testing application
int main(int argc, char** argv)
{
    consoleRead(argc, argv);
}
