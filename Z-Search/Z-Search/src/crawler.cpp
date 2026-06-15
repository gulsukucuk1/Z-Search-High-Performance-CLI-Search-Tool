#include <filesystem>
#include <functional>
#include <execution>
#include <vector>
#include <mutex>
#include "crawler.h"

namespace fs = std::filesystem;
std::mutex vector_mutex;

void Crawler::parallel_crawl(const std::string& path, FileCallback callback) {
    std::vector<std::string> files_to_search;

    // Önce hýzlýca dosya listesini çýkartýyoruz (Thread-safe)
    try {
        if (!fs::exists(path)) return;
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            if (entry.is_regular_file()) {
                files_to_search.push_back(entry.path().string());
            }
        }
    }
    catch (...) {}

    // Ýþlemcinin tüm çekirdeklerini (std::execution::par) kullanarak arama motoruna daðýtýyoruz
    std::for_each(std::execution::par, files_to_search.begin(), files_to_search.end(), [&](const std::string& filePath) {
        callback(filePath);
        });
}