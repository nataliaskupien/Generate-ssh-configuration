#include <gtest/gtest.h>
#include <filesystem>

namespace fs = std::filesystem;

bool created = false;

TEST(file, check_if_output_file_is_created)
{
    std::string directory_path = "../build";
    std::string file_path = "../build/configuration.txt";
    
    for(const auto & entry : fs::directory_iterator(directory_path))
    {
        if(entry.path() == file_path)
        {
            created = true;
        }
    }

    EXPECT_TRUE(created);
}