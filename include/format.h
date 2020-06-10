#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Sysmon::Format {
std::string ElapsedTime(long seconds);

std::string FillWithNLeadingSigns(const std::string& s, int minSize, char sign);

};  // namespace Format

#endif