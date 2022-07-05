#include "include/save_file.h"

File::File(std::string data, std::string file_name) : data(data), file_name(file_name) {}

void File::save_to_file()
{
    std::ofstream file (this->file_name);

    file << this->data;
}

void File::set_data(std::string data)
{
    this->data = data;
}

std::string File::get_data()
{
    return this->data;
}

void File::set_file_name(std::string file_name)
{
    this->file_name = file_name;
}

std::string File::get_file_name()
{
    return this->file_name;
}