//
// Created by Adams Humbert on 4/18/2025.
//

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <filesystem>
#include <iostream>
#include <unordered_set>


class FileWatcher {

public:

    explicit FileWatcher(const std::filesystem::path& FileDirectory /*,bool recursive*/);

    void update();

    std::vector<std::filesystem::path> get_files_in_directory(const std::filesystem::path& dir_path);

    std::unordered_set<std::filesystem::path> get_files_in_directory_hash(const std::filesystem::path& dir_path);

    std::vector<std::filesystem::path> find_changed_file(const std::filesystem::path& dir_path,
                                                         std::unordered_set<std::filesystem::path>& Previous_File_Set);

private:

    std::filesystem::file_time_type PrevTimeStamp;
    std::unordered_set<std::filesystem::path> file_set;

    std::filesystem::path FilePath;
};


//TODO:Testing Folder and testing functions



#endif //FILEWATCHER_H
