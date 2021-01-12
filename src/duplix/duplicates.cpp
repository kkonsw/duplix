// Copyright 2021 Kuznetsov Konstantin

#include <filesystem>
#include <stdexcept>

#include "duplix/duplicates.h"

namespace duplix {

namespace fs = std::filesystem;

std::vector<std::string> find_duplicate_files(
        const std::vector<std::string>& directories) {
    for (const auto& dir : directories) {
        fs::path directory(dir);
        if (!fs::is_directory(directory)) {
            throw std::runtime_error("Invalid directory!");
        }
    }

    std::vector<std::string> duplicates;
    return duplicates;
}


};  // namespace duplix
