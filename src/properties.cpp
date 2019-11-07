#include <properties.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>

std::map<std::string, std::string> Properties::properties;

// Trim string from the left
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// Trim string from the right
static void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Trim string from both ends
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void Properties::reload() {
    std::ifstream file(fileName);
    std::string line, propName, propValue;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::getline(lineStream, propName,  ':');
        std::getline(lineStream, propValue, ':');
        trim(propName);
        trim(propValue);
        properties[propName] = propValue;
    }
    file.close();
}

const std::string& Properties::raw_get(std::string propertyName) {
    return properties[propertyName];
}

std::string Properties::get_string(std::string propertyName) {
    const std::string& got = raw_get(propertyName);
    return got.substr(1, got.length() - 2);
}

int Properties::get_int(std::string propertyName) {
    return stoi(raw_get(propertyName));
}

std::pair<uint8_t, uint8_t> Properties::get_byte_pair(std::string propertyName) {
    std::istringstream lineStream(raw_get(propertyName));
    std::string byte1Str, byte2Str;
    std::getline(lineStream, byte1Str, ' ');
    std::getline(lineStream, byte2Str, ' ');
    return std::make_pair(stoi(byte1Str), stoi(byte2Str));
}