#include "../../include/linux/l_process.h"

#include "../../include/helper.h"
#include "../../include/parser.h"

#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

namespace Linux {

const std::string kProcDirectory{"/proc/"};
const std::string kStatFilename{"/stat"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kStatusFilename{"/status"};
const std::string kPasswordPath{"/etc/passwd"};

Process::Process(int pid)
    : mPid{pid},
      mUser{ReadUserFromFile(pid)},
      mCommand{ReadCommandFromFile(pid)},
      mRamInMb{ReadRamInKbFromFile(pid) / 1024},
      mUpTime{ReadUpTimeFromFile(pid)},
      mCpuUtilization{calcCpuUtilization(pid, mUpTime)} {}

int Process::Pid() const { return mPid; }

std::string Process::User() const { return mUser; }

std::string Process::Command() const { return mCommand; }

long Process::RamInMb() const { return mRamInMb; }

long Process::UpTime() const { return mUpTime; }

double Process::CpuUtilization() const { return mCpuUtilization; }

double Process::calcCpuUtilization(int pid, int upTimeProcess) {
    auto uptime = Parser::UpTime();

    long startTime = upTimeProcess;
    long elapsedTime = uptime - startTime;

    long totalTime = ClockTicksToSecond(ReadActiveJiffiesFromFile(pid));

    if (elapsedTime == 0) {
        return 0;
    }

    return static_cast<double>(totalTime) / static_cast<double>(elapsedTime);
}

long ReadActiveJiffiesFromFile(int pid) {
    auto line = Helper::ReadFirstLineFromFile(
        kProcDirectory + std::to_string(pid) + kStatFilename);
    if (line.empty()) {
        return {};
    }

    std::istringstream ist{line};
    std::string part;
    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    ist >> part;
    // no check value type is string
    char sign;
    ist >> sign;
    if (sign != 'S') {
        return 0;
    }

    for (auto i = 0; i < 10; ++i) {
        ist >> part;
        if (!Helper::IsNumber<long>(part)) {
            return 0;
        }
    }

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    auto utime = std::stol(part);

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    auto stime = std::stol(part);

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    auto cutime = std::stol(part);

    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    auto cstime = std::stol(part);

    return utime + stime + cutime + cstime;
}

std::string ReadCommandFromFile(int pid) {
    std::ifstream ifs{kProcDirectory + std::to_string(pid) + kCmdlineFilename};
    if (ifs.is_open()) {
        std::string line;
        std::getline(ifs, line);
        return line;
    }
    return std::string();
}

long ReadRamInKbFromFile(int pid) {
    return Helper::ReadValueFromFile<long>(
        kProcDirectory + std::to_string(pid) + kStatusFilename, "VmSize:");
}

std::string Uid(int pid) {
    return std::to_string(Helper::ReadValueFromFile<long>(
        kProcDirectory + std::to_string(pid) + kStatusFilename, "Uid:"));
}

std::string ReadUserFromFile(int pid) {
    auto targetUid = Uid(pid);

    std::ifstream ifs{kPasswordPath};
    if (ifs.is_open()) {
        std::string line;

        while (std::getline(ifs, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream ist{line};

            std::string user;
            ist >> user;
            char fill;
            ist >> fill;
            std::string uid;
            ist >> uid;
            if (uid == targetUid && fill == 'x') {
                return user;
            }
        }
    }
    return std::string{};
}

long ReadUpTimeFromFile(int pid) {
    auto line = Helper::ReadFirstLineFromFile(
        kProcDirectory + std::to_string(pid) + kStatFilename);
    if (line.empty()) {
        return 0;
    }
    return ParseProcessUptimeFromLine(line);
}

long ParseProcessUptimeFromLine(const std::string& line) {
    std::istringstream ist{line};
    std::string part;
    ist >> part;
    if (!Helper::IsNumber<long>(part)) {
        return 0;
    }
    ist >> part;
    // no check value type is string
    char sign;
    ist >> sign;
    if (sign != 'S') {
        return 0;
    }

    for (auto i = 0; i < 19; ++i) {
        ist >> part;
        if (!Helper::IsNumber<long>(part)) {
            return 0;
        }
    }
    return ClockTicksToSecond(std::stol(part));
}

long ClockTicksToSecond(long clockTicks) {
    return clockTicks / sysconf(_SC_CLK_TCK);
}

}  // namespace Linux
