#include "linux_process.h"

#include "linux_parser.h"

LinuxProcess::LinuxProcess(int pid)
    : mPid{pid},
      mUser{LinuxParser::User(pid)},
      mCommand{LinuxParser::Command(pid)},
      mRamInMb{LinuxParser::RamInKb(pid) / 1024},
      mUpTime{LinuxParser::UpTime(pid)},
      mCpuUtilization{calcCpuUtilization(pid, mUpTime)} {}

int LinuxProcess::Pid() const { return mPid; }

std::string LinuxProcess::User() const { return mUser; }

std::string LinuxProcess::Command() const { return mCommand; }

long LinuxProcess::RamInMb() const { return mRamInMb; }

long LinuxProcess::UpTime() const { return mUpTime; }

float LinuxProcess::CpuUtilization() const { return mCpuUtilization; }

float LinuxProcess::calcCpuUtilization(int pid, int upTimeProcess) {
    auto uptime = LinuxParser::UpTime();

    long startTime = upTimeProcess;
    long elapsedTime = uptime - startTime;

    long totalTime =
        LinuxParser::ClockTicksToSecond(LinuxParser::ActiveJiffies(pid));

    if (elapsedTime == 0) {
        return 0;
    }

    return static_cast<float>(totalTime) / static_cast<float>(elapsedTime);
}