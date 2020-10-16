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
#ifndef LINUX_PROCESSOR_H
#define LUNIX_PROCESSOR_H

#include "../processor.h"
#include "cpu_states.h"

#include <iosfwd>
#include <optional>

namespace Sysmon::Linux {

class Processor : public ::Sysmon::Processor {
   public:
    Processor() = default;
    Processor(const CpuStates& firstCpuState, const CpuStates& secondCpuState,
              const std::vector<CpuStates>& firstCoreStates,
              const std::vector<CpuStates>& secondCoreStates);
    ~Processor() = default;

    double Utilization() const override;
    std::vector<double> CoreUtilizations() const override;
    int CountOfCores() const override;

   private:
    double calcUtilization(const CpuStates& firstState,
                           const CpuStates& secondState) const;

    CpuStates mFirstCpuState{};
    CpuStates mSecondCpuState{};
    std::vector<CpuStates> mFirstCoreStates{};
    std::vector<CpuStates> mSecondCoreStates{};

   public:
    static Processor createFromFile();
    static Processor createFromFile(const std::string& filename);

    static std::optional<std::vector<CpuStates>> readFromFile(
        const std::string& filename);
    static std::optional<CpuStates> parseCpuState(const std::string line);
};

}  // namespace Sysmon::Linux

#endif
