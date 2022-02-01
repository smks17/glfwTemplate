#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <sstream>

/**
 * @brief delete space and tabs of begin and end of the string
 */
void trim(std::string* str);

class Config{
    private:
        std::string filename;
        bool succeed;
        std::string search(std::string key);
    public:
        static const std::string DEFAULT_FILENAME; 
        static const std::string DEFAULT_FOLDERPATH; 
        Config(std::string config_filename);
        bool is_succeed(){ return succeed; }
        std::string get(std::string key){ return search(key); }
};

template <typename T>
/**
 * convert string type to other type
 * @tparam T type of you want to converted
 * @param str input
 * @return T conversion of str in type of T
 */
static T convert_to (const std::string &str){
    std::istringstream ss(str);
    T num;
    ss >> num;
    return num;
}

extern Config conf;

#endif
