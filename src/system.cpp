#include "../include/system.h"

#include "../include/parser.h"

#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

namespace Sysmon{

System::System()
    : mKernel{Parser::Kernel()},
      mOperatingSystem{Parser::OperatingSystem()},
      mCpu{std::move(Processor::makeProcessor())},
      mMemory{Memory::makeMemory()},
      mLastCpuTimePoint{std::chrono::system_clock::now()},
      mLastMemoryTimePoint{mLastMemoryTimePoint} {}

std::string System::Kernel() const { return mKernel; }

std::string System::OperatingSystem() const { return mOperatingSystem; }

std::shared_ptr<Processor> System::Cpu() {
    auto newTimePoint = std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        newTimePoint - mLastCpuTimePoint);

    if (duration.count() > mMinReadDifferenceInMS) {
        mCpu = std::move(Processor::makeProcessor());
        mLastCpuTimePoint = newTimePoint;
    }
    return mCpu;
}

std::vector<std::shared_ptr<Process>> System::Processes() {
    auto newTimePoint = std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        newTimePoint - mLastProcessTimePoint);

    if (duration.count() > mMinReadDifferenceInMS) {
        mProcesses = updateProcesses();
        mLastProcessTimePoint = newTimePoint;
    }

    return mProcesses;
}

// DONE: Return the system's memory utilization
std::shared_ptr<Memory> System::MemoryUtilization() {
    auto newTimePoint = std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        newTimePoint - mLastMemoryTimePoint);

    if (duration.count() > mMinReadDifferenceInMS) {
        mMemory = std::move(Memory::makeMemory());
        mLastMemoryTimePoint = newTimePoint;
    }
    return mMemory;
}

// DONE: Return the number of seconds since the system started running
long System::UpTime() const { return Parser::UpTime(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() const { return Parser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() const { return Parser::TotalProcesses(); }

std::vector<std::shared_ptr<Process>> System::updateProcesses() {
    auto pids = Parser::Pids();

    std::vector<std::shared_ptr<Process>> processes;

    processes.reserve(pids.size());

    for (const auto& pid : pids) {
        processes.emplace_back(std::move(Process::makeProcess(pid)));
    }

    auto comparator = [](const std::shared_ptr<Process>& a,
                         const std::shared_ptr<Process>& b) { return *b < *a; };

    std::sort(processes.begin(), processes.end(), comparator);

    return processes;
}

}
