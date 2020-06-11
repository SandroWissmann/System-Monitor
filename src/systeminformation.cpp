#include "../include/systeminformation.h"

#include "../include/parser.h"

namespace Sysmon{

SystemInformation::SystemInformation(QObject *parent)
    : QObject(parent),
      mKernel{QString::fromStdString(Parser::Kernel())},
      mOperatingSystem{QString::fromStdString(Parser::OperatingSystem())},
      mCpu{Processor::makeProcessor()},
      mMemory{Memory::makeMemory()}
{
    startTimer(std::chrono::milliseconds{1000});
}

QString SystemInformation::Kernel() const
{
    return mKernel;
}

QString SystemInformation::OperatingSystem() const
{
    return mOperatingSystem;
}

double SystemInformation::TotalUsedMemoryInPercent()
{
    return mMemory->TotalUsedMemoryInPercent() * 100.0;
}

double SystemInformation::CachedMemoryInPercent()
{
    return mMemory->CachedMemoryInPercent() * 100.0;
}

double SystemInformation::NonCacheNonBufferMemoryInPercent()
{
    return
        mMemory->NonCacheNonBufferMemoryInPercent() * 100.0;
}

double SystemInformation::BuffersInPercent()
{
    return mMemory->BuffersInPercent() * 100.0;
}

double SystemInformation::SwapInPercent()
{
    return mMemory->SwapInPercent() * 100.0;
}

double SystemInformation::CpuUtilizationInPercent()
{
    return mCpu->Utilization() * 100;
}

QVector<double> SystemInformation::CoreUtilizationsInPercent()
{
    auto coreUtilizations = mCpu->CoreUtilizations();
    for(auto &coreUtilization : coreUtilizations) {
        coreUtilization *= 100;
    }
    return QVector<double>(coreUtilizations.begin(), coreUtilizations.end());
}

long SystemInformation::UpTime() const
{
    return Parser::UpTime();
}

int SystemInformation::TotalProcesses() const
{
    return Parser::TotalProcesses();
}

int SystemInformation::RunningProcesses() const
{
    return Parser::RunningProcesses();
}

void SystemInformation::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    mCpu = Processor::makeProcessor();
    mMemory = Memory::makeMemory();

    emit DataChanged();
}


}
