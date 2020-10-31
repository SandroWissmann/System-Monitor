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

#ifndef LINUX_CPU_STATES_H
#define LINUX_CPU_STATES_H

#include <iosfwd>

namespace Sysmon::Linux {

class CpuStates {
   public:
    CpuStates() = default;
    CpuStates(long user, long nice, long system, long idle, long iowait,
              long irq, long softfIrq, long steal, long guest, long guestnice);

    long Jiffies() const;
    long ActiveJiffies() const;
    long IdleJiffies() const;

   private:
    long mUser = 0;
    long mNice = 0;
    long mSystem = 0;
    long mIdle = 0;
    long mIOwait = 0;
    long mIRQ = 0;
    long mSoftIRQ = 0;
    long mSteal = 0;
    long mGuest = 0;
    long mGuestNice = 0;
};

std::istream& operator>>(std::istream& is, CpuStates& obj);

}  // namespace Sysmon::Linux

#endif
