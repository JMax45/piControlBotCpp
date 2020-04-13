#include "../include/Text.h"

void Text::split(std::string s, std::string delimiter, std::string filename){
    auto start = 0U;
    auto end = s.find(delimiter);
    std::ofstream file(filename);
    while (end != std::string::npos)
    {
        file << s.substr(start, end - start) << "\n";
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    file << s.substr(start, end);
    file.close();
}