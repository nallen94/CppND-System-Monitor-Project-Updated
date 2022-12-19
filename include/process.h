#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  Process(int pid);

  // TODO: Declare any necessary private members
 private:
 int process_id_;
 std::string user_;
 std::string command_;
 float cpu_util_;
 std::string ram_;
 long int uptime_;

 void getuptime();
 void getcpuutil();
 void getram();
 void getuser();
 void getcommand();

};

#endif