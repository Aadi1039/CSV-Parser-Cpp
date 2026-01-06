# CSV-Parser-Cpp

A **C++ in-memory CSV parser** that supports header-based operations, sorting, derived columns, and exporting results using an interactive command-line interface.

This project demonstrates clean C++ design, in-memory data processing, and practical use of STL, making it suitable for learning, experimentation, and portfolio showcase.

---

## 📌 Features

- Load and parse CSV files with headers
- Case-insensitive column name handling
- Sort data by column (ascending / descending)
- Create derived columns using arithmetic operations (e.g., High − Low)
- Print first N rows of processed data
- Write transformed data to a new CSV file
- Interactive, user-friendly menu
- In-memory processing for better performance

---

## 🛠️ Prerequisites

Make sure you have the following installed:

- C++ compiler (GCC / Clang / MSVC)
- Git
- VS Code or any C++ IDE (optional)

---

## ⚙️ Build Instructions

1. **Clone the repository**
```bash
git clone https://github.com/Aadi1039/CSV-Parser-Cpp.git
cd CSV-Parser-Cpp
```
## Compile the project

g++ -std=c++17 main.cpp adi_cpp_parser.cpp -o csv_parser

## ▶️ How to Run
```bash
./csv_parser
```

## 📋 Example Usage
- Sample Input CSV (QQQ.csv)

## Interactive Menu
```bash
1. Sort by column
2. Create derived column (subtraction)
3. Print first N rows
4. Write output CSV
0. Exit
```
## Example Flow

- Create a derived column:
```bash
Enter choice: 2
Enter new column name: day_range
Enter first column: High
Enter second column: Low
✔ Column added successfully
```

## Example Flow

- Create a derived column:
```bash
Enter choice: 2
Enter new column name: day_range
Enter first column: High
Enter second column: Low
✔ Column added successfully
```

## Print first 5 rows:
```bash

Date    High    Low     day_range
2024-01-05  420.8   410.4   10.400000
2024-01-04  415.2   405.9   9.300000
2024-01-02  410.0   400.1   9.900000
2024-01-03  408.3   402.5   5.800000
2024-01-01  405.5   398.2   7.300000
```

## 📁 Project Structure
```bash
CSV-Parser-Cpp/
├── adi_cpp_parser.h
├── adi_cpp_parser.cpp
├── main.cpp
├── QQQ.csv
└── README.md
```




