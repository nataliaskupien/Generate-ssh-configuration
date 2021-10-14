#include "config.h"

Config::Config(){} //TODO Jeżeli konstruktowa nie potrzebujesz to go nie musisz definiować w ogóle. Możesz też w pliku h napiasć Config() = default; 

 void Config::init_arguments(int argc, char* argv[])
 {
     for(int i = 1; i < argc; i++)
     {
        this->init_array.push_back(argv[i]);// TODO this-> nie jest potrzebne. po prostu: init_array.push_back(...)
     }
  
     for(auto i = init_array.begin(); i != init_array.end(); ++i )
     {
         if(*i == "-input")
         {
             i++; // TODO Zwiększanie i gdy iterujesz po wektorze jest trochę ryzykowne. Co jeżeli nie będzie następnego element?
             //TODO ewentualnie można tak
              if (i == init_array.end())
              {
               break;
              }
             this->input_name = *i;
         }
         else if(*i == "-output")
         {
             i++;
             // ewentualnie można tak (ale widzisz juz kod sie powtarza)
              if (i == init_array.end())
              {
               break;
              }
             this->output_name = *i;
         }
        else
        {
         // Nieznany element. Albo error albo ignoruj. 
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

// TODO Tą metodę na pewno trzeba podzielić na jakieś mniejsze fragmenty
 void Config::create_data() 
 {
    std::ifstream i(input_name);// TODO jezeli nie będzie argumentu to wykorzysta wewnętrzne pole input_name tej klasy 

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
         // TODO Może być wiele pól. Wszystkie powinny być skopiowane.
         // Nie można też polegać na tym że IP zawsze będzie pierwsze. 
         // trzeba wykryć pole z IP na podstawie pierwszego słowa.
         // A reszte pól po prostu skopiować ile by ich nie było.
         //
         // TODO UWAGA: nie wiem czy w ogole jest sens pole IP traktowac inaczej niz inne params
         // ono chyba w programie jest jest specjalnie uzywane co?
         
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
         
            // TODO Nie wiem czy tu jest sens iterować po tablicy bo tylko jedna linkCommand powinna być. Trzeba tylko sprawdzić czy jest. jak nie ma to ERROR
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
          // TODO podobnie jak przy targetach. moze byc wiele parametrow. wszystkie trzeba skopiwac
         // zamiast param1, param dwa powinnien byc vector<string> params
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

          // TODO czy tu nie wystarczy zrobic: for(const auto & item : j["links"][gateway.gateway_name].items()) 
         // jezeli links nie zawiera elementu o nazwie danego gatewaya to będzie wyjątek który trzeba obsłużyć i zgłosić błąd użytkownikowi
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

  //TODO ta czesc na pewno moglaby byc w osobnej metodze wywolanej tutaj
    for( int i = 0; i< gateway_array.size(); ++i)
    {
      // TODO tu powinno byc po prostu w petli przejechanie po wszystkich parametrach vector<string> params
        output_config += gateway_array[i].gateway_name + "\n\t" + gateway_array[i].param1 + "\n\t" + 
        gateway_array[i].param2 + "\n\t" + gateway_array[i].ip + "\n\n" ;
    }

  
  // TODO ten algorytm na pewno mozna uproscic ale to pozniej
    for(int i=0; i<links_array.size(); i++)
    {
     //TODO dodaj troche posrednich zmiennych np.
        auto current_link = links_array[i];
        for(int j =0; j<current_link.links_gateway[i].gateway_target.size(); j++)
        {
            auto current_link_gateway = links_array[i].links_gateway[i];
            auto current_link_gateway_target = current_link_gateway.gateway_target[j];
            auto target_name = current_link_gateway_target.target_name + "_" + current_link_gateway.gateway_name + "\n\t";
            output_config += target_name
            + current_link_gateway_target.ip + "\n\t" +  current_link_gateway_target.param1 + "\n\t" +
            current_link_gateway_target.param2 + "\n\t" + current_link_gateway_target.command + " " + current_link_gateway.gateway_name + "\n\n";
           // TODO parametry tez for po vector<string> params
        }
    }
  
 }

 bool Config::is_json() const // TODO czy to jest json trzeba sprawdzic probujac parsowac na strukture. jezeli nie bedzie bledu to ok.
 {
     if(input_name.size() > 0)
    {
        return true;
    }

    return false;
 }

 bool Config::save_to_file() const //TODO reczej if_output_defined ?
 {
    if (output_name.size() > 0)
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
 // TODO czy ten kod nie jest ten sam co wyzej? wynik tamten nie jest uzywany?
    std::string output_config;

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
             links_array[i].links_gateway[i].gateway_target[j].param2 + "\n\t" + links_array[i].links_gateway[i].gateway_target[j].command +"\n\n";
        }
    }
    return output_config;
}
