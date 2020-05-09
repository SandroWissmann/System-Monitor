#include "parser.h"

#include "linux_parser.h"

namespace Parser {

// System
float MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

long UpTime() { return LinuxParser::UpTime(); }

std::vector<int> Pids() { return LinuxParser::Pids(); }

int TotalProcesses() { return LinuxParser::TotalProcesses(); }

int RunningProcesses() { return LinuxParser::RunningProcesses(); }

std::string OperatingSystem() { return LinuxParser::OperatingSystem(); }

std::string Kernel() { return LinuxParser::Kernel(); }

std::vector<std::string> CpuUtilization() {
    return LinuxParser::CpuUtilization();
}

long Jiffies() { return LinuxParser::Jiffies(); }

long ActiveJiffies() { return LinuxParser::ActiveJiffies(); }

long ActiveJiffies(int pid) { return LinuxParser::ActiveJiffies(pid); }

long IdleJiffies() { return LinuxParser::IdleJiffies(); }

std::string Command(int pid) { return LinuxParser::Command(pid); }

long RamInKb(int pid) { return LinuxParser::RamInKb(pid); }

std::string User(int pid) { return LinuxParser::User(pid); }

long UpTime(int pid) { return LinuxParser::UpTime(pid); }

long ClockTicksToSecond(long clockTicks)
{
    return LinuxParser::ClockTicksToSecond(clockTicks);
}

};  // namespace Parser