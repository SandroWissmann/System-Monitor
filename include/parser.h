#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

// Wrapper which should select depending on the compiled os which
// parser to use
// Add for Supporting other OS in the future

namespace Sysmon::Parser {

// System

long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

};  // namespace Parser
#endif