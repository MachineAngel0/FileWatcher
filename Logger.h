//
// Created by Adams Humbert on 4/18/2025.
//

#ifndef LOGGER_H
#define LOGGER_H


#include <iostream>
#include <unordered_map>
#include <string_view>

enum PrintColor
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
};


//colors look up table
inline std::unordered_map<PrintColor, std::string> color_look_up{
    {Black, "30" },
    {Red, "31" },
    {Green, "32" },
    {Yellow, "33" },
    {Blue, "34" },
    {Magenta, "35" },
    {Cyan, "36" },
    {White, "37" },

};

class Logger
{
    public:
    // testing functions
    static void print_colors();
    static void print_tester();

    // actual print function to use
    static void print(const std::string_view& text, const PrintColor& color);
    // an assert function
    static void custom_assert(uint8_t assert_value, const std::string& message);

};



#endif //LOGGER_H
