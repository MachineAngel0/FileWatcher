//
// Created by Adams Humbert on 4/18/2025.
//

#include "FileWatcher.h"

#include <assert.h>


#include "Logger.h"

FileWatcher::FileWatcher(const std::filesystem::path& FileDirectory)
{
    // set our file path
    file_path = FileDirectory;

    // do an assert on the file path
    Logger::custom_assert(std::filesystem::is_directory(file_path), "Invalid Path For File Manager");

    // if we get here that means a valid path
    Logger::print("Valid Path", Green);
    std::cout << file_path << std::endl;


    /* Initialization */


    /*we want an up to date file set, and a time stamp*/

    // get all the files in the directory
    file_set = get_files_in_directory_hash();
    // so this works by checking the time stamps
    prev_time_stamp = std::filesystem::last_write_time(file_path);
}

void FileWatcher::update()
{

    // check if we have a modified file
    std::filesystem::file_time_type CurrentTimeStamp = std::filesystem::last_write_time(file_path);
    if (prev_time_stamp != CurrentTimeStamp)
    {
        // log
        std::cout << "File Changed Previous timestamp: " << prev_time_stamp << "//// New Time Stamp" <<
                CurrentTimeStamp << '\n';

        // update our time stamp
        prev_time_stamp = CurrentTimeStamp;

        //get a list of all the new files
        // find which files have changed
        // update our file_set to be current with any changes
        file_set = find_changed_file();
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

std::unordered_set<std::filesystem::path> FileWatcher::get_files_in_directory_hash()
{
    std::unordered_set<std::filesystem::path> files;
    Logger::print("New Set Of Files", Magenta);
    for (const auto& entry: std::filesystem::directory_iterator(file_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            std::cout << entry.path() << std::endl;
            files.insert(entry.path());
        }
    }
    return files;
}

std::unordered_set<std::filesystem::path> FileWatcher::find_changed_file()
{
    // get our changed set of files
    std::unordered_set<std::filesystem::path> updated_files = get_files_in_directory_hash();

    Logger::print("Prev Set of Files", Magenta);
    for (auto& Files_In_Set: file_set)
    {
        std::cout << Files_In_Set << '\n';
    }

    // with the size see if the files have been added, removed, or modified
    size_t prev_file_size = file_set.size();
    size_t new_file_size_count =  updated_files.size();

    if (prev_file_size != new_file_size_count) // check if we have added or removed any files
    {
        std::cout << "File Size Changed, Prev File Size: " << file_set.size() << " New File Size: " <<
                new_file_size_count << '\n';

        if (prev_file_size < new_file_size_count) // file(s) got added
        {
            Logger::print("File Was Added:", Magenta);
            std::cout << "Old File Size:" <<file_set.size() << ", New File Size:"<< new_file_size_count << '\n';

            //find the added file by checking if the old hash has the new files
            for (const auto& file: updated_files)
            {
                if (!file_set.contains(file))
                {
                    std::cout << "New File:" << file << std::endl;
                }
            }
        }
        else if (prev_file_size > new_file_size_count) // file(s) got removed
        {
            Logger::print("File Was Removed:", Magenta);
            std::cout << "Old File Size:" <<file_set.size() << ", New File Size:"<< new_file_size_count << '\n';

            //find the removed file by checking if the new hash does not contain the old files
            for (const auto& file: file_set)
            {
                if (!updated_files.contains(file))
                {
                    std::cout << "Deleted File:" << file << std::endl;
                }
            }



        }
    }
    else
    {
        // check which file was modified
        Logger::print("A File Was Modified:", Magenta);
    }


    // update our tile_set with the updated files
    return updated_files;
}



