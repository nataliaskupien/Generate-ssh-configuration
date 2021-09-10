cmake_minimum_required(VERSION 3.0.0)
add_subdirectory(nlohmann)
project(generate_ssh_config VERSION 0.1.0)


add_executable(generate_ssh_config 
    main.cpp
    config.cpp
    target.cpp
    gateway.cpp
    links.cpp
    save_file.cpp
    )

target_link_libraries(generate_ssh_config PRIVATE nlohmann_json::nlohmann_json)