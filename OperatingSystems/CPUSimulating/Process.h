//
// Created by james on 10/24/2018.
//
#include <iostream>
#include "Globals.h"
#ifndef HW3_PROCESS_H
#define HW3_PROCESS_H

class Process {
private:
    int pid;//Process ID
    int arrivalTime;//Process Arrival Time
    int cpuBT;//Process CPU Burst Time
    int remainingTime;//Process remaining time
    int priority;//Process Priority

public:
    //Default Constructor
    //Used for Process temp
    Process(){}
    //Should be every other process
    //CPU Burst time is actually the remaining time left for that process
    Process(int pid, int arrivalTime, int cpuBT, int priority)
            : pid(pid), arrivalTime (arrivalTime), cpuBT(cpuBT), remainingTime(cpuBT), priority(priority) {    }

    //Getters
    int getArrivalTime() const { return arrivalTime; }
    int getPID() const { return pid; }
    int getRemainingTime() const { return remainingTime; }
    int getCPUBT() const { return cpuBT; }
    int getPriority() const {return priority; }

    //Overloaded Operators
    Process& operator--()
    {
        remainingTime--;
        return *this;
    }
};

/*
 * COMPARRISON STRUCTS
 */
struct CompBT{
    bool operator()(const Process& left, const Process& right)
    {
        return !(left.getCPUBT() <= right.getCPUBT());
    }
};

struct CompPriority{
    bool operator()(const Process& left, const Process& right)
    {
        return left.getPriority() > right.getPriority();
    }
};


#endif //HW3_PROCESS_H
