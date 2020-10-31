/* System Monitor
 * Copyright (C) 2020  Sandro Wißmann
 *
 * System Monitor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Monitor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Monitor If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/System-Monitor
 */
#ifndef LINUX_PROCESS_H
#define LINUX_PROCESS_H

#include <string>

#include "../process.h"

namespace Sysmon::Linux {

class Process : public ::Sysmon::Process {
   public:
    Process(int pid);

    int Pid() const override;
    std::string User() const override;
    std::string Command() const override;
    long RamInMb() const override;
    long UpTime() const override;
    double CpuUtilization() const override;

   private:
    double calcCpuUtilization(int pid, int upTimeProcess);

    int mPid;
    std::string mUser;
    std::string mCommand;
    long mRamInMb;
    long mUpTime;
    double mCpuUtilization;
};

long ReadActiveJiffiesFromFile(int pid);
std::string ReadCommandFromFile(int pid);
long ReadRamInKbFromFile(int pid);
std::string ReadUidFromFile(int pid);
std::string ReadUserFromFile(int pid);
long ReadUpTimeFromFile(int pid);

long ParseProcessUptimeFromLine(const std::string& line);
long ClockTicksToSecond(long clockTicks);

}  // namespace Sysmon::Linux

#endif
