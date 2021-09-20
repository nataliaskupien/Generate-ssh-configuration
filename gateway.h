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
    std::string param1;
    std::string param2;
    std::string ip;

    std::vector <Target> gateway_target;

    Gateway();
};
#endif