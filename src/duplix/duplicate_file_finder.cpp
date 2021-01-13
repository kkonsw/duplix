// Copyright 2021 Kuznetsov Konstantin

#include <openssl/md5.h>

#include <iomanip>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

#include "duplix/duplicate_file_finder.h"

namespace duplix {

namespace fs = std::filesystem;

Duplicates DuplicateFileFinder::find_duplicate_files(
        const std::vector<std::string>& directories) {
    // check for valid directories
    for (const auto& dir : directories) {
        fs::path directory(dir);
        if (!fs::is_directory(directory)) {
            throw std::runtime_error("Invalid directory!");
        }
    }

    // get all regular files for each directory
    DirFiles dir_files;
    for (const auto& dir : directories) {
        dir_files.emplace(dir, DuplicateFileFinder::get_dir_files(dir));
    }

    // calculate file hashes
    HashedFiles hashed_files;
    for (const auto& files : dir_files) {
        for (const auto& file : files.second) {
            std::string hash = get_md5_file_hash(file);
            hashed_files.emplace(hash, file);
        }
    }

    // find duplicates
    Duplicates duplicates;
    auto it = hashed_files.begin();
    while (it != hashed_files.end()) {
        auto range = hashed_files.equal_range(it->first);
        if (std::distance(range.first, range.second) > 1) {
            Files identical_files;
            for (auto hash_it = range.first; hash_it != range.second;
                    ++hash_it) {
                identical_files.emplace_back(hash_it->second);
            }
            duplicates.emplace(it->first, identical_files);
        }
        it = range.second;
    }

    return duplicates;
}

Files DuplicateFileFinder::get_dir_files(const std::string& directory) {
    Files files;
    for (const auto& file_path : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(file_path)) {
            // do not include empty files
            if (fs::file_size(file_path) != 0) {
                files.emplace_back(file_path.path());
            }
        }
    }
    return files;
}

std::string DuplicateFileFinder::get_md5_file_hash(
        const std::string& file_path) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    std::ifstream ifs(file_path, std::ios::binary);
    char file_buffer[4096];
    while (ifs.read(file_buffer, sizeof(file_buffer)) || ifs.gcount()) {
        MD5_Update(&ctx, file_buffer, ifs.gcount());
    }
    unsigned char digest[MD5_DIGEST_LENGTH] = {};
    MD5_Final(digest, &ctx);

    // hex to string
    std::ostringstream hash;
    hash << std::hex << std::setfill('0');
    for (auto c : digest) {
        hash << std::setw(2) << static_cast<int>(c);
    }

    return hash.str();
}

};  // namespace duplix
