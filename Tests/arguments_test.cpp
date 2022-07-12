#include <gtest/gtest.h>
#include "include/config.h"

TEST(config_data, check_if_output_data_is_created)
{
    Config config;
    char* argv[] = {"generate_ssh_config", "-input", "/home/natalia/Generate-ssh-configuration/config.json"};
    int argc = 3;

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