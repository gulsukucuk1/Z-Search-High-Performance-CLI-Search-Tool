#pragma once
#include <string>
#include <functional>
#include <filesystem>

class Crawler {
public:
    using FileCallback = std::function<void(const std::string&)>;
    static void parallel_crawl(const std::string& path, FileCallback callback);
};