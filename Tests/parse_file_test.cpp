#include <gtest/gtest.h>
#include "include/config.h"

TEST(parse_target_arguments, check_if_vector_of_targets_is_correct)
{
    Config config;
    
    std::string json_file = " { \"targets\": {\"R5\": [\"HostName 192.168.56.102\",\"User Natalia\",\"IdentityFile C:\\\\Users\\\\d.kowalski\\\\.ssh\\\\private.ppk\"]},\
    \"gateways\": {\"Gateway1\": [\"param1\",\"param2\", \"param3\"]},\
    \"links\": {\"Gateway1\": [\"R5\"]},\
    \"linkCommand\": \"ProxyCommand ssh -W %h:%p <gateway>\"}";

    json j = json::parse(json_file);

    config.create_data(j);

    EXPECT_EQ(config.targets_array.size(), 1);
}

TEST(parse_target_arguments, check_if_all_parameters_of_taget_are_taken)
{
    Config config;
    
    std::string json_file = " { \"targets\": {\"R5\": [\"HostName 192.168.56.102\",\"User Natalia\",\"IdentityFile C:\\\\Users\\\\d.kowalski\\\\.ssh\\\\private.ppk\"]},\
    \"gateways\": {\"Gateway1\": [\"param1\",\"param2\", \"param3\"]},\
    \"links\": {\"Gateway1\": [\"R5\"]},\
    \"linkCommand\": \"ProxyCommand ssh -W %h:%p <gateway>\"}";

    json j = json::parse(json_file);

    config.create_data(j);

    EXPECT_EQ(config.targets_array[0].target_parameters.size(), 3);
}

TEST(parse_linkCommand_argument, check_if_command_contains_right_gateway)
{
    Config config;
    
    std::string json_file = " { \"targets\": {\"R5\": [\"HostName 192.168.56.102\",\"User Natalia\",\"IdentityFile C:\\\\Users\\\\d.kowalski\\\\.ssh\\\\private.ppk\"]},\
    \"gateways\": {\"Gateway1\": [\"param1\",\"param2\", \"param3\"]},\
    \"links\": {\"Gateway1\": [\"R5\"]},\
    \"linkCommand\": \"ProxyCommand ssh -W %h:%p <gateway>\"}";

    json j = json::parse(json_file);

    config.create_data(j);

    EXPECT_EQ(config.gateway_array[0].gateway_target[0].command,"ProxyCommand ssh -W %h:%p Gateway1" );
}

TEST(parse_gateway_arguments, check_if_vector_of_gateways_is_correct)
{
    Config config;
    
    std::string json_file = " { \"targets\": {\"R5\": [\"HostName 192.168.56.102\",\"User Natalia\",\"IdentityFile C:\\\\Users\\\\d.kowalski\\\\.ssh\\\\private.ppk\"]},\
    \"gateways\": {\"Gateway1\": [\"param1\",\"param2\", \"param3\"]},\
    \"links\": {\"Gateway1\": [\"R5\"]},\
    \"linkCommand\": \"ProxyCommand ssh -W %h:%p <gateway>\"}";

    json j = json::parse(json_file);

    config.create_data(j);

    EXPECT_EQ(config.gateway_array.size(), 1);
}

TEST(parse_gateway_arguments, check_if_all_parameters_of_gateway_are_taken)
{
    Config config;
    
    std::string json_file = " { \"targets\": {\"R5\": [\"HostName 192.168.56.102\",\"User Natalia\",\"IdentityFile C:\\\\Users\\\\d.kowalski\\\\.ssh\\\\private.ppk\"]},\
    \"gateways\": {\"Gateway1\": [\"param1\",\"param2\", \"param3\"]},\
    \"links\": {\"Gateway1\": [\"R5\"]},\
    \"linkCommand\": \"ProxyCommand ssh -W %h:%p <gateway>\"}";

    json j = json::parse(json_file);

    config.create_data(j);

    EXPECT_EQ(config.gateway_array[0].gateway_parameters.size(), 3);
}

TEST(parse_gateway_arguments, check_if_target_is_assigned_to_the_right_gateway)
{
    Config config;
    
    std::string json_file = " { \"targets\": {\"R5\": [\"HostName 192.168.56.102\",\"User Natalia\",\"IdentityFile C:\\\\Users\\\\d.kowalski\\\\.ssh\\\\private.ppk\"]},\
    \"gateways\": {\"Gateway1\": [\"param1\",\"param2\", \"param3\"]},\
    \"links\": {\"Gateway1\": [\"R5\"]},\
    \"linkCommand\": \"ProxyCommand ssh -W %h:%p <gateway>\"}";

    json j = json::parse(json_file);

    config.create_data(j);

    EXPECT_EQ(config.gateway_array[0].gateway_target[0].target_name, "R5");
}