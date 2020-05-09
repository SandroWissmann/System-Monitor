#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
std::string OperatingSystem();
std::string Kernel();
std::vector<int> Pids();

float MemoryUtilization();
long UpTime();
int TotalProcesses();
int RunningProcesses();

// CPU
enum CPUStates {
    kUser_ = 0,
    kNice_,
    kSystem_,
    kIdle_,
    kIOwait_,
    kIRQ_,
    kSoftIRQ_,
    kSteal_,
    kGuest_,
    kGuestNice_
};

long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();
std::vector<std::string> CpuUtilization();

std::vector<std::string> ParseCPUUtilizationFromLine(
    const std::string& line);

// Processes
std::string Command(int pid);
long RamInKb(int pid);
std::string Uid(int pid);
std::string User(int pid);
long UpTime(int pid);

long ParseProcessUptimeFromLine(const std::string& line);
long ClockTicksToSecond(long clockTicks);



};  // namespace LinuxParser

#endif