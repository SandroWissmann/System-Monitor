#ifndef LINUX_CPU_STATES_H
#define LINUX_CPU_STATES_H

#include <iosfwd>

namespace Sysmon::Linux {

class CpuStates {
   public:
    CpuStates() = default;
    CpuStates(long user, long nice, long system, long idle, long iowait,
              long irq, long softfIrq, long steal, long guest, long guestnice);

    long Jiffies() const;
    long ActiveJiffies() const;
    long IdleJiffies() const;

   private:
    long mUser = 0;
    long mNice = 0;
    long mSystem = 0;
    long mIdle = 0;
    long mIOwait = 0;
    long mIRQ = 0;
    long mSoftIRQ = 0;
    long mSteal = 0;
    long mGuest = 0;
    long mGuestNice = 0;
};

std::istream& operator>>(std::istream& is, CpuStates& obj);

}  // namespace Sysmon::Linux

#endif
