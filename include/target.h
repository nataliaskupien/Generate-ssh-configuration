#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

class Target
{
public:

    std::string target_name;
    std::vector<std::string> target_parameters;
    std::string command;

    Target() = default;
    friend std::ostream& operator<<(std::ostream &out, const Target &target);
};
#endif