#include "processor.h"
#include <string>
#include "linux_parser.h"

float Processor::Utilization() {
  auto cpuStats = LinuxParser::CpuUtilization();
  if (!cpuStats[0].empty()) {
    std::istringstream stringstream(cpuStats[0]);
    std::string line;
    int jifCounter = 0;
    while (stringstream) {
      stringstream >> line;
      if (line != "cpu") {
        cpuJiffies[jifCounter] = std::stof(line);
        jifCounter++;
      }
    }
    idle = cpuJiffies[3] + cpuJiffies[4];
    nonIdle = cpuJiffies[0] + cpuJiffies[1] + cpuJiffies[2] + cpuJiffies[5] +
              cpuJiffies[6] + cpuJiffies[7];
    total = idle + nonIdle;
    cpuPercentage = (total - idle) / total;
    return cpuPercentage;
  }
  return 0.0;
}