#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include "memory.h"
#include "process.h"
#include "processor.h"

#include <QObject>
#include <QString>

namespace Sysmon{

class SystemInformation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kernel READ Kernel CONSTANT)
    Q_PROPERTY(QString operatingSystem READ OperatingSystem CONSTANT)

    Q_PROPERTY(double totalUsedMemoryInPercent READ TotalUsedMemoryInPercent
               NOTIFY TotalUsedMemoryInPercentChanged)
    Q_PROPERTY(double cachedMemoryInPercent READ CachedMemoryInPercent
               NOTIFY CachedMemoryInPercentChanged)
    Q_PROPERTY(double nonCacheNonBufferMemoryInPercent
               READ NonCacheNonBufferMemoryInPercent
               NOTIFY NonCacheNonBufferMemoryInPercentChanged)

    Q_PROPERTY(double buffersInPercent READ BuffersInPercent
               NOTIFY BuffersInPercentChanged)
    Q_PROPERTY(double swapInPercent READ SwapInPercent
               NOTIFY SwapInPercentChanged)

    Q_PROPERTY(long UpTime READ UpTime NOTIFY UpTimeChanged)
    Q_PROPERTY(int totalProcesses READ TotalProcesses
               NOTIFY TotalProcessesChanged)
    Q_PROPERTY(int runningProcesses READ RunningProcesses
               NOTIFY RunningProcessesChanged)

public:
    explicit SystemInformation(QObject *parent = nullptr);


    QString Kernel() const;
    QString OperatingSystem() const;

    double TotalUsedMemoryInPercent();
    double CachedMemoryInPercent();
    double NonCacheNonBufferMemoryInPercent();
    double BuffersInPercent();
    double SwapInPercent();

    long UpTime() const;
    int TotalProcesses() const;
    int RunningProcesses() const;

signals:
    void TotalUsedMemoryInPercentChanged();
    void CachedMemoryInPercentChanged();
    void NonCacheNonBufferMemoryInPercentChanged();
    void BuffersInPercentChanged();
    void SwapInPercentChanged();

    void UpTimeChanged();
    void TotalProcessesChanged();
    void RunningProcessesChanged();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    const QString mKernel;
    const QString mOperatingSystem;

    std::shared_ptr<Processor> mCpu;
    std::shared_ptr<Memory> mMemory;
};

}

#endif // SYSTEMINFORMATION_H
