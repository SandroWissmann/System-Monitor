/* System Monitor
 * Copyright (C) 2020  Sandro Wißmann
 *
 * Minefield is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Minefield is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Monitor If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/System-Monitor
 */
#ifndef HELPER_H
#define HELPER_H

#include <optional>
#include <string>

namespace Sysmon::Helper {

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

}  // namespace Sysmon::Helper

#endif