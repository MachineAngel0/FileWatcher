//
// Created by Adams Humbert on 4/18/2025.
//

#include "FileWatcher.h"
#include "Logger.h"

void file_watcher_init(FileWatcher file_watcher, const std::filesystem::path& FileDirectory)
{
    // set our file path
    file_watcher.file_path = FileDirectory;

    // do an assert on the file path
    Logger::custom_assert(std::filesystem::is_directory(file_watcher.file_path), "Invalid Path For File Manager");

    // if we get here that means a valid path
    Logger::print("Valid Path", Green);
    std::cout << file_watcher.file_path << '\n';


    /* Initialization */


    /*we want an up to date file set, and a time stamp*/

    // get all the files in the directory
    file_watcher.file_set = file_watcher_get_files_in_directory_hash(file_watcher);
    // so this works by checking the time stamps
    file_watcher.prev_time_stamp = std::filesystem::last_write_time(file_watcher.file_path);
}

void file_watcher_update(FileWatcher file_watcher)
{
    // check if we have a modified file
    std::filesystem::file_time_type CurrentTimeStamp = std::filesystem::last_write_time(file_watcher.file_path);
    if (file_watcher.prev_time_stamp != CurrentTimeStamp)
    {
        // log
        std::cout << "File Changed Previous timestamp: " << file_watcher.prev_time_stamp << ", New Time Stamp: " <<
                CurrentTimeStamp << '\n';

        // update our time stamp
        file_watcher.prev_time_stamp = CurrentTimeStamp;

        //get a list of all the new files
        // find which files have changed
        // update our file_set to be current with any changes
        file_watcher.file_set = file_watcher_find_changed_file();
    }
}


std::vector<std::filesystem::path> file_watcher_get_files_in_directory(const std::filesystem::path& dir_path)
{
    std::vector<std::filesystem::path> files;
    for (const auto& entry: std::filesystem::recursive_directory_iterator(dir_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            files.emplace_back(entry.path());
        }
    }
    return files;
}

std::unordered_set<std::filesystem::path> file_watcher_get_files_in_directory_hash(const FileWatcher& file_watcher)
{
    std::unordered_set<std::filesystem::path> files;
#ifndef DEBUG_FILEWATCHER
    Logger::print("New Set Of Files", Magenta);
#endif
    for (const auto& entry: std::filesystem::recursive_directory_iterator(file_watcher.file_path))
    {
        if (std::filesystem::is_regular_file(entry))
        {
#ifndef DEBUG_FILEWATCHER
            std::cout << entry.path() << '\n';
#endif
            files.insert(entry.path());
        }
    }
    return files;
}

std::unordered_set<std::filesystem::path> file_watcher_find_changed_file(const FileWatcher& file_watcher_struct)
{
    // get our changed set of files
    std::unordered_set<std::filesystem::path> updated_files = file_watcher_get_files_in_directory_hash(file_watcher_struct);

#ifndef DEBUG_FILEWATCHER
    Logger::print("Prev Set of Files", Magenta);
    for (auto& Files_In_Set: file_set)
    {
        std::cout << Files_In_Set << '\n';
    }
#endif


    // with the size see if the files have been added, removed, or modified
    size_t prev_file_size = file_watcher_struct.file_set.size();
    size_t new_file_size_count = updated_files.size();

    if (prev_file_size != new_file_size_count) // check if we have added or removed any files
    {
        std::cout << "File Size Changed, Prev File Size: " << file_watcher_struct.file_set.size() << " New File Size: " <<
                new_file_size_count << '\n';

        if (prev_file_size < new_file_size_count) // file(s) got added
        {
            Logger::print("File Was Added:", Magenta);
            std::cout << "Old File Size:" << file_watcher_struct.file_set.size() << ", New File Size:" << new_file_size_count << '\n';

            //find the added file by checking if the old hash has the new files
            for (const auto& file: updated_files)
            {
                if (!file_watcher_struct.file_set.contains(file))
                {
                    std::cout << "New File:" << file << '\n';
                }
            }
        }
        else if (prev_file_size > new_file_size_count) // file(s) got removed
        {
            Logger::print("File Was Removed:", Magenta);
            std::cout << "Old File Size:" << file_watcher_struct.file_set.size() << ", New File Size:" << new_file_size_count << '\n';

            //find the removed file by checking if the new hash does not contain the old files
            for (const auto& file: file_watcher_struct.file_set)
            {
                if (!updated_files.contains(file))
                {
                    std::cout << "Deleted File:" << file << '\n';
                }
            }
        }
    }
    else
    {
        // check which file was modified
        Logger::print("A File Was Modified:", Magenta);
    }

    //TODO: look into move semantics since this seems like a use case for this return
    // update our tile_set with the updated files
    return updated_files;
}


\
