#include "process.h"

#include "linux/linux_process.h"

bool Process::operator<(const Process& a) const {
    return CpuUtilization() < a.CpuUtilization();
}

std::shared_ptr<Process> Process::makeProcess(int pid) {
#ifdef __linux__
    LinuxProcess process{pid};
    return std::move(std::make_unique<LinuxProcess>(process));
#elif _WIN32
#endif
}