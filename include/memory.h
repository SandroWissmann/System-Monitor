#ifndef MEMORY_H
#define MEMORY_H

#include <memory>

class Memory {
   public:
    virtual ~Memory() = default;

    virtual float TotalUsedMemoryInPercent() const = 0;
    virtual float CachedMemoryInPercent() const = 0;
    virtual float NonCacheNonBufferMemoryInPercent() const = 0;
    virtual float BuffersInPercent() const = 0;
    virtual float SwapInPercent() const = 0;

    static std::shared_ptr<Memory> makeMemory();
};

#endif