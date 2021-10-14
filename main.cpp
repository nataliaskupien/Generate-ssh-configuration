#include <iostream>
#include <string>
#include "config.h"
#include "save_file.h"

int main(int argc, char* argv[])
{
    Config config;

    File* file1;

    config.init_arguments(argc,argv);

    if(config.is_json() && config.save_to_file())
    {
        std::string output_name = config.get_output_name();

        config.create_data(config.get_input_name());

        std::string save_data = config.create_config();

        File file1(save_data, output_name);

        file1.save_to_file();
    }

    return 0;
}