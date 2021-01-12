// Copyright 2021 Kuznetsov Konstantin

/**
 * @file duplicate_file_finder.h
 * This file contains class DuplicateFileFinder with functionality
 * to find duplicate files in directories.
 */

#ifndef SRC_DUPLIX_DUPLICATE_FILE_FINDER_H_
#define SRC_DUPLIX_DUPLICATE_FILE_FINDER_H_

#include <map>
#include <vector>
#include <string>

namespace duplix {

/** Structure to store file sizes with filenames.
  *
  */
using Files = std::multimap<std::uintmax_t, std::string>;

/** Structure to store directory names
  * and all files inside directories.
  */
using DirFiles = std::multimap<std::string, Files>;


class DuplicateFileFinder {
 public:
 private:
};

/** This function finds duplicate files among all directories.
  * \param directories Directories to search for duplicate files.
  * \returns Names of identical files among input directories.
  */
std::vector<std::string> find_duplicate_files(
        const std::vector<std::string>& directories);

};  // namespace duplix

#endif  // SRC_DUPLIX_DUPLICATE_FILE_FINDER_H_
