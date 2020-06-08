#include "../../include/linux/l_memory.h"

#include "../../include/helper.h"

#include <fstream>
#include <iostream>

namespace Linux {

const std::string kProcDirectory{"/proc/"};
const std::string kMeminfoFilename{"/meminfo"};

Memory::Memory(long memTotal, long memFree, long buffers, long cached,
               long swapTotal, long swapFree, long shmem, long sReclaimable)
    : mTotalMemory{memTotal},
      mSwapTotal{swapTotal},
      mTotalUsedMemory{memTotal - memFree},
      mCachedMemory{cached + sReclaimable - shmem},
      mNonCacheNonBufferMemory{mTotalUsedMemory - (buffers + mCachedMemory)},
      mBuffers{buffers},
      mSwap{swapTotal - swapFree} {}

double Memory::TotalUsedMemoryInPercent() const {
    double percent = static_cast<double>(mTotalUsedMemory) /
                     static_cast<double>(mTotalMemory);
    return percent;
}

double Memory::NonCacheNonBufferMemoryInPercent() const {
    double percent = static_cast<double>(mNonCacheNonBufferMemory) /
                     static_cast<double>(mTotalMemory);
    return percent;
}

double Memory::BuffersInPercent() const {
    double percent =
        static_cast<double>(mBuffers) / static_cast<double>(mTotalMemory);
    return percent;
}

double Memory::CachedMemoryInPercent() const {
    double percent =
        static_cast<double>(mCachedMemory) / static_cast<double>(mTotalMemory);
    return percent;
}

double Memory::SwapInPercent() const {
    double percent =
        static_cast<double>(mSwap) / static_cast<double>(mSwapTotal);
    return percent;
}

Memory Memory::createFromFile() {
    return createFromFile(kProcDirectory + kMeminfoFilename);
}

Memory Memory::createFromFile(const std::string& filename) {
    Memory memory;
    std::ifstream ifs{filename};
    if (ifs.is_open()) {
        ifs >> memory;
    }
    return memory;
}

std::istream& operator>>(std::istream& is, Memory& obj) {
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

    obj = std::move(Memory{*memTotalOpt, *memFreeOpt, *buffersOpt, *cachedOpt,
                           *swapTotalOpt, *swapFreeOpt, *shmemOpt,
                           *sReclaimableOpt});

    return is;
}

}  // namespace Linux
