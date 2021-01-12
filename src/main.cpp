// Copyright 2021 Kuznetsov Konstantin

#include <iostream>
#include <vector>
#include <string>

#include "duplix/utilities.h"
#include "duplix/duplicates.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    if (args.size() != 2) {
        duplix::print_help_message();
        return -1;
    }

    try {
        duplix::find_duplicate_files(args);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
