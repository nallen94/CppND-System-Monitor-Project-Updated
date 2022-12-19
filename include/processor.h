#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:

 float prev_idle=0;
 float prev_total=0;

 std::vector<long> string_to_long(std::vector<std::string>);

};

#endif