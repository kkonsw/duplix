// Copyright 2021 Kuznetsov Konstantin

/**
 * @file utilities.h
 * This file contains utility functions.
 */

#ifndef SRC_DUPLIX_UTILITIES_H_
#define SRC_DUPLIX_UTILITIES_H_

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace duplix {

namespace fs = std::filesystem;

/** This function prints nice help message for users.
  *
  */
inline void print_help_message() {
    std::string help_msg =
        "duplix - CLI tool to find duplicate files in directories\n"
        "Usage: ./duplix first_dir second_dir";
    std::cout << help_msg << std::endl;
}

// TODO(duplix): move to separate header
inline void find_duplicate_files(const std::vector<std::string>& directories) {
    for (const auto& dir : directories) {
        fs::path directory(dir);
        if (!fs::is_directory(directory)) {
            throw std::runtime_error("Invalid directory!");
        }
    }
}

};  // namespace duplix

#endif  // SRC_DUPLIX_UTILITIES_H_
