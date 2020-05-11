#ifndef LINUX_PROCESSOR_H
#define LUNIX_PROCESSOR_H

#include "linux_cpu_states.h"
#include "../processor.h"

#include <iosfwd>
#include <optional>

class LinuxProcessor : public Processor {
   public:
    LinuxProcessor() = default;
    LinuxProcessor(const LinuxCpuStates& firstCpuState,
                   const LinuxCpuStates& secondCpuState,
                   const std::vector<LinuxCpuStates>& firstCoreStates,
                   const std::vector<LinuxCpuStates>& secondCoreStates);
    ~LinuxProcessor() = default;

    float Utilization() const override;
    std::vector<float> CoreUtilizations() const override;
    int CountOfCores() const override;

   private:
    float calcUtilization(const LinuxCpuStates& firstState,
                          const LinuxCpuStates& secondState) const;

    LinuxCpuStates mFirstCpuState{};
    LinuxCpuStates mSecondCpuState{};
    std::vector<LinuxCpuStates> mFirstCoreStates{};
    std::vector<LinuxCpuStates> mSecondCoreStates{};

   public:
    static LinuxProcessor createFromFile();
    static LinuxProcessor createFromFile(const std::string& filename);

    static std::optional<std::vector<LinuxCpuStates>> readFromFile(
        const std::string& filename);
    static std::optional<LinuxCpuStates> parseCpuState(const std::string line);
};

#endif