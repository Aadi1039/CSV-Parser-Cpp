#include "adi_cpp_parser.h"
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

/* ---------- Helpers ---------- */

static string trim(string s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

static string normalize(string s) {
    s = trim(s);
    for (char& c : s) c = tolower(c);
    return s;
}

static vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string cur;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') inQuotes = !inQuotes;
        else if (c == ',' && !inQuotes) {
            fields.push_back(trim(cur));
            cur.clear();
        } else cur.push_back(c);
    }
    fields.push_back(trim(cur));
    return fields;
}

/* ---------- CSVTable ---------- */

CSVTable::CSVTable(const string& file) {
    ifstream in(file);
    if (!in) throw runtime_error("Cannot open file");

    string line;
    getline(in, line);
    headers = parseCSVLine(line);

    for (size_t i = 0; i < headers.size(); i++)
        headerIndex[normalize(headers[i])] = i;

    while (getline(in, line))
        rows.push_back(parseCSVLine(line));
}

bool CSVTable::hasColumn(const string& col) const {
    return headerIndex.find(normalize(col)) != headerIndex.end();
}

void CSVTable::printColumns() const {
    cout << "Available columns: ";
    for (auto& h : headers) cout << h << " ";
    cout << "\n";
}

ColumnView CSVTable::operator[](const string& col) {
    string key = normalize(col);
    if (!hasColumn(col)) {
        printColumns();
        throw runtime_error("Invalid column: " + col);
    }
    return ColumnView(*this, headerIndex.at(key));
}

void CSVTable::sort(const string& col, bool ascending) {
    size_t idx = headerIndex.at(normalize(col));

    std::sort(rows.begin(), rows.end(),
         [&](const auto& a, const auto& b) {
             return ascending ? stod(a[idx]) < stod(b[idx])
                              : stod(a[idx]) > stod(b[idx]);
         });
}

void CSVTable::addColumn(const string& name,
                         const vector<double>& data) {
    headers.push_back(name);
    headerIndex[normalize(name)] = headers.size() - 1;

    for (size_t i = 0; i < rows.size(); i++)
        rows[i].push_back(to_string(data[i]));
}

void CSVTable::print(size_t n) const {
    for (auto& h : headers) cout << h << "\t";
    cout << "\n";

    for (size_t i = 0; i < min(n, rows.size()); i++) {
        for (auto& v : rows[i]) cout << v << "\t";
        cout << "\n";
    }
}

void CSVTable::write(const string& file) const {
    ofstream out(file);
    for (size_t i = 0; i < headers.size(); i++) {
        out << headers[i];
        if (i + 1 < headers.size()) out << ",";
    }
    out << "\n";

    for (auto& r : rows) {
        for (size_t i = 0; i < r.size(); i++) {
            out << r[i];
            if (i + 1 < r.size()) out << ",";
        }
        out << "\n";
    }
}

/* ---------- ColumnView ---------- */

ColumnView::ColumnView(CSVTable& t, size_t idx)
    : table(t), colIndex(idx) {}

void ColumnView::sort(const string& dir) const {
    table.sort(table.headers[colIndex], dir != "descending");
}

vector<double> ColumnView::values() const {
    vector<double> v;
    for (auto& r : table.rows)
        v.push_back(stod(r[colIndex]));
    return v;
}

/* ---------- Operators ---------- */

vector<double> operator-(const ColumnView& a,
                          const ColumnView& b) {
    auto va = a.values();
    auto vb = b.values();
    vector<double> res;

    for (size_t i = 0; i < va.size(); i++)
        res.push_back(va[i] - vb[i]);

    return res;
}
