#include "adi_cpp_parser.h"
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

static const size_t CHUNK_SIZE = 100000;

static vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string cur;
    bool inQuotes = false;
    for (char c : line) {
        if (c == '"') inQuotes = !inQuotes;
        else if (c == ',' && !inQuotes) {
            fields.push_back(cur);
            cur.clear();
        } else cur.push_back(c);
    }
    fields.push_back(cur);
    return fields;
}

static bool isNumber(const string& s) {
    if (s.empty()) return false;
    char* end = nullptr;
    strtod(s.c_str(), &end);
    return *end == '\0';
}

struct HeapNode {
    string line;
    vector<string> fields;
    size_t fileIndex;
};

struct Comparator {
    size_t col;
    bool numeric;
    bool operator()(const HeapNode& a, const HeapNode& b) const {
        if (numeric)
            return stod(a.fields[col]) > stod(b.fields[col]);
        return a.fields[col] > b.fields[col];
    }
};

adi_cpp_parser::adi_cpp_parser(const string& file)
    : inputFile(file), sortColumn(0) {}

void adi_cpp_parser::sort(size_t column) {
    sortColumn = column;
}

void adi_cpp_parser::write(const string& outFile) {
    ifstream in(inputFile);
    string header;
    getline(in, header);

    vector<string> chunk;
    vector<string> tempFiles;
    string line;
    int idx = 0;
    bool numeric = true;

    while (getline(in, line)) {
        auto f = parseCSVLine(line);
        if (sortColumn >= f.size()) continue;
        if (!isNumber(f[sortColumn])) numeric = false;
        chunk.push_back(line);

        if (chunk.size() == CHUNK_SIZE) {
            vector<HeapNode> rows;
            for (auto& l : chunk)
                rows.push_back({l, parseCSVLine(l), 0});
            std::sort(rows.begin(), rows.end(), [&](auto& a, auto& b) {
                if (numeric)
                    return stod(a.fields[sortColumn]) < stod(b.fields[sortColumn]);
                return a.fields[sortColumn] < b.fields[sortColumn];
            });
            string name = "chunk_" + to_string(idx++) + ".csv";
            ofstream out(name);
            for (auto& r : rows) out << r.line << '\n';
            tempFiles.push_back(name);
            chunk.clear();
        }
    }

    if (!chunk.empty()) {
        vector<HeapNode> rows;
        for (auto& l : chunk)
            rows.push_back({l, parseCSVLine(l), 0});
        std::sort(rows.begin(), rows.end(), [&](auto& a, auto& b) {
            if (numeric)
                return stod(a.fields[sortColumn]) < stod(b.fields[sortColumn]);
            return a.fields[sortColumn] < b.fields[sortColumn];
        });
        string name = "chunk_" + to_string(idx++) + ".csv";
        ofstream out(name);
        for (auto& r : rows) out << r.line << '\n';
        tempFiles.push_back(name);
    }

    in.close();

    vector<ifstream> files(tempFiles.size());
    priority_queue<HeapNode, vector<HeapNode>, Comparator>
        pq(Comparator{sortColumn, numeric});

    for (size_t i = 0; i < tempFiles.size(); i++) {
        files[i].open(tempFiles[i]);
        if (getline(files[i], line)) {
            pq.push({line, parseCSVLine(line), i});
        }
    }

    ofstream out(outFile);
    out << header << '\n';

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        out << top.line << '\n';

        if (getline(files[top.fileIndex], line)) {
            pq.push({line, parseCSVLine(line), top.fileIndex});
        }
    }

    out.close();
    for (auto& f : files) f.close();
    for (auto& f : tempFiles) remove(f.c_str());
}
