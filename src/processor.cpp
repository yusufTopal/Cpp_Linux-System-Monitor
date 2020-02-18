#include "processor.h"
#include "linux_parser.h"
#include <string>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {     
    auto cpuStats =LinuxParser::CpuUtilization();
    cumIdle = std::stof(cpuStats[0].at(4));
      
    /*Idle = idle + iowait
    NonIdle = user + nice + system + irq + softirq + steal
    Total = Idle + NonIdle

    CPU_Percentage = (totald - idled)/totald
    */
    return 0.0; }