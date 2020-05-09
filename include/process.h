#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
    Process(int pid);

    int Pid() const;
    std::string User() const;
    std::string Command() const;
    float CpuUtilization() const;
    std::string RamInMb() const;
    long int UpTime() const;
    bool operator<(Process const& a) const;

private:
    int mPid;
    std::string mUser;
    std::string mCommand;
};

#endif