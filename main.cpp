#include <iostream>
#include <string>
#include "include/config.h"
#include "include/save_file.h"

int main(int argc, char* argv[])
{
    std::unique_ptr<Config> config = std::make_unique<Config>();

    config->init_arguments(argc,argv);

    if(config->is_json() && config->save_to_file())
    {
        std::string output_name = config->get_output_name();

        config->create_data();

        std::string save_data = config->create_config();

        std::unique_ptr<File> file = std::make_unique<File>(save_data,output_name);

        file->save_to_file();
    }
    else
    {
        std::cerr << "File is not json provided or output file name is incorrect" << std::endl;
        return 1;
    }

    return 0;
}
