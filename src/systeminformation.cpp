/* System Monitor
 * Copyright (C) 2020  Sandro Wißmann
 *
 * Minefield is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Minefield is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Monitor If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/System-Monitor
 */
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
