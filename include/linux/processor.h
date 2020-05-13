#ifndef LINUX_PROCESSOR_H
#define LUNIX_PROCESSOR_H

#include "../processor.h"
#include "cpu_states.h"

#include <iosfwd>
#include <optional>

namespace Linux {

class Processor : public ::Processor {
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

}  // namespace Linux

#endif