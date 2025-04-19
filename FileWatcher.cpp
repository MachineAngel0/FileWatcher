//
// Created by Adams Humbert on 4/18/2025.
//

#include "FileWatcher.h"

#include <assert.h>


#include "Logger.h"

FileWatcher::FileWatcher(const std::filesystem::path& FileDirectory)
{
    // set our file path
    FilePath = FileDirectory;

    // do an assert on the file path
    Logger::custom_assert(std::filesystem::is_directory(FilePath), "Invalid Path For File Manager");

    // if we get here that means a valid path
    Logger::print("Valid Path", Green);
    std::cout << FilePath << std::endl;


    /* Initialization */


    /*we want an up to date file set, and a time stamp*/

    // get all the files in the directory
    file_set = get_files_in_directory_hash(FilePath);
    // so this works by checking the time stamps
    PrevTimeStamp = std::filesystem::last_write_time(FilePath);
}

void FileWatcher::update()
{

    if (PrevTimeStamp != std::filesystem::last_write_time(FilePath))
    {

        std::cout << "File Changed Previous timestamp: " << PrevTimeStamp << "//// New Time Stamp" <<
                std::filesystem::last_write_time(FilePath) << '\n';
        PrevTimeStamp = std::filesystem::last_write_time(FilePath);

        //check which file is new?
        std::vector<std::filesystem::path> a = find_changed_file(FilePath, file_set);

        file_set = get_files_in_directory_hash(FilePath);
    }
}




std::vector<std::filesystem::path> FileWatcher::get_files_in_directory(const std::filesystem::path& dir_path)
{
    std::vector<std::filesystem::path> files;
    for (const auto& entry: std::filesystem::directory_iterator(dir_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            files.emplace_back(entry.path());
        }
    }
    return files;
}

std::unordered_set<std::filesystem::path> FileWatcher::get_files_in_directory_hash(const std::filesystem::path& dir_path)
{
    std::unordered_set<std::filesystem::path> files;
    for (const auto& entry: std::filesystem::directory_iterator(dir_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            files.insert(entry.path());
        }
    }
    return files;
}

std::vector<std::filesystem::path> FileWatcher::find_changed_file(const std::filesystem::path& dir_path,
                                                     std::unordered_set<std::filesystem::path>& Previous_File_Set)
{
    std::vector<std::filesystem::path> files;

    int new_file_size_count = 0;
    // check the sizes, and see if the files have been added, removed, or modified
    Logger::print("New Set Of Files", Magenta);
    for (const auto& entry: std::filesystem::directory_iterator(dir_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            std::cout << entry.path() << '\n';
            new_file_size_count++;
        }
    }

    Logger::print("Prev Set of Files", Magenta);
    for (auto& Files_In_Set: Previous_File_Set)
    {
        std::cout << Files_In_Set << '\n';
    }


    size_t prev_file_size = Previous_File_Set.size();
    if (prev_file_size != new_file_size_count)
    {
        std::cout << "File Size Changed, Prev File Size: " << Previous_File_Set.size() << " New File Size: " <<
                new_file_size_count << '\n';

        if (prev_file_size < new_file_size_count)
        {
            Logger::print("File Was Added:", Magenta);
            std::cout << "Old File Size:" <<Previous_File_Set.size() << ", New File Size:"<< new_file_size_count << '\n';

            //find the added file
            for (const auto& entry: std::filesystem::directory_iterator(dir_path))
            {
                if (std::filesystem::is_regular_file(entry) and !Previous_File_Set.contains(entry.path()))
                {
                    std::cout << "New File:" << entry.path() << std::endl;
                    files.emplace_back(entry.path());
                    Previous_File_Set.insert(entry.path());
                }
            }
        }
        else if (prev_file_size > new_file_size_count)
        {
            Logger::print("File Was Removed:", Magenta);
            std::cout << Previous_File_Set.size() << new_file_size_count << '\n';

            //find removed file
            std::unordered_set<std::filesystem::path> Files_In_Set;
            for (const auto& entry: std::filesystem::directory_iterator(dir_path))
            {
                if (std::filesystem::is_regular_file(entry))
                {
                    files.emplace_back(entry.path());
                }
            }
            std::unordered_set<std::filesystem::path> difference;
            std::ranges::set_difference(Previous_File_Set, Files_In_Set,
                                        std::inserter(difference, difference.begin()));

            std::cout << "Difference (set1 - set2): ";
            for (const auto& element : difference) {
                std::cout << element << '\n';
            }
            std::cout << std::endl;


        }
    }
    else
    {
        // check which file was modified
        Logger::print("A File Was Modified:", Magenta);
    }



    return files;
}



