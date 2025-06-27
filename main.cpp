#include <chrono>
#include <filesystem>
#include <thread>
#include <unordered_set>
#include <vector>

#include "Logger.h"

#include "FileWatcher.h"
#include "Timer.h"

int main()
{
    //testing the logger works,
    Logger::print_colors();
    Logger::print_tester();

    //std::filesystem::path FilePath = R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcher)";

    FileWatcher file_watcher;
    file_watcher_init(file_watcher, R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcher)");
    // file path to test the assertion works
    //FileWatcher* file_watcher = new FileWatcher(R"(C:\Users\Adams Humbert\Documents\Clion\FileWatcherasds)");

    Timer timer;
    int elapsed_count = 1;
    double average = 0;

    // fake application/game loop
    //TODO: add some sort of input for escaping and easy testing
    while (true)
    {
        timer.reset();

        file_watcher_update(file_watcher);

        std::cout<< std::fixed << "Time Elapsed: " << (double)timer.elapsed() << '\n';
        average += timer.elapsed()/elapsed_count;
        std::cout << "Average:" << average << '\n';
        elapsed_count++;
    }

    return 0;
}
