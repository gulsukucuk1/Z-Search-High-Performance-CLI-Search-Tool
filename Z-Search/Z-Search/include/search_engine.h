#pragma once
#include <string>
#include <string_view>

class SearchEngine {
private:
    std::string search_pattern;

public:
    SearchEngine();
    ~SearchEngine();

    bool compile(const std::string& pattern);
    void search(const void* data, size_t length, const std::string& filePath);
};