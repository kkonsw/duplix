// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <map>

#include "duplix/duplicate_file_finder.h"

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

    // get all regular file names and sizes for each directory
    DirFiles dir_files;
    for (const auto& dir : directories) {
        Files files;
        for (const auto& file_path : fs::recursive_directory_iterator(dir)) {
            if (fs::is_regular_file(file_path)) {
                files.emplace(fs::file_size(file_path), file_path.path());
            }
        }
        dir_files.emplace(dir, files);
    }

    // print all filenames with sizes
    for (const auto& files : dir_files) {
        std::cout << "Listing Directory " << files.first << ":" << std::endl;
        for (const auto& file : files.second) {
            std::cout << "\tFile " << file.second << " has size "
                << file.first << " bytes" << std::endl;
        }
    }

    std::vector<std::string> duplicates;
    return duplicates;
}

};  // namespace duplix
