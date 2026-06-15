#include "search_engine.h"
#include <iostream>
#include <string_view>
#include <algorithm>
#include <mutex>
#include <cctype>

std::mutex print_mutex;

SearchEngine::SearchEngine() {}
SearchEngine::~SearchEngine() {}

bool SearchEngine::compile(const std::string& pattern) {
    if (pattern.empty()) return false;
    search_pattern = pattern;
    return true;
}

void SearchEngine::search(const void* data, size_t length, const std::string& filePath) {
    if (search_pattern.empty() || !data || length == 0) return;

    std::string_view haystack(static_cast<const char*>(data), length);

    // CASE-INSENSITIVE ARAMA: toupper kullanarak her iki harfi de büyük yapýp karþýlaþtýrýr
    auto it = std::search(
        haystack.begin(), haystack.end(),
        search_pattern.begin(), search_pattern.end(),
        [](char ch1, char ch2) {
            return std::toupper(static_cast<unsigned char>(ch1)) ==
                std::toupper(static_cast<unsigned char>(ch2));
        }
    );

    if (it != haystack.end()) {
        size_t offset = std::distance(haystack.begin(), it);
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "[Z-Search] Bulundu: " << filePath << " (Offset: " << offset << ")\n";
    }
}