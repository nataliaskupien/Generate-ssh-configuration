#include <gtest/gtest.h>
#include "include/config.h"
#include "include/save_file.h"

TEST(save_data, check_if_correct_data_is_saved_to_file)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json"};
    int argc = 3;

    config.init_arguments(argc, argv);
    config.create_data(config.parse(config.input_name));
    std::string save_data = config.create_config();
    std::string output_name = config.get_output_name();
    std::unique_ptr<File> file = std::make_unique<File>(save_data,output_name);
    
    EXPECT_EQ(save_data, file->get_data());
}

TEST(save_data, check_if_output_file_name_is_correct)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json","-output", "config.txt"};
    int argc = 3;

    config.init_arguments(argc, argv);
    config.create_data(config.parse(config.input_name));
    std::string save_data = config.create_config();
    std::string output_name = "config.txt";
    std::unique_ptr<File> file = std::make_unique<File>(save_data,output_name);
    
    EXPECT_EQ(output_name, file->get_file_name());
}

TEST(config_data, check_output_name_if_not_defined_by_user)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json"};
    int argc = 3;

    config.init_arguments(argc, argv);
    config.create_data(config.parse(config.input_name));
    std::string save_data = config.create_config();
    std::string output_name = config.get_output_name();
    std::unique_ptr<File> file = std::make_unique<File>(save_data,output_name);

    EXPECT_EQ(file->get_file_name(), "configuration.txt");
}