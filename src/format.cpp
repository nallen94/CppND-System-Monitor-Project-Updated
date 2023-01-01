#include "format.h"
#include "iostream"

#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long minutes=seconds/60;
  long hours=seconds/3600;

  string time = "00:00:00";
  string sec = std::to_string((seconds%3600)%60);
  sec.insert(0, 2-sec.length(), '0');
  string mins = std::to_string(minutes);
  mins.insert(0, 2 - mins.length(), '0');
  string hrs = std::to_string(hours);
  hrs.insert(0, 2 - hrs.length(), '0');

  if (seconds > 0)
    time= hrs + ":" + mins + ":" + sec;

  return time;
}