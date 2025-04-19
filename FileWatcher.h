//
// Created by Adams Humbert on 4/18/2025.
//

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <filesystem>
#include <unordered_set>

//TODO:
// Ability to be able to ignore certain directory paths, such as the .git file, or the CMake File, could do either a hash set or some sort of file I/O (Json or CSV)
// Take Updated Files and parse its .ext, and then have an event or something similar listen so that they can load/unload, or do any operation they want on the file
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
