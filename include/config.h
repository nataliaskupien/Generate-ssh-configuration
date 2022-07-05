#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <fstream>
#include "target.h"
#include "gateway.h"
#include "links.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config
{
public:
    std::string input_name = "abc";
    std::string output_name;
    std::string output_config;
    std::string link_command;

    std::vector <std::string> init_array;
    std::vector <Links> links_array;
    std::vector <Target> targets_array;
    std::vector <Gateway> gateway_array;

    Config() = default;

    void init_arguments(int argc, char* argv[]);

    std::string get_input_name();

    std::string get_output_name();

    std::string get_link_command();

    std::vector <std::string> get_arguments();

    void create_data(std::string input_name);

    bool save_to_file() const;

    bool is_json() const;

    std::string create_config();

    friend std::ostream& operator<<(std::ostream &out, const std::vector<Gateway> &gateway);
    friend std::ostream& operator<<(std::ostream &out2, const std::vector<Target> &target);
};
#endif