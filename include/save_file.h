#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <string>
#include <iostream>
#include <fstream>

class File
{
private:
    std::string data;
    std::string file_name;

public:
    File(std::string data, std::string file_name);

    void save_to_file();

    void set_data(std::string data);

    std::string get_data();

    void set_file_name(std::string file_name);

    std::string get_file_name();
};
#endif