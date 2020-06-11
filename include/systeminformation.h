#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <QObject>
#include <QString>

#include "system.h"

namespace Sysmon{

class SystemInformation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString kernel READ Kernel CONSTANT)
    Q_PROPERTY(QString operatingSystem READ OperatingSystem CONSTANT)
    Q_PROPERTY(long UpTime READ UpTime CONSTANT)

    Q_PROPERTY(double totalUsedMemoryInPercent READ TotalUsedMemoryInPercent
               CONSTANT)
    Q_PROPERTY(double cachedMemoryInPercent READ CachedMemoryInPercent
               CONSTANT)
    Q_PROPERTY(double nonCacheNonBufferMemoryInPercent READ
               NonCacheNonBufferMemoryInPercent CONSTANT)
    Q_PROPERTY(double buffersInPercent READ BuffersInPercent CONSTANT)
    Q_PROPERTY(double swapInPercent READ SwapInPercent CONSTANT)

    Q_PROPERTY(int totalProcesses READ TotalProcesses CONSTANT)
    Q_PROPERTY(int runningProcesses READ RunningProcesses CONSTANT)

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


private:
    System mSystem;

};

}

#endif // SYSTEMINFORMATION_H
