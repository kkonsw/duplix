// Copyright 2021 Kuznetsov Konstantin

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

#include <catch2/catch.hpp>

#include "duplix/duplicate_file_finder.h"

namespace fs = std::filesystem;

class DuplicateFileFinderFixture {
 public:
     DuplicateFileFinderFixture() {
         // create test directory
         tmp_dir_path = fs::temp_directory_path() / "test_dir";
         fs::create_directories(tmp_dir_path);
         fs::current_path(tmp_dir_path);

         // create two directories for testing
         auto dir_a = tmp_dir_path / "a";
         auto dir_b = tmp_dir_path / "b";
         fs::create_directory(dir_a);
         fs::create_directory(dir_b);
         directories.emplace_back(dir_a);
         directories.emplace_back(dir_b);
     }

     ~DuplicateFileFinderFixture() {
         // remove test directory
         fs::remove_all(tmp_dir_path);
     }

 protected:
     fs::path tmp_dir_path;
     std::vector<std::string> directories;
};

TEST_CASE_METHOD(DuplicateFileFinderFixture,
        "Finding duplicates among incorrect directories throws",
        "[DuplicateFileFinder]") {
    directories.clear();
    directories.emplace_back("123");
    directories.emplace_back("456");

    REQUIRE_THROWS(duplix::DuplicateFileFinder::
            find_duplicate_files(directories));
}

TEST_CASE_METHOD(DuplicateFileFinderFixture,
        "Empty directories have no duplicates",
        "[DuplicateFileFinder]") {
    auto duplicates = duplix::DuplicateFileFinder::
        find_duplicate_files(directories);

    REQUIRE(duplicates.size() == 0);
}

TEST_CASE_METHOD(DuplicateFileFinderFixture,
        "Empty files are not duplicates",
        "[DuplicateFileFinder]") {
    // create regular empty files
    std::ofstream("a/file1");
    std::ofstream("b/file2");
    auto duplicates = duplix::DuplicateFileFinder::
        find_duplicate_files(directories);

    REQUIRE(duplicates.size() == 0);
}

TEST_CASE_METHOD(DuplicateFileFinderFixture,
        "Find duplicate files",
        "[DuplicateFileFinder]") {
    auto file1 = std::ofstream("a/file1");
    auto file2 = std::ofstream("b/file2");
    file1 << "test" << "\n";
    file2 << "test" << "\n";
    file1.flush();
    file2.flush();

    auto duplicates = duplix::DuplicateFileFinder::
        find_duplicate_files(directories);
    REQUIRE(duplicates.size() == 1);

    auto hash = duplicates.begin()->first;
    auto files = duplicates.begin()->second;

    REQUIRE(hash == "d8e8fca2dc0f896fd7cb4cb0031ba249");
    REQUIRE(files[0] == "/tmp/test_dir/a/file1");
    REQUIRE(files[1] == "/tmp/test_dir/b/file2");
}

TEST_CASE_METHOD(DuplicateFileFinderFixture,
        "Search single directory for duplicates",
        "[DuplicateFileFinder]") {
    auto file1 = std::ofstream("a/file1");
    auto file2 = std::ofstream("a/file2");
    file1 << "test" << "\n";
    file2 << "test" << "\n";
    file1.flush();
    file2.flush();

    directories.clear();
    directories.emplace_back(tmp_dir_path / "a");
    auto duplicates = duplix::DuplicateFileFinder::
        find_duplicate_files(directories);
    REQUIRE(duplicates.size() == 1);

    auto hash = duplicates.begin()->first;
    auto files = duplicates.begin()->second;

    REQUIRE(hash == "d8e8fca2dc0f896fd7cb4cb0031ba249");
    REQUIRE(files[0] == "/tmp/test_dir/a/file2");
    REQUIRE(files[1] == "/tmp/test_dir/a/file1");
}

TEST_CASE_METHOD(DuplicateFileFinderFixture,
        "Searching the same directory twice marks all files as duplicates",
        "[DuplicateFileFinder]") {
    auto file1 = std::ofstream("a/file1");
    file1 << "test" << "\n";
    file1.flush();

    directories.clear();
    directories.emplace_back(tmp_dir_path / "a");
    directories.emplace_back(tmp_dir_path / "a");
    auto duplicates = duplix::DuplicateFileFinder::
        find_duplicate_files(directories);
    REQUIRE(duplicates.size() == 1);

    auto hash = duplicates.begin()->first;
    auto files = duplicates.begin()->second;

    REQUIRE(hash == "d8e8fca2dc0f896fd7cb4cb0031ba249");
    REQUIRE(files[0] == "/tmp/test_dir/a/file1");
    REQUIRE(files[1] == "/tmp/test_dir/a/file1");
}
