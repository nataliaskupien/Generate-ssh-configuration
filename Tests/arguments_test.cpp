#include <gtest/gtest.h>
#include "include/config.h"
#include "include/save_file.h"

TEST(config_data, check_if_input_file_is_json)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json", "-output", "config.txt"};
    int argc = 5;

    config.init_arguments(argc, argv);

    EXPECT_TRUE(config.is_json());
}

TEST(config_data, check_if_output_file_is_defined)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json", "-output", "config.txt"};
    int argc = 5;

    config.init_arguments(argc, argv);

    EXPECT_TRUE(config.if_output_defined());
}

TEST(config_data, check_if_input_arguments_are_processed)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json", "-output", "config.txt"};
    int argc = 5;

    config.init_arguments(argc, argv);

    std::vector<std::string> arguments = {"-input", "/home/natalia/Generate-ssh-configuration/config.json", "-output", "config.txt"};

    EXPECT_EQ(config.get_arguments(), arguments);
}