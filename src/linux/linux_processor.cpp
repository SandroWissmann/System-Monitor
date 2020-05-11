#include "linux_processor.h"

#include "linux_cpu_states.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

const std::string kProcDirectory{"/proc/"};
const std::string kStatFilename{"/stat"};

LinuxProcessor::LinuxProcessor(
    const LinuxCpuStates& firstCpuState, const LinuxCpuStates& secondCpuState,
    const std::vector<LinuxCpuStates>& firstCoreStates,
    const std::vector<LinuxCpuStates>& secondCoreStates)
    : mFirstCpuState{firstCpuState},
      mSecondCpuState{secondCpuState},
      mFirstCoreStates{firstCoreStates},
      mSecondCoreStates{secondCoreStates} {


          assert(firstCoreStates.size() == secondCoreStates.size());
      }

// DONE: Return the aggregate CPU utilization
float LinuxProcessor::Utilization() const {
    return calcUtilization(mFirstCpuState, mSecondCpuState);
}

std::vector<float> LinuxProcessor::CoreUtilizations() const {
    std::vector<float> coreUtilizations;
    coreUtilizations.reserve(mFirstCoreStates.size());

    for (std::size_t i=0; i < mFirstCoreStates.size(); ++i) {
        coreUtilizations.emplace_back(calcUtilization(mFirstCoreStates[i], mSecondCoreStates[i]));
    }
    return coreUtilizations;
}

int LinuxProcessor::CountOfCores() const { return mFirstCoreStates.size(); }

float LinuxProcessor::calcUtilization(const LinuxCpuStates& firstState,
                                      const LinuxCpuStates& secondState) const {
    float deltaTotalTime = secondState.Jiffies() - firstState.Jiffies();
    float deltaActiveTime =
        secondState.ActiveJiffies() - firstState.ActiveJiffies();
    return deltaActiveTime / deltaTotalTime;
}

LinuxProcessor LinuxProcessor::createFromFile() {
    return createFromFile(kProcDirectory + kStatFilename);
}

LinuxProcessor LinuxProcessor::createFromFile(const std::string& filename) {
    auto firstStates = readFromFile(filename);
    if (!firstStates) {
        return LinuxProcessor{};
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto secondStates = readFromFile(filename);
    if (!secondStates) {
        return LinuxProcessor{};
    }

    auto firstCpuState = firstStates->front();
    auto firstCoreStates = std::vector<LinuxCpuStates>{
        firstStates.value().begin() + 1, firstStates.value().end()};

    auto secondCpuState = secondStates->front();
    auto secondCoreStates = std::vector<LinuxCpuStates>{
        secondStates.value().begin() + 1, secondStates.value().end()};

    return LinuxProcessor{firstCpuState, secondCpuState, firstCoreStates,
                          secondCoreStates};
}

std::optional<std::vector<LinuxCpuStates>> LinuxProcessor::readFromFile(
    const std::string& filename) {
    std::ifstream ifs{filename};
    if (!ifs.is_open()) {
        return {};
    }

    std::string line;
    // Assume there must be also the CPUState
    std::getline(ifs, line);
    auto optCpuState = parseCpuState(line);
    if (!optCpuState) {
        return {};
    }
    // Assume there must be atleast one CoreState
    std::getline(ifs, line);
    auto optCoreState = parseCpuState(line);
    if (!optCoreState) {
        return {};
    }
    // optional cores
    std::vector<LinuxCpuStates> states;
    states.emplace_back(*optCpuState);
    states.emplace_back(*optCoreState);

    while (std::getline(ifs, line)) {
        auto optNextCoreState = parseCpuState(line);
        if (!optNextCoreState) {
            break;
        }
        states.emplace_back(*optNextCoreState);
    }
    return {states};
}

std::optional<LinuxCpuStates> LinuxProcessor::parseCpuState(
    const std::string line) {
    LinuxCpuStates cpuStates;
    std::istringstream ist{line};
    ist >> cpuStates;
    if (ist.fail()) {
        return {};
    }
    return {cpuStates};
}