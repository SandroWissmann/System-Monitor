#include "helper.h"

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

namespace Helper {

template <typename ValueType>
ValueType ReadValueFromFile(const std::string& filename,
                            const std::string& key) {
    std::ifstream ifs{filename};
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            auto valueOpt = ReadValueFromLine<ValueType>(line, key);
            if (valueOpt) {
                return *valueOpt;
            }
        }
    }
    return ValueType{};
}

template int ReadValueFromFile(const std::string& filename,
                               const std::string& key);
template long ReadValueFromFile(const std::string& filename,
                                const std::string& key);
template double ReadValueFromFile(const std::string& filename,
                                  const std::string& key);

template <typename ValueType>
std::optional<ValueType> ReadValueFromLine(const std::string& line,
                                           const std::string& expectedKey) {
    std::istringstream ist{line};
    std::string key;
    ist >> key;
    if (key == expectedKey) {
        std::string value;
        ist >> value;

        if (IsNumber<ValueType>(value)) {
            if (std::is_same<ValueType, int>::value) {
                return {std::stoi(value)};
            }
            if (std::is_same<ValueType, long>::value) {
                return {std::stol(value)};
            }
            if (std::is_same<ValueType, double>::value) {
                return {std::stof(value)};
            }
            if (std::is_same<ValueType, double>::value) {
                return {std::stod(value)};
            }
        }
    }
    return {};
}

template std::optional<int> ReadValueFromLine(const std::string& line,
                                              const std::string& expectedKey);
template std::optional<long> ReadValueFromLine(const std::string& line,
                                               const std::string& expectedKey);
template std::optional<double> ReadValueFromLine(
    const std::string& line, const std::string& expectedKey);

template <typename T>
bool IsNumber(const std::string& s) {
    if (s.empty()) {
        return false;
    }

    std::istringstream ist(s);
    T n;
    ist >> std::noskipws >> n;

    return ist.eof() && !ist.fail();
}

template bool IsNumber<int>(const std::string& s);
template bool IsNumber<double>(const std::string& s);

std::string ReadFirstLineFromFile(const std::string& filename) {
    std::string line;
    std::ifstream ifs{filename};
    if (ifs.is_open()) {
        std::getline(ifs, line);
    }
    return line;
}

}  // namespace Helper