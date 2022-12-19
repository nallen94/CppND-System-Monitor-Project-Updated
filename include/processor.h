#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:

 float prev_idletime=0;
 float prev_totaltime=0;

 std::vector<long> string2long(std::vector<std::string>);

};

#endif