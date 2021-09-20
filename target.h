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
    std::string param1;
    std::string param2;
    std::string ip;
    std::string command;
    std::string gateway;

    Target();
};
#endif