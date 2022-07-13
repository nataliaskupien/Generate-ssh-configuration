#include <iostream>
#include <string>
#include "include/config.h"
#include "include/save_file.h"

int main(int argc, char* argv[])
{
    std::unique_ptr<Config> config = std::make_unique<Config>();

    try
    {
        config->init_arguments(argc,argv);
        
        if(config->is_json())
        {
            std::string output_name = config->get_output_name();

            config->create_data(config->parse(config->input_name));

            std::string save_data = config->create_config();

            std::unique_ptr<File> file = std::make_unique<File>(save_data,output_name);

            file->save_to_file();
        }
    }
    catch(std::invalid_argument &e)
    {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}
