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
#ifndef PROCESSTABLEMODEL_H
#define PROCESSTABLEMODEL_H

#include <QAbstractTableModel>
#include <memory>

namespace Sysmon {

class Process;

class ProcessTableModel : public QAbstractTableModel {
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

QString fillWithNLeadingSigns(const QString &s, int minSize, char sign);

}  // namespace Sysmon

#endif  // PROCESSTABLEMODEL_H
