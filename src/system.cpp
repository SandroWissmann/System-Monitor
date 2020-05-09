#include <unistd.h>
#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "parser.h"

#include <iostream>
#include <fstream>

System::System()
    : mKernel{Parser::Kernel()},
      mOperatingSystem{Parser::OperatingSystem()},
      mCpu{Processor{}} {}

// TODO: Return the system's CPU
Processor& System::Cpu() { return mCpu; }

// TODO: Return a container composed of the system's processes
std::vector<Process>& System::Processes() {
    
    mProcesses.clear();

    auto pids = Parser::Pids();
    mPids = pids;

    mProcesses.reserve(pids.size());

    for (const auto& pid : pids) {
        if(pid > 32768 || pid < 0) {
            std::cout << pid<<'\n';
        }

        Process process{pid};
        mProcesses.emplace_back(process);
    }

    std::sort(mProcesses.begin(), mProcesses.end());

    return mProcesses;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() const { return mKernel; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() const { 
    return Parser::MemoryUtilization(); 
}

// DONE: Return the operating system name
std::string System::OperatingSystem() const { return mOperatingSystem; }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() const { return Parser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() const { return Parser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() const { return Parser::UpTime(); }