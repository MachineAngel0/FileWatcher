//
// Created by Adams Humbert on 4/18/2025.
//

#include "Logger.h"

#include <assert.h>
#include <ranges>


void Logger::print_colors()
{
    /*
     *30 → Black
    *31 → Red
    *32 → Green
    *33 → Yellow
    *34 → Blue
    *35 → Magenta
    *36 → Cyan
    *37 → White
    */


    // Text colors (foreground)
    std::cout << "\033[30m" << "Black" << "\033[0m" << std::endl;
    std::cout << "\033[31m" << "Red" << "\033[0m" << std::endl;
    std::cout << "\033[32m" << "Green" << "\033[0m" << std::endl;
    std::cout << "\033[33m" << "Yellow" << "\033[0m" << std::endl;
    std::cout << "\033[34m" << "Blue" << "\033[0m" << std::endl;
    std::cout << "\033[35m" << "Magenta" << "\033[0m" << std::endl;
    std::cout << "\033[36m" << "Cyan" << "\033[0m" << std::endl;
    std::cout << "\033[37m" << "White" << "\033[0m" << std::endl;
}

/** Doc - Main Print Function
 * @note trying to use '\n' instead of std::endl will cause printing bugs, if using std::cout
 * TODO: might want to look into using platform specific color text
 * @param text string to pass in
 * @param color ANSI Color, See Enum for Colors Available
 */
void Logger::print(const std::string_view& text, const PrintColor& color)
{
    // printf should be fine, since were only printing and not doing any sort of file i/o with it
    auto ANSI = color_look_up[color];
    printf("\033[%sm %s \033[0m \n", ANSI.c_str(), text.data());

    /* equivalent code */

    //std::cout << "\033[" << ANSI << "m" << text << "\033[0m" << std::endl;

    //std::cout << "\033[31m" << "Red" << "\033[0m" << std::endl;
}



void Logger::print_tester()
{
    // view keys lets us iterate through only the keys, since thats all we need, first time im seeing this funcation
    for (const auto& key: color_look_up | std::views::keys)
    {
        print("Get All The Colors You Desire", key);
    }
}

void Logger::custom_assert(const uint8_t assert_value, const std::string& message)
{
    if (assert_value) return;
    Logger::print("Custom Asser Message: " + message, Red);
    assert(assert_value);
}
