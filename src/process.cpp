#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

#include "parser.h"

#include <fstream>

Process::Process(int pid)
    : mPid{pid}, mUser{Parser::User(pid)}, 
    mCommand{Parser::Command(pid)} 
    {      
    }

// DONE: Return this process's ID
int Process::Pid() const { return mPid; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    
    auto uptime = Parser::UpTime();

    long startTime = Parser::UpTime(Pid());
    long elapsedTime = uptime -  startTime;

    long totalTime = Parser::ClockTicksToSecond(
        Parser::ActiveJiffies(Pid()));

    if(elapsedTime == 0) {
        return 0;
    }

    return static_cast<float>(totalTime) / 
        static_cast<float>(elapsedTime);
}

// DONE: Return the command that generated this process
std::string Process::Command() const { return mCommand; }

// DONE: Return this process's memory utilization
std::string Process::RamInMb() const {
    return std::to_string(Parser::RamInKb(Pid()) / 1024);
}

// DONE: Return the user (name) that generated this process
std::string Process::User() const { return mUser; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() const { return Parser::UpTime(Pid()); }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return a.CpuUtilization() < CpuUtilization();
}