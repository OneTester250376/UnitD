#include "libs.hpp"
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

void 
RunUnits()
{
    std::vector<std::string> directories;

    for (const auto& entry : fs::directory_iterator(UNIT_DIR)) {
       if (entry.is_directory()) {
            directories.push_back(entry.path().filename());
       }
    }

    if (directories.empty()) {
        std::cout << "No directories with unit.toml files found in " << UNIT_DIR << std::endl;
        return; 
    }

    for (const auto& directory : directories) {
        if (!unit_parse((fs::path(UNIT_DIR) / directory / UNIT_FILENAME).string()))
        {
            exit(1);
        }
    }
}

