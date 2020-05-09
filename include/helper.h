#ifndef HELPER_H
#define HELPER_H

#include <optional>
#include <string>

namespace Helper {

// Helper functions
template <typename ValueType>
ValueType ReadValueFromFile(const std::string& filename,
                            const std::string& key);

template <typename ValueType>
std::optional<ValueType> ReadValueFromLine(const std::string& line,
                                           const std::string& expectedKey);

template <typename T>
bool IsNumber(const std::string& s);

std::string ReadFirstLineFromFile(const std::string& filename);

}  // namespace Helper

#endif