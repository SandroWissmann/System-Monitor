#include "parser.h"

#include "linux/memory.h"
#include "linux/parser.h"

namespace Parser {

// System
long UpTime() { return Linux::Parser::UpTime(); }

std::vector<int> Pids() { return Linux::Parser::Pids(); }

int TotalProcesses() { return Linux::Parser::TotalProcesses(); }

int RunningProcesses() { return Linux::Parser::RunningProcesses(); }

std::string OperatingSystem() { return Linux::Parser::OperatingSystem(); }

std::string Kernel() { return Linux::Parser::Kernel(); }

};  // namespace Parser