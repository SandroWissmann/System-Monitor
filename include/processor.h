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
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <memory>
#include <vector>

namespace Sysmon {

class Processor {
   public:
    virtual ~Processor() = default;
    virtual double Utilization() const = 0;
    virtual std::vector<double> CoreUtilizations() const = 0;
    virtual int CountOfCores() const = 0;

    static std::shared_ptr<Processor> makeProcessor();
};

}  // namespace Sysmon

#endif
