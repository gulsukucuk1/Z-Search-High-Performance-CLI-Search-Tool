#include "io_manager.h"

IOManager::MappedFile IOManager::mapFile(const std::string& filePath) {
    MappedFile mf;
    mf.fileHandle = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (mf.fileHandle == INVALID_HANDLE_VALUE) return mf;

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(mf.fileHandle, &fileSize)) {
        CloseHandle(mf.fileHandle);
        return mf;
    }
    mf.size = static_cast<size_t>(fileSize.QuadPart);

    if (mf.size == 0) {
        CloseHandle(mf.fileHandle);
        return mf;
    }

    mf.mappingHandle = CreateFileMappingA(mf.fileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (mf.mappingHandle == NULL) {
        CloseHandle(mf.fileHandle);
        return mf;
    }

    mf.data = MapViewOfFile(mf.mappingHandle, FILE_MAP_READ, 0, 0, 0);
    return mf;
}

void IOManager::unmapFile(MappedFile& mf) {
    if (mf.data) UnmapViewOfFile(mf.data);
    if (mf.mappingHandle) CloseHandle(mf.mappingHandle);
    if (mf.fileHandle != INVALID_HANDLE_VALUE) CloseHandle(mf.fileHandle);
}