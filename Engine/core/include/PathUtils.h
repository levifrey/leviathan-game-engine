#pragma once
#include <filesystem>
#include <unistd.h>
#include <limits.h>

namespace PathUtils {
    
inline std::filesystem::path projectDir;
inline std::filesystem::path executableDir;
inline std::filesystem::path assetDir;
inline std::filesystem::path shaderDir;
inline std::filesystem::path objectDir;
inline std::filesystem::path textureDir;

inline std::filesystem::path getExecutableDir() {
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) -1);
    if (len == -1) return {};
    buffer[len] = '\0';
    return std::filesystem::path(buffer).parent_path();
}
    
inline void init() {
    executableDir = getExecutableDir();
    projectDir = executableDir.parent_path();
    assetDir = projectDir / "Engine/resources";
    shaderDir = assetDir / "shaders";
    objectDir = assetDir / "objects";
    textureDir = assetDir / "textures";
}

}


