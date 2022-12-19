#include "processor.h"

// https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<long> usages = string_to_long(LinuxParser::CpuUtilization());

  float totaltime = usages[LinuxParser::CPUStates::kUser_] +
                    usages[LinuxParser::CPUStates::kNice_] +
                    usages[LinuxParser::CPUStates::kSystem_] +
                    usages[LinuxParser::CPUStates::kIdle_] +
                    usages[LinuxParser::CPUStates::kIOwait_] +
                    usages[LinuxParser::CPUStates::kIRQ_] +
                    usages[LinuxParser::CPUStates::kSoftIRQ_] +
                    usages[LinuxParser::CPUStates::kSteal_];

  float idletime = usages[LinuxParser::CPUStates::kIdle_] +
                   usages[LinuxParser::CPUStates::kIOwait_];

  float diff_idle = idletime - prev_idle;
  float diff_total = totaltime - prev_total;
  float cpu_usage = (diff_total - diff_idle) / diff_total;

  prev_idle = idletime;
  prev_total = totaltime;

  return cpu_usage;
}

std::vector<long> Processor::string_to_long(std::vector<std::string> string_val) \
{
  std::vector<long> cpu_usages;
  for (auto i : string_val) cpu_usages.push_back(std::stol(i));

  return cpu_usages;
}