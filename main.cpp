#include <chrono>
#include <filesystem>
#include <thread>
#include <unordered_set>
#include <vector>

#include "Logger.h"

#include "FileWatcher.h"

int main()
{
    Logger::print_colors();
    Logger::print_tester();

    //std::filesystem::path FilePath = R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcher)";

    FileWatcher* file_watcher = new FileWatcher(R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcher)");
    //FileWatcher* file_watcher = new FileWatcher(R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcherasds)");

    // fake application/game loop
    while (true)
    {
        file_watcher->update();
    }

    return 0;
}
