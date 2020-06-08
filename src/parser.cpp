#include "../include/parser.h"

#include "../include/linux/l_memory.h"
#include "../include/linux/l_parser.h"

namespace Parser {

// System
long UpTime() { return Linux::Parser::UpTime(); }

std::vector<int> Pids() { return Linux::Parser::Pids(); }

int TotalProcesses() { return Linux::Parser::TotalProcesses(); }

int RunningProcesses() { return Linux::Parser::RunningProcesses(); }

std::string OperatingSystem() { return Linux::Parser::OperatingSystem(); }

std::string Kernel() { return Linux::Parser::Kernel(); }

};  // namespace Parser
