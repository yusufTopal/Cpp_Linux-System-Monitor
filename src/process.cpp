#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include <unordered_map>
#include <time.h>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int id) : pid(id){
    cmd= LinuxParser::Command(pid);
    ram= LinuxParser::Ram(pid);
    cpuUtilization= CpuUtilization();
}
void Process::operator=(const Process &M ) { 
        cpuUtilization = M.cpuUtilization;
        cmd= M.cmd;
        ram=M.ram;
        user=M.user;
    }
// TODO: Return this process's ID
int Process::Pid() { return pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    std::stringstream path;
    path << kProcDirectory << "/" << pid << kStatFilename;
    std::ifstream is(path.str());
    string line;
    std::unordered_map<int ,int> data = {
            {13,0},
            {14,0},
            {15,0},
            {16,0},
            {21,0}};
    if (is.is_open()) {
        getline(is, line);
        std::istringstream ss(line);
        string val;
        for (int i = 1, count = 0; count < data.size(); ++i) {
            ss >> val;
            if (data.find(i) != data.end()) {
                int val_int = std::atoi(val.c_str());
                data[i] = val_int;
                count++;
            }
        }
    }
    long long uptime = LinuxParser::UpTime();
    long int hertz = sysconf(_SC_CLK_TCK);
    float  total_time = data[13] + data[14] +
                        data[15] + data[16];
    long int seconds = uptime -  (data[21] / hertz);
    float result = ((total_time / hertz) / seconds);
    return result;
  }

// TODO: Return the command that generated this process

string Process::Command() { return LinuxParser::Command(pid);; }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() {return LinuxParser::User(pid);}
     
// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid);}

// TODO: Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const& a) const { return  cpuUtilization > a.cpuUtilization; }