#include "memory"

#include "linux/linux_memory.h"

std::shared_ptr<Memory> Memory::makeMemory() {
#ifdef __linux__
    LinuxMemory memory = LinuxMemory::createFromFile();
    return std::move(std::make_unique<LinuxMemory>(memory));
#elif _WIN32
#endif
}