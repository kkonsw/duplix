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

/** Structure to store file names.
  *
  */
using Files = std::vector<std::string>;

/** Structure to store directory names
  * with all files inside directories.
  */
using DirFiles = std::multimap<std::string, Files>;

class DuplicateFileFinder {
 public:
/** This function finds duplicate files among all directories.
  * \param directories Directories to search for duplicate files.
  * \returns Names of identical files among input directories.
  */
static std::vector<std::string> find_duplicate_files(
        const std::vector<std::string>& directories);

/** This function calculates md5 hash of a file using OpenSSL.
  * \param file_path Path to file.
  * \returns md5 hash as a string.
  */
static std::string get_md5_file_hash(const std::string& file_path);

/** This function iterates over all directory files, and,
  * recursively, over the files of all subdirectories.
  * \param directory Directory to search for files.
  * \returns All regular file names.
  */
static Files get_dir_files(const std::string& directory);
};

};  // namespace duplix

#endif  // SRC_DUPLIX_DUPLICATE_FILE_FINDER_H_
