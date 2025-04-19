//
// Created by Adams Humbert on 4/18/2025.
//

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <filesystem>
#include <unordered_set>

//TODO: Add a recursive check for subdirectories
class FileWatcher {

public:

    explicit FileWatcher(const std::filesystem::path& FileDirectory /*,bool recursive*/);

    void update();

    std::vector<std::filesystem::path> get_files_in_directory(const std::filesystem::path& dir_path);

    std::unordered_set<std::filesystem::path> get_files_in_directory_hash();

   std::unordered_set<std::filesystem::path> find_changed_file();

private:

    // file path we want to be operating on
    std::filesystem::path file_path;
    // time stamp for checking against file modification, add, or remove
    std::filesystem::file_time_type prev_time_stamp;
    // a list of all our files, to check against any file changes
    std::unordered_set<std::filesystem::path> file_set;
};


//TODO: Testing Folder and testing functions



#endif //FILEWATCHER_H
