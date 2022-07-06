#ifndef LINKS_H
#define LINKS_H

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "gateway.h"

class Links
{
public:
    std::vector<Gateway>links_gateway;
    Links() = default;
};
#endif