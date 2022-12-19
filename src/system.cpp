#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
  std::vector<int> processes = LinuxParser::Pids();

  for (int i : processes) {
    Process proc = i;
    processes_.push_back(proc);
  }

  processes_=Sort(processes_);

  return processes_;
}

std::vector<Process>& System::Sort(std::vector<Process>& processes_unordered)
{

    std::sort(processes_unordered.begin(),processes_unordered.end(),[](Process &utila, Process & utilb)
    {
      return utilb.CpuUtilization()<utila.CpuUtilization();
    });

  return processes_unordered;

}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }