#include "process.h"

#include "linux/process.h"

bool Process::operator<(const Process& a) const {
    return CpuUtilization() < a.CpuUtilization();
}

std::shared_ptr<Process> Process::makeProcess(int pid) {
#ifdef __linux__
    Linux::Process process{pid};
    return std::move(std::make_unique<Linux::Process>(process));
#elif _WIN32
#endif
}
