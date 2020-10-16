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
#include "../../include/parser.h"
#include "../../include/helper.h"

#include <unistd.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace Sysmon::Linux::Parser {

const std::string kOSPath{"/etc/os-release"};
const std::string kProcDirectory{"/proc/"};
const std::string kVersionFilename{"/version"};
const std::string kUptimeFilename{"/uptime"};
const std::string kStatFilename{"/stat"};

std::string OperatingSystem() {
    std::string line;
    std::string key;
    std::string value;
    std::ifstream filestream(kOSPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ' ', '_');
            std::replace(line.begin(), line.end(), '=', ' ');
            std::replace(line.begin(), line.end(), '"', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "PRETTY_NAME") {
                    std::replace(value.begin(), value.end(), '_', ' ');
                    return value;
                }
            }
        }
    }
    return value;
}

std::string Kernel() {
    std::string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::string os;
        std::string fill;
        std::string kernel;
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> fill >> kernel;
        return kernel;
    }
    return std::string{};
}

std::vector<int> Pids() {
    std::vector<int> pids;
    std::filesystem::path path{kProcDirectory};
    for (auto& entry : std::filesystem::directory_iterator{path}) {
        if (entry.is_directory()) {
            if (auto filename = entry.path().filename();
                Helper::IsNumber<int>(filename)) {
                auto pid = std::stoi(filename);
                pids.emplace_back(pid);
            }
        }
    }
    return pids;
}

long UpTime() {
    std::ifstream ifs{kProcDirectory + kUptimeFilename};
    if (ifs.is_open()) {
        std::string line;
        std::getline(ifs, line);
        std::istringstream ist{line};
        std::string uptime;
        ist >> uptime;

        if (Helper::IsNumber<double>(uptime)) {
            return std::stol(uptime);
        }
    }
    return 0;
}

int TotalProcesses() {
    return Helper::ReadValueFromFile<int>(kProcDirectory + kStatFilename,
                                          "processes");
}

int RunningProcesses() {
    return Helper::ReadValueFromFile<int>(kProcDirectory + kStatFilename,
                                          "procs_running");
}

}  // namespace Linux::Parser
