# 📊 CSV Parser in C++

A menu-driven CSV parser written in C++ that efficiently reads, writes, and sorts large CSV files (100MB+) using external sorting.

---

## ✨ Features
- 📂 Read large CSV files safely
- ✍️ Write sorted output to a new CSV file
- 🔢 Sort by any column (0-based index)
- 🧹 Automatic deletion of temporary chunk files
- ⚡ Memory-efficient external sorting
- 🖥️ Menu-driven CLI interface
- 🍎 Compatible with macOS and VS Code

---

## 🛠️ Prerequisites
- C++ compiler (`g++`)
- macOS / Linux
- VS Code (recommended)

---

## ⚙️ Compile
```bash
g++ -std=c++17 csv_parser.cpp -o csv_parser
```

## ▶️ Example Usage
 CSV Parser Menu 
1. Read CSV & Write Sorted CSV
2. Exit

- Enter choice: 1
- Enter input CSV file name: data.csv
- Enter output CSV file name: sorted.csv
- Enter column index (0-based): 1


## 📁 Output
- ✅ Sorted CSV file is created (e.g., `sorted.csv`)
- 🧹 Temporary chunk files are deleted automatically
- 📄 Output can be opened directly in VS Code

## 🚀 Project Highlight
Developed a memory-efficient CSV parser in C++ capable of reading, writing, and sorting large CSV files (100MB+) using external sorting techniques.
