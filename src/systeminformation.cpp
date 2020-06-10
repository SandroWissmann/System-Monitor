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
