#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memTotal, memUt, memFree, buffers, cached;
  std::string key, value, line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stringstream(line);
      while (stringstream >> key >> value) {
        if (key == "MemTotal") memTotal = std::stof(value);
        if (key == "MemFree") memFree = std::stof(value);
        if (key == "Buffers") buffers = std::stof(value);
        if (key == "Cached") cached = std::stof(value);
      }
    }
    memUt = 100 - (((memFree + buffers + cached) * 100) / memTotal);
    return memUt;
  }
  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream istream(kProcDirectory + kUptimeFilename);
  string line;
  long upTime = 0;
  if (istream.is_open()) {
    std::getline(istream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
    return upTime;
  }
  return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  string line, cpu;
  long usrjf, nicejf, systemjf;
  std::ifstream istream(kProcDirectory + kStatFilename);
  if (istream.is_open()) {
    std::getline(istream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> usrjf >> nicejf >> systemjf;
    return systemjf;
  }
  return 0;
}

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  string line;
  string filePath = kProcDirectory + '/' + to_string(pid) + '/' + kStatFilename;
  std::ifstream filestream(filePath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      std::vector<std::string> results(
          (std::istream_iterator<std::string>(stringstream)),
          std::istream_iterator<std::string>());
      return std::stol(results.at(22));  // /proc/[pid]/stat starttime 22th.
    }
  }
  return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string line, cpu;
  long usrjf;
  std::ifstream istream(kProcDirectory + kStatFilename);
  if (istream.is_open()) {
    std::getline(istream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> usrjf;
    return usrjf;
  }
  return 0;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line, cpu;
  long usrjf, nicejf, systemjf, idlejf;
  std::ifstream istream(kProcDirectory + kStatFilename);
  if (istream.is_open()) {
    std::getline(istream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> usrjf >> nicejf >> systemjf >> idlejf;
    return idlejf;
  }
  return 0;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string key, line;
  int totalProcessCount;
  std::ifstream istream(kProcDirectory + kMeminfoFilename);
  if (istream.is_open()) {
    while (std::getline(istream, line)) {
      std::istringstream istringstream(line);
      istringstream >> key >> totalProcessCount;
      if (key == "processes") return totalProcessCount;
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string key, line;
  int totalProcessCount;
  std::ifstream istream(kProcDirectory + kMeminfoFilename);
  if (istream.is_open()) {
    while (std::getline(istream, line)) {
      std::istringstream istringstream(line);
      istringstream >> key >> totalProcessCount;
      if (key == "procs_running") return totalProcessCount;
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string command;
  string filePath =
      kProcDirectory + '/' + to_string(pid) + '/' + kCmdlineFilename;
  std::ifstream istream(filePath);
  if (istream.is_open()) {
    while (getline(istream, command)) {
      return command;
    }
  }
  return string();
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid[[maybe_unused]]) { 
  string  line,key,memory,kb;
   string filePath =
      kProcDirectory + '/' + to_string(pid) + '/' + kStatusFilename;
  std::ifstream istream(filePath); 
  if (istream.is_open()) {
    while (std::getline(istream, line)) {
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream istringstream(line);
      istringstream >> key >> memory >> kb;
      if (key == "VmSize") return memory;
    }
  }
  return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]) {
   return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }