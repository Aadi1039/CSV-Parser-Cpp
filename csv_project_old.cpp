#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

const size_t CHUNK_SIZE = 100000;

vector<string> parseCSVLine(const string &line) {
    vector<string> fields;
    string current;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields.push_back(current);
            current.clear();
        } else {
            current.push_back(c);
        }
    }
    fields.push_back(current);
    return fields;
}

void sortChunk(vector<string> &lines, size_t col) {
    sort(lines.begin(), lines.end(),
         [&](const string &a, const string &b) {
             auto fa = parseCSVLine(a);
             auto fb = parseCSVLine(b);
             return fa[col] < fb[col];
         });
}

void readWriteSortCSV(const string &inputFile,
                      const string &outputFile,
                      size_t sortColumn) {

    ifstream in(inputFile);
    if (!in.is_open()) {
        cout << "Cannot open input file\n";
        return;
    }

    string header;
    getline(in, header);

    vector<string> chunk;
    vector<string> tempFiles;
    string line;
    int index = 0;

    while (getline(in, line)) {
        chunk.push_back(line);

        if (chunk.size() == CHUNK_SIZE) {
            sortChunk(chunk, sortColumn);
            string fname = "chunk_" + to_string(index++) + ".csv";
            ofstream out(fname);
            for (auto &l : chunk) out << l << '\n';
            out.close();
            tempFiles.push_back(fname);
            chunk.clear();
        }
    }

    if (!chunk.empty()) {
        sortChunk(chunk, sortColumn);
        string fname = "chunk_" + to_string(index++) + ".csv";
        ofstream out(fname);
        for (auto &l : chunk) out << l << '\n';
        out.close();
        tempFiles.push_back(fname);
    }

    in.close();

    ofstream finalOut(outputFile);
    finalOut << header << '\n';

    vector<ifstream> files(tempFiles.size());
    vector<string> current(tempFiles.size());
    vector<bool> finished(tempFiles.size(), false);

    for (size_t i = 0; i < tempFiles.size(); i++) {
        files[i].open(tempFiles[i]);
        if (!getline(files[i], current[i]))
            finished[i] = true;
    }

    while (true) {
        int minIndex = -1;
        vector<string> minFields;

        for (size_t i = 0; i < current.size(); i++) {
            if (finished[i]) continue;
            auto fields = parseCSVLine(current[i]);
            if (minIndex == -1 || fields[sortColumn] < minFields[sortColumn]) {
                minIndex = i;
                minFields = fields;
            }
        }

        if (minIndex == -1) break;

        finalOut << current[minIndex] << '\n';

        if (!getline(files[minIndex], current[minIndex]))
            finished[minIndex] = true;
    }

    for (auto &f : files) f.close();
    finalOut.close();

    for (auto &f : tempFiles) remove(f.c_str());

    cout << "CSV read, written & temporary files deleted successfully: "
         << outputFile << endl;
}

void showMenu() {
    cout << "\n===== CSV PARSER MENU =====\n";
    cout << "1. Read CSV & Write Sorted CSV\n";
    cout << "2. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            string inputFile, outputFile;
            size_t column;

            cout << "Enter input CSV file name: ";
            cin >> inputFile;

            cout << "Enter output CSV file name: ";
            cin >> outputFile;

            cout << "Enter column index (0-based): ";
            cin >> column;

            readWriteSortCSV(inputFile, outputFile, column);
        }
        else if (choice == 2) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }
    return 0;
}
