#include "format.h"

#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  string time = "00:00:00";

  if (seconds > 0)
    time = std::to_string(seconds / 3600) + ":" + std::to_string((seconds / 60)%60) +
           ":" + std::to_string(seconds%60);

  return time;
}