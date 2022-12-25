/**
*   Part 1.
* Design, create and test a C++ console application. The application should:
* Read all files in a specified folder (assume they are ascii).
* For each file, ascertain:
*  - The longest word
*  - The shortest word
*  - The total word count
*  - The number of occurrences of one or more specified words.
* Produce a design, including a simple class diagram – use Powerpoint
* Explain how it was (or could be tested) – again use Powerpoint
* The implementation should demonstrate, as far as possible:
*  - Abstraction
*  - Inheritance
*  - Use of the C++ standard library, including smart pointers, and if possible lambdas.
*
*   Part 2.
* Extend the application to scan the subfolders from a specified location (and nested sub folders).
* Consideration should be given to:
*  - Performance
*  - Scalability
*  - Feedback and Instrumentation (logging of progress)
*
* Document any design and implementation decisions in your Presentation. Try to keep this artefact as simple and coherent as possible.
**/

#include <iostream>
#include "ParallelFileRead.h"

void printSymbols() {
    // 65 - 90 : A - Z
    // 97 -122 : a - z
    // 48 - 57 : 0 - 9

    unsigned char c;
    for (unsigned int i = 0; i <= 256; i++) {
        c = i;
        std::cout << i << ": " << c << "\n";
    }
}

// Testing application
int main()
{
    const char* folderPath = "Files";
    std::vector<std::string> specialWords = { "a", "test" };
    ParallelFileRead parallelFileReader(specialWords);
    parallelFileReader.readFolderFiles(folderPath);

    std::cout << "Number of files found: " << parallelFileReader.getFileCount() << std::endl;
    std::cout << parallelFileReader.getFileCalculations() << std::endl;
}
