#ifndef LINUX_PROCESS_H
#define LINUX_PROCESS_H

#include "../process.h"

#include <string>

namespace Sysmon::Linux {

class Process : public ::Sysmon::Process {
   public:
    Process(int pid);

    int Pid() const override;
    std::string User() const override;
    std::string Command() const override;
    long RamInMb() const override;
    long UpTime() const override;
    double CpuUtilization() const override;

   private:
    double calcCpuUtilization(int pid, int upTimeProcess);

    int mPid;
    std::string mUser;
    std::string mCommand;
    long mRamInMb;
    long mUpTime;
    double mCpuUtilization;
};

long ReadActiveJiffiesFromFile(int pid);
std::string ReadCommandFromFile(int pid);
long ReadRamInKbFromFile(int pid);
std::string ReadUidFromFile(int pid);
std::string ReadUserFromFile(int pid);
long ReadUpTimeFromFile(int pid);

long ParseProcessUptimeFromLine(const std::string& line);
long ClockTicksToSecond(long clockTicks);

}  // namespace Linux

#endif
