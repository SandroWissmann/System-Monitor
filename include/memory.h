#ifndef MEMORY_H
#define MEMORY_H

#include <memory>

class Memory {
   public:
    virtual ~Memory() = default;

    virtual double TotalUsedMemoryInPercent() const = 0;
    virtual double CachedMemoryInPercent() const = 0;
    virtual double NonCacheNonBufferMemoryInPercent() const = 0;
    virtual double BuffersInPercent() const = 0;
    virtual double SwapInPercent() const = 0;

    static std::shared_ptr<Memory> makeMemory();
};

#endif