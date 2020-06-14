#include "../include/processtablemodel.h"

#include "../include/process.h"
#include "../include/parser.h"

namespace Sysmon{

static constexpr auto pidColumn = 0;
static constexpr auto userColumn = 1;
static constexpr auto cpuUtilizationColumn = 2;
static constexpr auto ramInMbColumn = 3;
static constexpr auto upTimeColumn = 4;
static constexpr auto commandColumn = 5;

ProcessTableModel::ProcessTableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    mProcesses = updateProcesses();
    startTimer(std::chrono::milliseconds{1000});
}

int ProcessTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mProcesses.size();
}

int ProcessTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (commandColumn + 1);
}

QVariant ProcessTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        switch(index.column()) {
        case pidColumn:
            return mProcesses[index.row()]->Pid();
        case userColumn:
            return QString::fromStdString(mProcesses[index.row()]->User());
        case cpuUtilizationColumn: {
            auto utilization = mProcesses[index.row()]->CpuUtilization();
            utilization *=100;
            return QString::number(utilization, 'f', 2);
        }
        case ramInMbColumn:
            return static_cast<long long>(mProcesses[index.row()]->RamInMb());
        case upTimeColumn:
            return toFormatedTime(mProcesses[index.row()]->UpTime());
        case commandColumn:
            return QString::fromStdString(mProcesses[index.row()]->Command());
        }
    }
    return QVariant{};
}

QVariant ProcessTableModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
    if(orientation == Qt::Orientation::Vertical) {
        return QVariant{};
    }

    if(role == Qt::DisplayRole) {
        switch(section) {
        case pidColumn:
            return tr("PID");
        case userColumn:
            return tr("USER");
        case cpuUtilizationColumn:
            return tr("CPU[%]");
        case ramInMbColumn:
            return tr("RAM[MB]");
        case upTimeColumn:
            return tr("TIME+");
        case commandColumn:
            return tr("COMMAND");
        }
    }
    return QVariant{};
}

void ProcessTableModel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    beginResetModel();
    mProcesses = updateProcesses();
    endResetModel();
}

QVector<std::shared_ptr<Process> > ProcessTableModel::updateProcesses()
{
    auto pids = Parser::Pids();

    QVector<std::shared_ptr<Process>> processes;

    processes.reserve(pids.size());

    for (const auto& pid : pids) {
        processes.push_back(Process::makeProcess(pid));
    }

    auto comparator = [](const std::shared_ptr<Process>& a,
                         const std::shared_ptr<Process>& b) { return *b < *a; };

    std::sort(processes.begin(), processes.end(), comparator);

    return processes;
}

QString toFormatedTime(long seconds)
{
    auto minutes = seconds / 60;
    seconds -= minutes * 60;

    auto hours = minutes / 60;
    minutes -= hours * 60;

    if (hours > 99) {
        hours = 99;
    }

    return fillWithNLeadingSigns(QString::number(hours), 2, '0') + ":" +
           fillWithNLeadingSigns(QString::number(minutes), 2, '0') + ":" +
           fillWithNLeadingSigns(QString::number(seconds), 2, '0');
}

QString fillWithNLeadingSigns(const QString& s, int minSize, char sign)
{
    auto countOfFills = minSize;
    countOfFills -= static_cast<int>(s.size());
    if (countOfFills > 0) {
        return QString(static_cast<std::size_t>(countOfFills), sign) + s;
    }
    return s;
}

}
