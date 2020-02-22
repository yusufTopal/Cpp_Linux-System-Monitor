#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int id): pid(id) {
    cpuUtilization=CpuUtilization();
    cmd=Command();
    user= LinuxParser::User(pid);
    upTime=LinuxParser::UpTime(pid);
    ram= LinuxParser::Ram(pid);
}

// TODO: Return this process's ID
int Process::Pid() {  return pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization; }

// TODO: Return the command that generated this process
string Process::Command() { return cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() {return user;}
     

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid);}

// TODO: Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const& a) const { return cpuUtilization > a.cpuUtilization; }