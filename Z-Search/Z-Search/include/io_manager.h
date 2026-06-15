#pragma once
#include <windows.h>
#include <string>

class IOManager {
public:
    struct MappedFile {
        void* data = nullptr;
        size_t size = 0;
        HANDLE fileHandle = INVALID_HANDLE_VALUE;
        HANDLE mappingHandle = NULL;
    };

    static MappedFile mapFile(const std::string& filePath);
    static void unmapFile(MappedFile& file);
};