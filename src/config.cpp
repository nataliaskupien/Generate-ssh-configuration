#include "include/config.h"
#include <algorithm>

void Config::init_arguments(int argc, char* argv[])
{
    std::vector<std::string>::iterator itr;

    for(int i = 1; i < argc; i++)
    {
        init_array.push_back(argv[i]);
    }
    for(itr = init_array.begin(); itr != init_array.end(); ++itr )
    {
        if(*itr == "-input")
        {
            itr = std::next(itr,1);
            
            if(itr == init_array.end())
            {
                break;
            }
            this->input_name = *itr;
        }
        else if(*itr == "-output")
        {
            itr = std::next(itr,1);

            if(itr == init_array.end())
            {
                break;
            }
            this->output_name = *itr;
        }
        else
        {
            std::cerr << "Unrecognized element in vector" << std::endl;
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

void Config::create_data()
{
    std::ifstream i(input_name);
    json j = ordered_json::parse(i);
    
    std::string val;

    //Tworzenie targetow

    for(auto it = j["targets"].begin(); it != j["targets"].end(); ++it)
    {
        Target target;
        target.target_name = it.key();

        for(const auto & item : j["targets"][target.target_name].items())
        {
            val = item.value().get<std::string>();

            target.target_parameters.push_back(val);

            if(j["linkCommand"].empty())
            {
                std::cerr << "No link command found!" << std::endl;
            }
            else
            {
                target.command = j["linkCommand"];
            }
        }
        targets_array.push_back(target);
    }

//Tworzenie gateways

    for(auto it = j["gateways"].begin(); it != j["gateways"].end(); ++it)
    {
        Gateway gateway;

        gateway.gateway_name = it.key();

        for(const auto & item : j["gateways"][gateway.gateway_name].items())
        {
            val = item.value().get<std::string>();
            gateway.gateway_parameters.push_back(val);
        }

//Przypisanie targetów do okreslonego Gateway

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
                        std::string to_replace = "<gateway>";
                        auto f = gateway.gateway_target[i].command.find(to_replace);

                        if(f != std::string::npos)
                        {
                            gateway.gateway_target[i].command.erase(f, to_replace.length());
                            gateway.gateway_target[i].command += gateway.gateway_name;
                        }
                        
                    }
                }
            }
        }
    gateway_array.push_back(gateway);
    }

//Wrzucenie do Links Gateway z przypisanymi do niego targetami

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
    try
    {
        std::ifstream i(input_name);
        json j = json::parse(i);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool Config::if_output_defined() const
{
    if(output_name.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Config::create_config()
{
    std::ostringstream ss;
    ss << gateway_array;
    output_config += ss.str();

    for(int i = 0; i < links_array.size(); i++)
    {
        auto current_link_gateway = links_array[i].links_gateway[i];

        for(int j = 0; j < current_link_gateway.gateway_target.size(); j++)
        {
            auto current_link_target = current_link_gateway.gateway_target[j];
            auto target_name = current_link_gateway.gateway_name + "_" + current_link_target.target_name;
            output_config += target_name;

            ss.str("");
            ss.clear();
            ss << current_link_target;
            output_config += ss.str();
        }
    }
    return output_config;
}

std::ostream& operator<<(std::ostream &out, const std::vector<Gateway> &gateway)
{
        
    for(int i = 0; i < gateway.size(); i++)
    {
        out << gateway[i].gateway_name << "\n";

        for(int j = 0; j < gateway[i].gateway_parameters.size(); j++)
        {
            out << "\t" << gateway[i].gateway_parameters[j] << "\n";
        }
        out << "\n";
    }
    return out;
}

std::ostream& operator<<(std::ostream &out2, const Target &target)
{

    for(int j = 0; j < target.target_parameters.size(); j++)
    {
        out2 << "\n\t" << target.target_parameters[j];
    }
    out2 << "\n\t" << target.command << "\n\n";

    return out2;
}