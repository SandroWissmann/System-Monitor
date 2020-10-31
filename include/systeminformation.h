/* System Monitor
 * Copyright (C) 2020  Sandro Wißmann
 *
 * System Monitor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Monitor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Monitor If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: https://github.com/SandroWissmann/System-Monitor
 */
#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <QObject>
#include <QString>
#include <QVector>

#include "memory.h"
#include "process.h"
#include "processor.h"

namespace Sysmon {

class SystemInformation : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString kernel READ Kernel CONSTANT)
    Q_PROPERTY(QString operatingSystem READ OperatingSystem CONSTANT)

    Q_PROPERTY(double totalUsedMemoryInPercent READ TotalUsedMemoryInPercent
                   NOTIFY DataChanged)
    Q_PROPERTY(double cachedMemoryInPercent READ CachedMemoryInPercent NOTIFY
                   DataChanged)
    Q_PROPERTY(double nonCacheNonBufferMemoryInPercent READ
                   NonCacheNonBufferMemoryInPercent NOTIFY DataChanged)
    Q_PROPERTY(double buffersInPercent READ BuffersInPercent NOTIFY DataChanged)
    Q_PROPERTY(double swapInPercent READ SwapInPercent NOTIFY DataChanged)

    Q_PROPERTY(double cpuUtilizationInPercent READ CpuUtilizationInPercent
                   NOTIFY DataChanged)
    Q_PROPERTY(QVector<double> coreUtilizationsInPercent READ
                   CoreUtilizationsInPercent NOTIFY DataChanged)

    Q_PROPERTY(long UpTime READ UpTime NOTIFY DataChanged)
    Q_PROPERTY(int totalProcesses READ TotalProcesses NOTIFY DataChanged)
    Q_PROPERTY(int runningProcesses READ RunningProcesses NOTIFY DataChanged)

   public:
    explicit SystemInformation(QObject *parent = nullptr);

    QString Kernel() const;
    QString OperatingSystem() const;

    double TotalUsedMemoryInPercent();
    double CachedMemoryInPercent();
    double NonCacheNonBufferMemoryInPercent();
    double BuffersInPercent();
    double SwapInPercent();

    double CpuUtilizationInPercent();
    QVector<double> CoreUtilizationsInPercent();

    long UpTime() const;
    int TotalProcesses() const;
    int RunningProcesses() const;

   signals:
    void DataChanged();

   protected:
    void timerEvent(QTimerEvent *event) override;

   private:
    const QString mKernel;
    const QString mOperatingSystem;

    std::shared_ptr<Processor> mCpu;
    std::shared_ptr<Memory> mMemory;
};

}  // namespace Sysmon

#endif  // SYSTEMINFORMATION_H
