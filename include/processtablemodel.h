#ifndef PROCESSTABLEMODEL_H
#define PROCESSTABLEMODEL_H

#include <QAbstractTableModel>

#include <memory>

namespace Sysmon{

class Process;

class ProcessTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ProcessTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const override;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QVector<std::shared_ptr<Process>> updateProcesses();

    QVector<std::shared_ptr<Process>> mProcesses = {};
};

QString toFormatedTime(long seconds);

QString fillWithNLeadingSigns(const QString& s, int minSize, char sign);

}

#endif // PROCESSTABLEMODEL_H
