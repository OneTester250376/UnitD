#include <iostream>
#include <string>
#include <toml++/toml.hpp>
#include <security/pam_appl.h>

#define UNITD_VERSION "0.1.0"
#define UNITD_BRANCH "unstable"
#define UNIT_DIR "/etc/units/"
#define UNIT_FILENAME "unit.toml"

int unit_parse(const std::string& filename)
{
    try
    {
        toml::table tbl = toml::parse_file(filename);
        // Перевірка наявності розділу "Unit" у таблиці
        if (tbl.contains("Unit"))
        {
            const toml::table& unit_section = tbl["Unit"].as_table();
            UnitData unit_data;
            // Зчитування даних з розділу "Unit"
            unit_data.name = unit_section["Name"].value_or("");
            unit_data.auto_start = unit_section["AutoStart"].value_or(false);
            // Інші поля, якщо вони є
            // Потім можна використовувати ці дані для подальшої обробки
            // Наприклад, вивід на екран або подальша логіка програми
            std::cout << "Unit Name: " << unit_data.name << "\n";
            std::cout << "Auto Start: " << (unit_data.auto_start ? "Yes" : "No") << "\n";
        }
        else
        {
            std::cerr << "Unit section not found in the TOML file.\n";
            return 1;
        }
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "Error parsing file " << filename << ":\n" << err << "\n";
        return 1;
    }

    return 0;
}
void version() {
    std::cout << "UnitD version " << UNITD_VERSION << " and branch " << UNITD_BRANCH;
}
