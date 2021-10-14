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

    json j = json::parse(i);

    //Tworzenie targetow

    for(auto it = j["targets"].begin(); it != j["targets"].end(); ++it)
    {
        Target target;

        target.target_name = it.key();

        std::string input;
        std::string delimieter = " ";

        for(const auto & item : j["targets"][target.target_name].items())
        {
            if(item.key() == "0")
            {
                input = item.value().get<std::string>();

                target.ip = input.erase(0, input.find(delimieter) + delimieter.length());
            }
            else if(item.key() == "1")
            {
                input = item.value().get<std::string>();

                target.param1 = input.erase(0 ,input.find(delimieter) + delimieter.length());
            }
            else if(item.key() == "2")
            {
                input = item.value().get<std::string>();

                target.param2 = input.erase(0, input.find(delimieter) + delimieter.length());
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
            if(item.key() == "0")
            {
                gateway.param1 = item.value().get<std::string>();
            }
            else if(item.key() == "1")
            {
                gateway.param2 = item.value().get<std::string>();
            }
            else if(item.key() == "2")
            {
                gateway.ip = item.value().get<std::string>();
            }
        }

        for(auto it = j["links"].begin(); it != j["links"].end(); ++it)
        {
            std::string link_name = it.key();
        
            if (link_name != gateway.gateway_name)
            {
                continue;
            }

            for(const auto & item : j["links"][link_name].items())
            {
                for (int i=0; i<targets_array.size(); i++)
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

        for (int i=0; i<gateway_array.size(); i++)
        {
            if(name == gateway_array[i].gateway_name)
            {

                link.links_gateway[i] = gateway_array[i];
            }
        }
        links_array.push_back(link);
    }

    //Tworzenie pliku wyjsciowego

    for( int i = 0; i< gateway_array.size(); ++i)
    {
        output_config += gateway_array[i].gateway_name + "\n\t" + gateway_array[i].param1 + "\n\t" + 
        gateway_array[i].param2 + "\n\t" + gateway_array[i].ip + "\n\n" ;
    }

    for(int i=0; i<links_array.size(); i++)
    {
        for(int j =0; j<links_array[i].links_gateway[i].gateway_target.size(); j++)
        {
            output_config += links_array[i].links_gateway[i].gateway_target[j].target_name + "_" + links_array[i].links_gateway[i].gateway_name + "\n\t"
            + links_array[i].links_gateway[i].gateway_target[j].ip + "\n\t" +  links_array[i].links_gateway[i].gateway_target[j].param1 + "\n\t" +
            links_array[i].links_gateway[i].gateway_target[j].param2 + "\n\t" + links_array[i].links_gateway[i].gateway_target[j].command + " " + links_array[i].links_gateway[i].gateway_name + "\n\n";
        }
    }
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

 std::string Config::get_link_command()
 {
     return this->link_command;
 }
