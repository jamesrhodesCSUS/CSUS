#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Process.h"
#include "RoundRobin.h"
#include "ShortestJobFirst.h"
#include "PR_noPREMP.h"
#include "PR_withPREMP.h"

struct compare
{
    inline bool operator() (const Process& left, const Process& right)
    {
        return (left.getArrivalTime() < right.getArrivalTime());
    }
};

int main() {
    std::ifstream inputFile("../input.txt");
    std::string procType;
    int pid, arrivalTime, cpuBT, priority;
    int timeQuantum;
    int inputSize;
    std::vector<Process> myVector;

    if(inputFile)
    {
        inputFile >> procType;
        if (procType == "RR")
            inputFile >> timeQuantum;

        inputFile >> inputSize;

        for(int i = 0; i < inputSize; i++)
        {
            inputFile >> pid >> arrivalTime >> cpuBT >> priority;
            Process proc(pid, arrivalTime, cpuBT, priority);
            myVector.push_back(proc);
        }
    }
    else
    {
        std::cout << "Cannot open file!";
        return 0;
    }

    std::sort(myVector.begin(), myVector.end(), compare());

    if (procType == "RR")
        RoundRobin(myVector, timeQuantum);
    else if (procType == "SJF")
        ShortestJobFirst(myVector);
    else if (procType == "PR_noPREMP")
        PrNoPre(myVector);
    else
        PrWithPre(myVector);

    return 0;
}