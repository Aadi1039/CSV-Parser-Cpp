# CSV Parser in C++

This is a memory-efficient CSV sorting tool written in C++.  
It can sort very large CSV files using an external merge sort algorithm.

---

## Features
- Works with large CSV files (100MB+)
- Correct external merge sort (no data loss)
- Automatically detects numeric and string columns
- Simple user input based interface

---

## How to Build

```bash
g++ -std=c++17 main.cpp adi_cpp_parser.cpp -o csv_sorter
```
## How to Run
```bash
./csv_sorter
```
## Usage
After running, the program will ask:
```bash
Enter input CSV file name:
Enter column index (0-based):
Enter output CSV file name:
```
## Example:
crime.csv
2
sorted.csv

## Project Structure
- adi_cpp_parser.h      -> CSV parser library
- adi_cpp_parser.cpp    -> Implementation
- main.cpp              -> Program entry point
- csv_project_old.cpp   -> Old deprecated implementation

## Note

csv_project_old.cpp is kept only for reference.
The new implementation fixes merge and sorting bugs.

