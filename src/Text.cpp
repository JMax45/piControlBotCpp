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

bool Text::checkSame(std::vector<std::string> list, std::string str){
    bool value = false;
    for(int i=0; i<list.size(); i++){
        if(list[i]==str){
            value = true;
        }
    }
    return value;
}