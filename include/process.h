#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int id);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const ;  // TODO: See src/process.cpp
  void operator=(const Process &M );

  // TODO: Declare any necessary private members
 private:
 const std::string kProcDirectory{"/proc/"};
 const std::string kStatFilename{"/stat"};
    int pid{0};
    float cpuUtilization{0.0};
    std::string user,cmd,ram;
};

#endif