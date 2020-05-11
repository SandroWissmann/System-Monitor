#include "linux_memory.h"

#include "../helper.h"

#include <fstream>
#include <iostream>

const std::string kProcDirectory{"/proc/"};
const std::string kMeminfoFilename{"/meminfo"};

/*
Total used memory = MemTotal - MemFree
Non cache/buffer memory (green) =
    Total used memory - (Buffers + Cached memory)
Buffers (blue) = Buffers
Cached memory (yellow) = Cached + SReclaimable - Shmem
Swap = SwapTotal - SwapFree
*/

LinuxMemory::LinuxMemory(long memTotal, long memFree, long buffers, long cached,
                         long swapTotal, long swapFree, long shmem,
                         long sReclaimable)
    : mTotalMemory{memTotal},
      mSwapTotal{swapTotal},
      mTotalUsedMemory{memTotal - memFree},
      mCachedMemory{cached + sReclaimable - shmem},
      mNonCacheNonBufferMemory{mTotalUsedMemory - (buffers + mCachedMemory)},
      mBuffers{buffers},
      mSwap{swapTotal - swapFree} {}

float LinuxMemory::TotalUsedMemoryInPercent() const {
    float percent =
        static_cast<float>(mTotalUsedMemory) / static_cast<float>(mTotalMemory);
    return percent;
}

float LinuxMemory::NonCacheNonBufferMemoryInPercent() const {
    float percent = static_cast<float>(mNonCacheNonBufferMemory) /
                    static_cast<float>(mTotalMemory);
    return percent;
}

float LinuxMemory::BuffersInPercent() const {
    float percent =
        static_cast<float>(mBuffers) / static_cast<float>(mTotalMemory);
    return percent;
}

float LinuxMemory::CachedMemoryInPercent() const {
    float percent =
        static_cast<float>(mCachedMemory) / static_cast<float>(mTotalMemory);
    return percent;
}

float LinuxMemory::SwapInPercent() const {
    float percent = static_cast<float>(mSwap) / static_cast<float>(mSwapTotal);
    return percent;
}

LinuxMemory LinuxMemory::createFromFile() {
    return createFromFile(kProcDirectory + kMeminfoFilename);
}

LinuxMemory LinuxMemory::createFromFile(const std::string& filename) {
    LinuxMemory memory;
    std::ifstream ifs{filename};
    if (ifs.is_open()) {
        ifs >> memory;
    }
    return memory;
}

std::istream& operator>>(std::istream& is, LinuxMemory& obj) {
    std::string line;
    std::getline(is, line);
    auto memTotalOpt = Helper::ReadValueFromLine<long>(line, "MemTotal:");
    if (!memTotalOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    std::getline(is, line);
    auto memFreeOpt = Helper::ReadValueFromLine<long>(line, "MemFree:");
    if (!memFreeOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    std::getline(is, line);  // MemAvailable:
    std::getline(is, line);
    auto buffersOpt = Helper::ReadValueFromLine<long>(line, "Buffers:");
    if (!buffersOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    std::getline(is, line);
    auto cachedOpt = Helper::ReadValueFromLine<long>(line, "Cached:");
    if (!cachedOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    for (int i = 0; i < 9; ++i) {
        std::getline(is, line);
    }
    std::getline(is, line);
    auto swapTotalOpt = Helper::ReadValueFromLine<long>(line, "SwapTotal:");
    if (!swapTotalOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    std::getline(is, line);
    auto swapFreeOpt = Helper::ReadValueFromLine<long>(line, "SwapFree:");
    if (!swapFreeOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    for (int i = 0; i < 4; ++i) {
        std::getline(is, line);
    }
    std::getline(is, line);
    auto shmemOpt = Helper::ReadValueFromLine<long>(line, "Shmem:");
    if (!shmemOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    for (int i = 0; i < 2; ++i) {
        std::getline(is, line);
    }
    std::getline(is, line);
    auto sReclaimableOpt =
        Helper::ReadValueFromLine<long>(line, "SReclaimable:");
    if (!sReclaimableOpt) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    obj = std::move(LinuxMemory{*memTotalOpt, *memFreeOpt, *buffersOpt,
                                *cachedOpt, *swapTotalOpt, *swapFreeOpt,
                                *shmemOpt, *sReclaimableOpt});

    return is;
}
