#include "io_manager.h"
#include "crawler.h"
#include "search_engine.h"
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {
    // Türkçe karakter desteði
    setlocale(LC_ALL, "Turkish");

    if (argc < 3) {
        std::cout << "==================================================\n";
        std::cout << "          Z-SEARCH v2.0 (CASE-INSENSITIVE)        \n";
        std::cout << "==================================================\n";
        std::cout << "Kullanim: ZSearch.exe <Dizin> <Kelime>\n\n";
        return 1;
    }

    std::string searchDir = argv[1];
    std::string pattern = argv[2];

    SearchEngine engine;
    if (!engine.compile(pattern)) {
        std::cerr << "[-] Arama deseni hatali.\n";
        return 1;
    }

    std::cout << "[+] Z-Search Taraniyor: " << searchDir << " | Hedef: " << pattern << "\n\n";

    auto start_time = std::chrono::high_resolution_clock::now();

    Crawler::parallel_crawl(searchDir, [&](const std::string& filePath) {
        auto mappedFile = IOManager::mapFile(filePath);
        if (mappedFile.data) {
            engine.search(mappedFile.data, mappedFile.size, filePath);
            IOManager::unmapFile(mappedFile);
        }
        });

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "\n[+] Tarama Bitti! Toplam sure: " << duration << " ms.\n";

    return 0;
}