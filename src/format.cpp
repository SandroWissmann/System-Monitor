#include <string>

#include "../include/format.h"

#include <fstream>

namespace Sysmon::Format {

// INPUT: Long measuring seconds
// OUTPUT: HH:MM:SS
std::string ElapsedTime(long seconds) {
    auto minutes = seconds / 60;
    seconds -= minutes * 60;

    auto hours = minutes / 60;
    minutes -= hours * 60;

    if (hours > 99) {
        hours = 99;
    }

    return FillWithNLeadingSigns(std::to_string(hours), 2, '0') + ":" +
           FillWithNLeadingSigns(std::to_string(minutes), 2, '0') + ":" +
           FillWithNLeadingSigns(std::to_string(seconds), 2, '0');
}

std::string FillWithNLeadingSigns(const std::string& s, int minSize,
                                  char sign) {
    auto countOfFills = minSize;
    countOfFills -= static_cast<int>(s.size());
    if (countOfFills > 0) {
        return std::string(static_cast<std::size_t>(countOfFills), sign) + s;
    }
    return s;
}

}  // namespace Format
