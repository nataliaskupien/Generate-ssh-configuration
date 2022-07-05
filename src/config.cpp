#include "include/config.h"
#include <algorithm>

void Config::init_arguments(int argc, char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
    init_array.push_back(argv[i]);
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

void Config::create_data(std::string input_name)
{
    std::ifstream i(input_name);
    json j = json::parse(i);
    std::string val;

    //Tworzenie targetow

    for(auto it = j["targets"].begin(); it != j["targets"].end(); ++it)
    {
        Target target;
        target.target_name = it.key();

        for(const auto & item : j["targets"][target.target_name].items())
        {
            val = item.value().get<std::string>();

            if(val.find("IP") != std::string::npos)
            {
                target.ip = val;
            }
            else
            {
                target.target_parameters.push_back(val);
            }

            for(auto it = j["linkCommand"].begin(); it != j["linkCommand"].end(); ++it)
            {
                target.command = it.key();
            }
        }
        targets_array.push_back(target);
    }

//Tworzenie gateways i przypisanie targetow do danego gatewaya

    for(auto it = j["gateways"].begin(); it != j["gateways"].end(); ++it)
    {
        Gateway gateway;

        gateway.gateway_name = it.key();

        for(const auto & item : j["gateways"][gateway.gateway_name].items())
        {
            val = item.value().get<std::string>();
            gateway.gateway_parameters.push_back(val);
        }

        for(auto it = j["links"].begin(); it != j["links"].end(); ++it)
        {
            std::string link_name = it.key();
        
            if (link_name != gateway.gateway_name)
            {
                continue;
            }

            for(const auto & item : j["links"][gateway.gateway_name].items())
            {
                for (int i = 0; i < targets_array.size(); i++)
                {
                    if(item.value().get<std::string>() == targets_array[i].target_name)
                    {
                        gateway.gateway_target.push_back(targets_array[i]);
                    }
                }
            }
        }
    gateway_array.push_back(gateway);
    }

    for(auto it = j["links"].begin(); it != j["links"].end(); ++it)
    {
        Links link;
        std::string name = it.key();

        if(link.links_gateway.size() == 0)
        {
            link.links_gateway = gateway_array;
        }

        for (int i = 0; i < gateway_array.size(); i++)
        {
            if(name == gateway_array[i].gateway_name)
            {
                link.links_gateway[i] = gateway_array[i];
            }
        }
    links_array.push_back(link);
    }
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

std::string Config::get_link_command()
{
    return this->link_command;
}

std::string Config::create_config()
{
    std::string output_config;

    std::ostringstream ss;
    ss << gateway_array;
    output_config += ss.str();
    std::cout << output_config;

    for(int i = 0; i < links_array.size(); i++)
    {
        for(int j = 0; j < links_array[i].links_gateway[i].gateway_target.size(); j++)
        {
            auto current_link_gateway = links_array[i].links_gateway[i];
            auto current_link_target = current_link_gateway.gateway_target[j];
            auto target_name = current_link_target.target_name + "_" + current_link_gateway.gateway_name;
            output_config += "\n" + target_name;

            ss.str("");
            ss.clear();
            ss << gateway_array[j].gateway_target;
            output_config += ss.str();
        }
    }
    return output_config;
}

std::ostream& operator<<(std::ostream &out, const std::vector<Gateway> &gateway)
{
        
      for(int i = 0; i < gateway.size(); i++)
      {
          out << "\n" << gateway[i].gateway_name << "\n";

          for(int j = 0; j < gateway[i].gateway_parameters.size(); j++)
          {
              out << gateway[i].gateway_parameters[j] << "\n";
          }
      }

    return out;
}
std::ostream& operator<<(std::ostream &out2, const std::vector<Target> &target)
{
    for(int i = 0; i< target.size(); i++)
    {
        out2 << "\n" << target[i].ip << "\n";

        for(int j = 0; j < target[i].target_parameters.size(); j++)
        {
            out2 << target[i].target_parameters[j] << "\n";
        }
    }
    return out2;
}