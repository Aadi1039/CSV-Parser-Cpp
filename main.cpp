#include "adi_cpp_parser.h"
#include <iostream>
using namespace std;

int main() {
    string inputFile, outputFile;
    size_t column;

    cout << "Enter input CSV file name: ";
    cin >> inputFile;

    cout << "Enter column index (0-based): ";
    cin >> column;

    cout << "Enter output CSV file name: ";
    cin >> outputFile;

    adi_cpp_parser parser(inputFile);
    parser.sort(column);
    parser.write(outputFile);

    cout << "Sorting completed successfully\n";
    return 0;
}
