#pragma once
#include <string>

class adi_cpp_parser {
public:
    explicit adi_cpp_parser(const std::string& file);
    void sort(size_t column);
    void write(const std::string& outFile);

private:
    std::string inputFile;
    size_t sortColumn;
};
