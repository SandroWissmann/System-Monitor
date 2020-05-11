#ifndef LINUX_PROCESS_H
#define LINUX_PROCESS_H

#include "../process.h"

#include <string>

class LinuxProcess : public Process {
   public:
    LinuxProcess(int pid);

    int Pid() const override;
    std::string User() const override;
    std::string Command() const override;
    long RamInMb() const override;
    long UpTime() const override;
    float CpuUtilization() const override;

   private:
    float calcCpuUtilization(int pid, int upTimeProcess);

    int mPid;
    std::string mUser;
    std::string mCommand;
    long mRamInMb;
    long mUpTime;
    float mCpuUtilization;
};

#endif