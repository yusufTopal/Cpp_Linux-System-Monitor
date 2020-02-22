#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"
#include <iostream>
using std::set;
using std::size_t;
using std::string;
using std::vector;


System::System(){
    upTime=LinuxParser::UpTime();

}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
        auto pids = LinuxParser::Pids();
    for (int pid : pids) {
            processes_.push_back(Process(pid));
        }
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel();}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    if(runningProcess <=0)
        runningProcess=LinuxParser::RunningProcesses(); 
    return runningProcess;    
    }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    if(totalProcess<=0)
        totalProcess= LinuxParser::TotalProcesses();
    return totalProcess;
}
    

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    if(upTime<=0)
        upTime=LinuxParser::UpTime();
    return upTime;
}