#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

class CSVTable;

class ColumnView {
    CSVTable& table;
    size_t colIndex;

public:
    ColumnView(CSVTable& t, size_t idx);

    void sort(const std::string& dir = "ascending") const;
    std::vector<double> values() const;
};

class CSVTable {
private:
    std::vector<std::string> headers;
    std::unordered_map<std::string, size_t> headerIndex;
    std::vector<std::vector<std::string>> rows;

public:
    explicit CSVTable(const std::string& file);

    bool hasColumn(const std::string& col) const;
    void printColumns() const;

    ColumnView operator[](const std::string& col);

    void sort(const std::string& col, bool ascending = true);
    void addColumn(const std::string& name,
                   const std::vector<double>& data);

    void print(size_t n = 10) const;
    void write(const std::string& file) const;

    friend class ColumnView;
};

std::vector<double> operator-(const ColumnView& a,
                              const ColumnView& b);
