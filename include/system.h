#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
   public:
    System();

    Processor& Cpu();
    std::vector<Process>& Processes();
    float MemoryUtilization() const;
    long UpTime() const;
    int TotalProcesses() const;
    int RunningProcesses() const;
    std::string Kernel() const;
    std::string OperatingSystem() const;

   private:
    const std::string mKernel;
    const std::string mOperatingSystem;
    Processor mCpu = {};
    std::vector<Process> mProcesses = {};
    std::vector<int> mPids;
};

#endif