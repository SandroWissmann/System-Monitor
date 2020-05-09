//#include <dirent.h>
#include <unistd.h>
#include <filesystem>
#include <string>
#include <vector>

#include "helper.h"
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

#include <dirent.h>

namespace LinuxParser {

// DONE: An example of how to read data from the filesystem
string OperatingSystem() {
    string line;
    string key;
    string value;
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

// DONE: An example of how to read data from the filesystem
// Fixed this before returned version which is one token before
// the real kernel name
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

// DONE: Update this to use std::filesystem
std::vector<int> Pids() {
    std::vector<int> pids;
    std::filesystem::path path{kProcDirectory};
    for (auto& entry : std::filesystem::directory_iterator{path}) {
        if (entry.is_directory()) {
            if (auto filename = entry.path().filename();
                Helper::IsNumber<int>(filename)) {
                auto pid = std::stoi(filename);
                pids.emplace_back(pid);

                if(pid > 32768) {
                    pid = 32768;
                }
            }
        }
    }
    return pids;
}



// DONE: Read and return the system memory utilization

// for now only calculate total used Memory here
// like in htop we could also calculate later:
/*
Total used memory = MemTotal - MemFree
Non cache/buffer memory (green) =
    Total used memory - (Buffers + Cached memory)
Buffers (blue) = Buffers
Cached memory (yellow) = Cached + SReclaimable - Shmem
Swap = SwapTotal - SwapFree
*/
float MemoryUtilization() {
    std::ifstream ifs{kProcDirectory + kMeminfoFilename};
    if (ifs.is_open()) {
        string line;
        std::getline(ifs, line);
        auto memTotalOpt = Helper::ReadValueFromLine<long>(line, "MemTotal:");
        if (!memTotalOpt) {
            return 0.0;
        }
        std::getline(ifs, line);
        auto memFreeOpt = Helper::ReadValueFromLine<long>(line, "MemFree:");
        if (!memFreeOpt) {
            return 0.0;
        }
        float memTotal = *memTotalOpt;
        float memUsed =  *memTotalOpt - *memFreeOpt;
        return  memUsed / memTotal;
    }
    return 0.0;
}

// DONE: Read and return the system uptime
long UpTime() {
    std::ifstream ifs{kProcDirectory + kUptimeFilename};
    if (ifs.is_open()) {
        string line;
        std::getline(ifs, line);
        std::istringstream ist{line};
        string uptime;
        ist >> uptime;

        if (Helper::IsNumber<double>(uptime)) {
            return std::stol(uptime);
        }
    }
    else {
        std::ofstream ofs{"debug.txt", std::ios_base::app};
        ofs << kProcDirectory + kUptimeFilename
            <<"\tCould not be opened\n";
    }
    return 0;
}

// DONE: Read and return the total number of processes
int TotalProcesses() {
    return Helper::ReadValueFromFile<int>(kProcDirectory + kStatFilename,
                                          "processes");
}

// DONE: Read and return the number of running processes
int RunningProcesses() {
    return Helper::ReadValueFromFile<int>(kProcDirectory + kStatFilename,
                                          "procs_running");
}

// DONE: Read and return the number of jiffies for the system
long Jiffies() { return ActiveJiffies() + IdleJiffies(); }

// DONE: Read and return the number of active jiffies for a PID
long ActiveJiffies(int pid) { 
    auto line = Helper::ReadFirstLineFromFile(kProcDirectory + std::to_string(pid) 
        + kStatFilename);
    if (line.empty()) {
        return {};
    }

    std::istringstream ist{line};
    std::string part;
    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    ist >> part;
    // no check value type is string
    char sign;
    ist >> sign;
    if (sign != 'S') {
        return 0;
    }

    for (auto i = 0; i < 10; ++i) {
        ist >> part;
        if (!Helper::IsNumber<long>(part)) {
            return 0;
        }
    }

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
            return 0;
    }
    auto utime = std::stol(part); 

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
            return 0;
    }
    auto stime = std::stol(part); 

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
            return 0;
    }
    auto cutime = std::stol(part); 

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
            return 0;
    }
    auto cstime = std::stol(part); 


    return utime + stime + cutime + cstime; 
}


// DONE: Read and return the number of active jiffies for the system
long ActiveJiffies() {
    std::vector<std::string> values = LinuxParser::CpuUtilization();
    if(values.empty()) {
        return 0;
    }

    auto result = std::stol(values[kUser_]) + std::stol(values[kNice_]) +
            std::stol(values[kSystem_]) + std::stol(values[kIdle_]) +
            std::stol(values[kSoftIRQ_]) + std::stol(values[kSteal_]) +
            std::stol(values[kGuest_]) + std::stol(values[kGuestNice_]);

    return result;
}

// DONE: Read and return the number of idle jiffies for the system
long IdleJiffies() {
    std::vector<std::string> values = LinuxParser::CpuUtilization();
    if(values.empty()) {
        return 0;
    }

    auto result = std::stol(values[kIdle_]) + std::stol(values[kIOwait_]);

    return result;
}

// DONE: Read and return CPU utilization
std::vector<std::string> CpuUtilization() {
    auto line = Helper::ReadFirstLineFromFile(kProcDirectory + kStatFilename);
    if (line.empty()) {
        return {};
    }

    return ParseCPUUtilizationFromLine(line);
}

std::vector<std::string> ParseCPUUtilizationFromLine(const std::string& line) {
    std::istringstream ist{line};
    std::string part;
    ist >> part;
    if (part != "cpu") {
        return {};
    }
    std::vector<std::string> utilisation;
    constexpr auto countOfExpetedParts = 10;
    utilisation.reserve(countOfExpetedParts);
    while (!ist.eof()) {
        ist >> part;
        if (!Helper::IsNumber<long>(part)) {
            return {};
        }
        utilisation.emplace_back(part);
    }
    if (utilisation.size() != countOfExpetedParts) {
        return {};
    }
    return utilisation;
}

// DONE: Read and return the command associated with a process
std::string Command(int pid) {
    std::ifstream ifs{kProcDirectory + std::to_string(pid) + kCmdlineFilename};
    if (ifs.is_open()) {
        std::string line;
        std::getline(ifs, line);
        return line;
    }
    else {
        std::ofstream ofs{"debug.txt", std::ios_base::app};
        ofs << kProcDirectory + std::to_string(pid) + kCmdlineFilename 
            <<"\tCould not be opened\n";
    }

    return std::string();
}

// DONE: Read and return the memory used by a process
// modified the return type from std::string to long since
// we alway return in kB
long RamInKb(int pid) {
    return Helper::ReadValueFromFile<long>(
        kProcDirectory + std::to_string(pid) + kStatusFilename, "VmSize:");
}

// DONE: Read and return the user ID associated with a process
std::string Uid(int pid) {
    return std::to_string(Helper::ReadValueFromFile<long>(
        kProcDirectory + std::to_string(pid) + kStatusFilename, "Uid:"));
}

// DONE: Read and return the user associated with a process
string User(int pid) {
    auto targetUid = Uid(pid);

    std::ifstream ifs{kPasswordPath};
    if (ifs.is_open()) {
        std::string line;

        while (std::getline(ifs, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream ist{line};

            std::string user;
            ist >> user;
            char fill;
            ist >> fill;
            std::string uid;
            ist >> uid;
            if (uid == targetUid && fill == 'x') {
                return user;
            }
        }
    }
    return std::string{};
}

// DONE: Read and return the uptime of a process
long UpTime(int pid) {
    auto line = Helper::ReadFirstLineFromFile(kProcDirectory + 
        std::to_string(pid) + kStatFilename);
    if(line.empty()) {
            std::ofstream ofs{"debug.txt", std::ios_base::app};
        ofs << kProcDirectory + std::to_string(pid) + kCmdlineFilename 
            <<"\tUptime not read\n";
        return 0;
    }

    return ParseProcessUptimeFromLine(line);
}

long ParseProcessUptimeFromLine(const std::string& line)
{
    std::istringstream ist{line};
    std::string part;
    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    ist >> part;
    // no check value type is string
    char sign;
    ist >> sign;
    if (sign != 'S') {
        return 0;
    }

    for (auto i = 0; i < 19; ++i) {
        ist >> part;
        if (!Helper::IsNumber<long>(part)) {
            return 0;
        }
    }
    return ClockTicksToSecond(std::stol(part));
}

long ClockTicksToSecond(long clockTicks) {
    return clockTicks / sysconf(_SC_CLK_TCK);
}

}  // namespace LinuxParser