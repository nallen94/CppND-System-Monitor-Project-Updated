#include "processor.h"

float Processor::Utilization() {
  std::vector<long> usages = string2long(LinuxParser::CpuUtilization());

  // https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  // Used the above link for reference to calculcate the TIMES of processor
  float idletime = usages[LinuxParser::CPUStates::kIdle_] +
                   usages[LinuxParser::CPUStates::kIOwait_];
 
  float nonidletime = usages[LinuxParser::CPUStates::kUser_] +
                      usages[LinuxParser::CPUStates::kNice_] +
                      usages[LinuxParser::CPUStates::kSystem_] +
                      usages[LinuxParser::CPUStates::kIRQ_] +
                      usages[LinuxParser::CPUStates::kSoftIRQ_] +
                      usages[LinuxParser::CPUStates::kSteal_];

  float totaltime = nonidletime + idletime;

  float totald = totaltime - prev_totaltime;
  float idled = idletime - prev_idletime;
  float CPU_Percentage = (totald - idled) / totald;

  prev_totaltime = totaltime;
  prev_idletime = idletime;

  return CPU_Percentage;
}


//to convert the vector of strings to long data type
std::vector<long> Processor::string2long(
  std::vector<std::string> string_val) {
  std::vector<long> cpu_usages;
  for (auto i : string_val) cpu_usages.push_back(std::stol(i));

  return cpu_usages;
}