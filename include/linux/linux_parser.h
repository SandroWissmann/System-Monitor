#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <string>
#include <vector>

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

long UpTime();
int TotalProcesses();
int RunningProcesses();

// Processes
long ActiveJiffies(int pid);
std::string Command(int pid);
long RamInKb(int pid);
std::string Uid(int pid);
std::string User(int pid);
long UpTime(int pid);

long ParseProcessUptimeFromLine(const std::string& line);
long ClockTicksToSecond(long clockTicks);

};  // namespace LinuxParser

#endif