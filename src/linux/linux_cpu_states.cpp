#include "linux_cpu_states.h"

#include "../helper.h"

#include <iostream>
#include <regex>

LinuxCpuStates::LinuxCpuStates(long user, long nice, long system, long idle,
                               long iowait, long irq, long softfIrq, long steal,
                               long guest, long guestnice)
    : mUser{user},
      mNice{nice},
      mSystem{system},
      mIdle{idle},
      mIOwait{iowait},
      mIRQ{irq},
      mSoftIRQ{softfIrq},
      mSteal{steal},
      mGuest{guest},
      mGuestNice{guestnice} {}

long LinuxCpuStates::Jiffies() const { return ActiveJiffies() + IdleJiffies(); }

long LinuxCpuStates::ActiveJiffies() const {
    return mUser + mNice + mSystem + mIdle + mSoftIRQ + mSteal + mGuest +
           mGuestNice;
}

long LinuxCpuStates::IdleJiffies() const { return mIdle + mIOwait; }

std::istream& operator>>(std::istream& is, LinuxCpuStates& obj) {
    std::regex regex{R"(cpu(\d+)?)"};

    std::string part;
    is >> part;
    if (!std::regex_match(part, regex)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    std::vector<std::string> utilisation;
    constexpr auto countOfExpetedParts = 10;
    utilisation.reserve(countOfExpetedParts);
    while (!is.eof()) {
        is >> part;
        if (!Helper::IsNumber<long>(part)) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        utilisation.emplace_back(part);
    }
    if (utilisation.size() != countOfExpetedParts) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    obj = LinuxCpuStates{std::stol(utilisation[0]), std::stol(utilisation[1]),
                         std::stol(utilisation[2]), std::stol(utilisation[3]),
                         std::stol(utilisation[4]), std::stol(utilisation[5]),
                         std::stol(utilisation[6]), std::stol(utilisation[7]),
                         std::stol(utilisation[8]), std::stol(utilisation[9])};
    return is;
}