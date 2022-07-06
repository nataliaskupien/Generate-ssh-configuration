#ifndef GATEWAY_H
#define GATEWAY_H

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "target.h"

class Gateway
{
public:
    std::string gateway_name;
    std::vector<std::string> gateway_parameters;
    std::vector <Target> gateway_target;

    friend std::ostream& operator<<(std::ostream &out, const std::vector<Gateway> &gateway);
};
#endif