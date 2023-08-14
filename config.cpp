#include <fstream>
#include <iostream>

#ifdef _WIN32
    #include <Windows.h>

    std::string getProjectPath(){
        wchar_t buffer[MAX_PATH] = {0};
        int position_slash = 0;
        std::string path;
        GetModuleFileNameW(NULL, buffer, MAX_PATH);
        for (int i = 0; i < (sizeof(buffer) / sizeof(buffer[0])); i++) {
            if (buffer[i] == '/' || buffer[i] == '\\')
                position_slash = i;
            char ch;
            int ch_size = sizeof(ch);
            wctomb_s(&ch_size, &ch, sizeof(buffer[i]), buffer[i]);
            path += ch;
        }
        return path.substr(0, position_slash+1);
    }
#else
    #include <limits.h>
    #include <unistd.h>

    std::string getProjectPath(){
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        int position_slash = 0;
        for(int i = 0; i < count; i++){
                if (result[i] == '/' || result[i] == '\\'){
                        position_slash = i;
                }
        }
        return std::string( result, (count > 0) ? count - (count - position_slash - 1) : 0 );
    }
#endif

#include "config.h"

const std::string Config::DEFAULT_FILENAME = "setting.conf";
const std::string Config::DEFAULT_FOLDERPATH = getProjectPath();

// global object
Config conf(Config::DEFAULT_FILENAME);

void trim(std::string* str){
    while(!str->empty() && std::isspace(*(str->begin())))
        str->erase(str->begin());

    while(!str->empty() && std::isspace(*str->rbegin()))
        str->erase(str->length()-1);
}

Config::Config(std::string config_filename = DEFAULT_FILENAME){
    filename = config_filename;
}

std::string Config::search(std::string key){
    std::ifstream in(DEFAULT_FOLDERPATH + filename, std::ios::in);
    if(!in.is_open()){
        succeed = false;
        return "";
    }

    std::string value;
    std::string line;
    while(!in.eof()){
        std::getline(in, line);
        trim(&line);
        if(line.at(0) == '#')
            continue;

        size_t pos = line.find("=");
        std::string first = line.substr(0, pos);
        if(first == key){
            value = line.substr(pos + 1, line.size());
            trim(&value);
            break;
        }
    }

    in.close();
    return value;
}
