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

#ifndef LINUX_MEMORY_H
#define LINUX_MEMORY_H

#include "../memory.h"

#include <iosfwd>

namespace Sysmon::Linux {

class Memory : public ::Sysmon::Memory {
   public:
    Memory() = default;
    Memory(long memTotal, long memFree, long buffers, long cached,
           long swapTotal, long swapFree, long shmem, long sReclaimable);
    ~Memory() = default;

    double TotalUsedMemoryInPercent() const override;
    double CachedMemoryInPercent() const override;
    double NonCacheNonBufferMemoryInPercent() const override;
    double BuffersInPercent() const override;
    double SwapInPercent() const override;

   private:
    long mTotalMemory = 0;
    long mSwapTotal = 0;
    long mTotalUsedMemory = 0;
    long mCachedMemory = 0;
    long mNonCacheNonBufferMemory = 0;
    long mBuffers = 0;
    long mSwap = 0;

   public:
    static Memory createFromFile();
    static Memory createFromFile(const std::string& filename);
};

std::istream& operator>>(std::istream& is, Memory& obj);

}  // namespace Sysmon::Linux

#endif
