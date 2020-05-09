#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

// Wrapper which should select depending on the compiled os which
// parser to use
// Add for Supporting other OS in the future
namespace Parser {

// System
float MemoryUtilization();

long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::string Command(int pid);
long RamInKb(int pid);
std::string User(int pid);
long UpTime(int pid);

long ClockTicksToSecond(long clockTicks);

};  // namespace Parser
#endif