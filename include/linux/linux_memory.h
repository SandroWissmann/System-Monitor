#ifndef LINUX_MEMORY_H
#define LINUX_MEMORY_H

#include "../memory.h"

#include <iosfwd>

class LinuxMemory : public Memory {
   public:
    LinuxMemory() = default;
    LinuxMemory(long memTotal, long memFree, long buffers, long cached,
                long swapTotal, long swapFree, long shmem, long sReclaimable);
    ~LinuxMemory() = default;

    float TotalUsedMemoryInPercent() const override;
    float CachedMemoryInPercent() const override;
    float NonCacheNonBufferMemoryInPercent() const override;
    float BuffersInPercent() const override;
    float SwapInPercent() const override;

   private:
    long mTotalMemory = 0;
    long mSwapTotal = 0;
    long mTotalUsedMemory = 0;
    long mCachedMemory = 0;
    long mNonCacheNonBufferMemory = 0;
    long mBuffers = 0;
    long mSwap = 0;

   public:
    static LinuxMemory createFromFile();
    static LinuxMemory createFromFile(const std::string& filename);
};

std::istream& operator>>(std::istream& is, LinuxMemory& obj);

#endif