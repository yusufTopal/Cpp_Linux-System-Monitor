#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  

 private:
    float cpuJiffies[10]{0};
    float idle,nonIdle,total,cpuPercentage;
   
};

#endif