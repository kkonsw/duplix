// Copyright 2021 Kuznetsov Konstantin

/**
 * @file utilities.h
 * This file contains utility functions.
 */

#ifndef SRC_DUPLIX_UTILITIES_H_
#define SRC_DUPLIX_UTILITIES_H_

#include <iostream>
#include <string>

namespace duplix {

/** This function prints nice help message for users.
  *
  */
inline void print_help_message() {
    std::string help_msg =
        "duplix - CLI tool to find duplicate files in directories\n"
        "Usage: ./duplix first_dir second_dir";
    std::cout << help_msg << std::endl;
}

};  // namespace duplix

#endif  // SRC_DUPLIX_UTILITIES_H_
