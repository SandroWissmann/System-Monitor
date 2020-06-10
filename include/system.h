#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include <chrono>
#include <memory>

#include "memory.h"
#include "process.h"
#include "processor.h"

namespace Sysmon{

class System {
   public:
    System();

    std::string Kernel() const;
    std::string OperatingSystem() const;

    std::shared_ptr<Processor> Cpu();
    std::vector<std::shared_ptr<Process>> Processes();
    std::shared_ptr<Memory> MemoryUtilization();
    long UpTime() const;
    int TotalProcesses() const;
    int RunningProcesses() const;

   private:
    std::vector<std::shared_ptr<Process>> updateProcesses();

    const std::string mKernel;
    const std::string mOperatingSystem;

    std::shared_ptr<Processor> mCpu;
    std::shared_ptr<Memory> mMemory;
    std::vector<std::shared_ptr<Process>> mProcesses = {};

    std::chrono::time_point<std::chrono::system_clock> mLastCpuTimePoint{};
    std::chrono::time_point<std::chrono::system_clock> mLastMemoryTimePoint{};
    std::chrono::time_point<std::chrono::system_clock> mLastProcessTimePoint{};
    static constexpr auto mMinReadDifferenceInMS = 100;
};

}

#endif