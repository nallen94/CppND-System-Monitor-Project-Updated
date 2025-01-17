#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// vector<int> LinuxParser::Pids() {
//   vector<int> pids;
//   const std::filesystem::path process_dir{kProcDirectory};
//   for (auto const& dir_entry :
//        std::filesystem::recursive_directory_iterator{process_dir})

//   return pids;
// }

// TODO: Read and return the system memory utilization
// https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  float value{0.0};

  float MemTotal, MemFree, Buffers, Cached, SReclaimable, Shmem{0.0};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal")
          MemTotal = value;
        else if (key == "MemFree")
          MemFree = value;
        else if (key == "Buffers")
          Buffers = value;
        else if (key == "Cached")
          Cached = value;
        else if (key == "SReclaimable")
          SReclaimable = value;
        else if (key == "Shmem")
          Shmem = value;
      }
    }
  }
  Cached = Cached + SReclaimable - Shmem;
  value = (MemTotal - MemFree - Buffers - Cached) / MemTotal;
  return value;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string value;
  long uptime_system, uptime_idle;
  long uptime;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 2; i++) {
      linestream >> value;
      if (i == 0) uptime_system = std::stol(value);
      if (i == 1) uptime_idle = std::stol(value);
    }
  }
  uptime = (uptime_system + uptime_idle) / sysconf(_SC_CLK_TCK);
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> usages;
  string line;
  string value;
  std::ifstream fstream(kProcDirectory + kStatFilename);
  if (fstream.is_open()) {
    std::getline(fstream, line);
    std::istringstream linestream(line);
    while (!linestream.eof()) {
      linestream >> value;
      if (value != "cpu") usages.push_back(value.substr());
    }
  }
  return usages;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int value{0};
  int processes;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          processes = value;
        }
      }
    }
  }
  return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int value{0};
  int processes_running;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          processes_running = value;
        }
      }
    }
  }
  return processes_running;
}

std::vector<float> LinuxParser::CpuUtilization(int pid){
  std::vector<float> cputimes;
  string value;
  string line;

  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      for(int i=1; i<=22; i++){
        linestream>>value;
        if(i==14)
        cputimes.push_back(std::stof(value)/sysconf(_SC_CLK_TCK));
        if(i==15)
        cputimes.push_back(std::stof(value)/sysconf(_SC_CLK_TCK));
        if(i==16)
        cputimes.push_back(std::stof(value)/sysconf(_SC_CLK_TCK));
        if(i==17)
        cputimes.push_back(std::stof(value)/sysconf(_SC_CLK_TCK));
        if(i==22)
        cputimes.push_back(std::stof(value)/sysconf(_SC_CLK_TCK));
      }
    }
  }
  return cputimes;
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string line;
  string key;
  string value{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      value = line;
    }
  }
  return value;
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string value{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value ) {
        if (key == "VmSize") {        
          value = std::to_string(std::stof(value)* 0.001);
          value=value.substr(0, value.find(".")+0);
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value {};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line;
  string key;
  string x;
  string value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> x >> value) {
        if (value == Uid(pid)) {
          return key;

        }
      }
    }
  }
  return key;
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  string line;
  string key;
  string value;
  long uptime{0};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +
                           kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for (int i = 1; i <= 22; i++) {
        linestream >> value;
        if (i == 22) uptime = std::stol(value) / sysconf(_SC_CLK_TCK);
      }
    }
  }
  return uptime;
}
