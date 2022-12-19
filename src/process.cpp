#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) 
            :process_id_(pid)
    { 
    getcpuutil();
    getuptime();
    getram();
    getuser();
    getcommand();
    }

// TODO: Return this process's ID
int Process::Pid() { return process_id_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_util_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}

void Process::getuser()
{
    user_=LinuxParser::User(Pid());
}

void Process::getcommand()
{
    command_=LinuxParser::Command(Pid());
}

void Process::getram()
{
    ram_=LinuxParser::Ram(Pid());
}

void Process::getcpuutil()
{
    long sysuptime=LinuxParser::UpTime();
    std::vector<float> cputimes = LinuxParser::CpuUtilization(Pid());

    if(cputimes.size()==5)
    {
    float totaltime= cputimes[0]+cputimes[1]+cputimes[2]+cputimes[3];
    float seconds=sysuptime - cputimes[4];

    cpu_util_=totaltime/seconds;
    }
    else
    cpu_util_=0;

}

void Process::getuptime()
{
    uptime_=LinuxParser::UpTime(Pid());

}