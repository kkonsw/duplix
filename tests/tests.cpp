// Copyright 2021 Kuznetsov Konstantin

#include <vector>
#include <string>

#include <catch2/catch.hpp>

#include "duplix/duplicate_file_finder.h"

TEST_CASE("Finding duplicates among incorrect directories throws",
        "[Duplicates]") {
    std::vector<std::string> directories;
    directories.emplace_back("123");
    directories.emplace_back("456");
    REQUIRE_THROWS(duplix::find_duplicate_files(directories));
}
