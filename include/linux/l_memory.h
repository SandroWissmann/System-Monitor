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
