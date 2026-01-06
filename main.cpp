#include "adi_cpp_parser.h"
#include <iostream>

using namespace std;

int main() {
    try {
        string file;
        cout << "Enter CSV file name: ";
        cin >> file;

        CSVTable parser(file);

        int choice;
        do {
            cout << "\n---- MENU ----\n";
            cout << "1. Sort by column\n";
            cout << "2. Create derived column (subtraction)\n";
            cout << "3. Print first N rows\n";
            cout << "4. Write output CSV\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                string col, dir;
                cout << "Enter column name: ";
                cin >> col;
                cout << "Direction (ascending/descending): ";
                cin >> dir;

                if (!parser.hasColumn(col)) {
                    cout << "❌ Invalid column name\n";
                    parser.printColumns();
                    continue;
                }

                parser[col].sort(dir);
                cout << "✔ Sorted successfully\n";
            }

            else if (choice == 2) {
                string newCol, c1, c2;
                cout << "Enter new column name: ";
                cin >> newCol;
                cout << "Enter first column: ";
                cin >> c1;
                cout << "Enter second column: ";
                cin >> c2;

                if (!parser.hasColumn(c1) || !parser.hasColumn(c2)) {
                    cout << "❌ Invalid column name(s)\n";
                    parser.printColumns();
                    continue;
                }

                parser.addColumn(newCol, parser[c1] - parser[c2]);
                cout << "✔ Column added successfully\n";
            }

            else if (choice == 3) {
                int n;
                cout << "Enter number of rows to print: ";
                cin >> n;
                parser.print(n);
            }

            else if (choice == 4) {
                string outFile;
                cout << "Enter output CSV file name: ";
                cin >> outFile;
                parser.write(outFile);
                cout << "✔ Output file written successfully\n";
            }

        } while (choice != 0);

        cout << "Program exited.\n";
    }
    catch (const exception& e) {
        cout << "Fatal error: " << e.what() << endl;
    }

    return 0;
}
