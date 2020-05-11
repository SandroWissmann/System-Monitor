#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <string>
#include <vector>

namespace Linux::Parser {

// System
std::string OperatingSystem();
std::string Kernel();
std::vector<int> Pids();

long UpTime();
int TotalProcesses();
int RunningProcesses();

}  // namespace Linux::Parser

#endif