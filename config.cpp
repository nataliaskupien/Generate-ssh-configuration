#include "config.h"

Config::Config(){}

 void Config::init_arguments(int argc, char* argv[])
 {
     for(int i = 1; i < argc; i++)
     {
        this->init_array.push_back(argv[i]);
     }
     for(auto i = init_array.begin(); i != init_array.end(); ++i )
     {
         if(*i == "-input")
         {
             i++;

             this->input_name = *i;
         }
         if(*i == "-output")
         {
             i++;

             this->output_name = *i;
         }
     }
 }

 std::string Config::get_input_name()
 {
     return this->input_name;
 }
 std::string Config::get_output_name()
 {
     return this->output_name;
 }

 std::vector <std::string> Config::get_arguments()
 {
     return this->init_array;
 }

 std::string Config::create_output(std::string input_name)
 {
    std::ifstream i(input_name);

    json j;

    i>>j;

    std::string target_name;
    std::string gateway_name;
    std::string links_name;
    std::string command_name;

    output_config += "Targets:\n";

    for(auto it = j["targets"].begin(); it != j["targets"].end(); ++it)
    {
        target_name = it.key();

        output_config += "\t" + target_name + ": ";

        for(const auto & item : j["targets"][target_name].items())
        {
            if(item.key() == "0")
            {
                target1.param1 = item.value().get<std::string>();
            }
            else if(item.key() == "1")
            {
                target1.param2 = item.value().get<std::string>();
            }
            else if(item.key() == "2")
            {
                target1.ip = item.value().get<std::string>();
            }
        }

        output_config += target1.param1 + "," + target1.param2 + "," + target1.ip + "\n" ;
    }

    output_config += "\nGateways:\n";

    for(auto it = j["gateways"].begin(); it != j["gateways"].end(); ++it)
    {
        gateway_name = it.key();

        output_config +=  "\t" + gateway_name + ": ";

        for(const auto & item : j["gateways"][gateway_name].items())
        {
            if(item.key() == "0")
            {
                gateway1.param1 = item.value().get<std::string>();
            }
            else if(item.key() == "1")
            {
                gateway1.param2 = item.value().get<std::string>();
            }
            else if(item.key() == "2")
            {
                gateway1.ip = item.value().get<std::string>();
            }
        }

        output_config += gateway1.param1 + "," + gateway1.param2 + "," + gateway1.ip + "\n";
    }
    
    output_config += "\nLinks:\n";

    for(auto it = j["links"].begin(); it != j["links"].end(); ++it)
    {
        links_name = it.key();

        output_config +=  "\t" + links_name + ": ";
    
        for(const auto & item : j["links"][links_name].items())
        {
            if(item.key() == "0")
            {
                link1.target1 = item.value().get<std::string>();
            }
            else if(item.key() == "1")
            {
                link1.target2 = item.value().get<std::string>();
            }
        }

        output_config += link1.target1 + "," + link1.target2 + "\n";
    }

    output_config += "\nLink command: ";
    
        for(const auto & item : j["linkCommand"].items())
        {
              this->link_command = item.value().get<std::string>();
        }

        output_config += this->link_command + "\n";

    return output_config;
 }
 
 bool Config::is_json() const
 {
     if(input_name.size() > 0)
    {
        return true;
    }

    return false;
 }

 bool Config::save_to_file() const
 {
     if(output_name.size() > 0)
    {
        return true;
    }

    return false;
 }