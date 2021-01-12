// Copyright 2021 Kuznetsov Konstantin

/**
 * @file duplicates.h
 * This file contains functions to
 * find duplicate files in directories.
 */

#ifndef SRC_DUPLIX_DUPLICATES_H_
#define SRC_DUPLIX_DUPLICATES_H_

#include <vector>
#include <string>

namespace duplix {

/** This function finds duplicate files among all directories.
  * \param directories Directories to search for duplicate files.
  * \returns Names of identical files among input directories.
  */
std::vector<std::string> find_duplicate_files(
        const std::vector<std::string>& directories);

};  // namespace duplix

#endif  // SRC_DUPLIX_DUPLICATES_H_
