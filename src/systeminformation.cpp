#include "../include/systeminformation.h"

namespace Sysmon{

SystemInformation::SystemInformation(QObject *parent)
    : QObject(parent),
      mSystem{System{}}
{
}

QString SystemInformation::Kernel() const
{
    return QString::fromUtf8(mSystem.Kernel().data(), mSystem.Kernel().size());
}

QString SystemInformation::OperatingSystem() const
{
    return QString::fromUtf8(mSystem.OperatingSystem().data(),
                             mSystem.OperatingSystem().size());
}

double SystemInformation::TotalUsedMemoryInPercent()
{
    return mSystem.MemoryUtilization()->TotalUsedMemoryInPercent() * 100.0;
}

double SystemInformation::CachedMemoryInPercent()
{
    return mSystem.MemoryUtilization()->CachedMemoryInPercent() * 100.0;
}

double SystemInformation::NonCacheNonBufferMemoryInPercent()
{
    return
        mSystem.MemoryUtilization()->NonCacheNonBufferMemoryInPercent() * 100.0;
}

double SystemInformation::BuffersInPercent()
{
    return mSystem.MemoryUtilization()->BuffersInPercent() * 100.0;
}

double SystemInformation::SwapInPercent()
{
    return mSystem.MemoryUtilization()->SwapInPercent() * 100.0;
}

long SystemInformation::UpTime() const
{
    return mSystem.UpTime();
}

int SystemInformation::TotalProcesses() const
{
    return mSystem.TotalProcesses();
}

int SystemInformation::RunningProcesses() const
{
    return mSystem.RunningProcesses();
}


}
