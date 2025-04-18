#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>
#include <vector>

std::vector<std::filesystem::path> get_files_in_directory(const std::filesystem::path& dir_path)
{
    std::vector<std::filesystem::path> files;
    for (const auto& entry: std::filesystem::directory_iterator(dir_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            files.push_back(entry.path());
        }
    }
    return files;
}


void run()
{
    std::filesystem::path directory_to_watch = "C:\\Users\\Adams Humbert\\Documents\\Clion\\FileWatcher";
    // Current directory

    std::vector<std::filesystem::path> previous_files = get_files_in_directory(directory_to_watch);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Check every second
        std::vector<std::filesystem::path> current_files = get_files_in_directory(directory_to_watch);


        for (const auto& file: current_files)
        {
            if (std::ranges::find(previous_files, file) == previous_files.end())
            {
                std::cout << "New file detected: " << file << std::endl;
            }
        }
        previous_files = current_files;
    }
}



int main()
{

    std::filesystem::path FilePath =  R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcher)";

    // so this works by checking the time stamps
    std::filesystem::file_time_type PrevTimeStamp{std::filesystem::last_write_time(FilePath)};
    while (true)
    {
        if (PrevTimeStamp != std::filesystem::last_write_time(FilePath))
        {
            std::cout << "File Changed Previous timestamp: " << PrevTimeStamp << std::endl;
            PrevTimeStamp = std::filesystem::last_write_time(FilePath);
        }
    }

    return 0;
}
