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
#ifndef PROCESS_H
#define PROCESS_H

#include <memory>
#include <string>

namespace Sysmon {

class Process {
   public:
    virtual int Pid() const = 0;
    virtual std::string User() const = 0;
    virtual std::string Command() const = 0;
    virtual long RamInMb() const = 0;
    virtual long UpTime() const = 0;
    virtual double CpuUtilization() const = 0;
    bool operator<(const Process& a) const;

    static std::shared_ptr<Process> makeProcess(int pid);
};

}  // namespace Sysmon

#endif