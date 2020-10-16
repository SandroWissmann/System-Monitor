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
#include "../include/parser.h"

#include "../include/linux/l_memory.h"
#include "../include/linux/l_parser.h"

namespace Sysmon::Parser {

// System
long UpTime() { return Linux::Parser::UpTime(); }

std::vector<int> Pids() { return Linux::Parser::Pids(); }

int TotalProcesses() { return Linux::Parser::TotalProcesses(); }

int RunningProcesses() { return Linux::Parser::RunningProcesses(); }

std::string OperatingSystem() { return Linux::Parser::OperatingSystem(); }

std::string Kernel() { return Linux::Parser::Kernel(); }

};  // namespace Parser
