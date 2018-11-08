//
// Created by james on 10/24/2018.
//
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Globals.h"
#ifndef HW3_ROUNDROBIN_H
#define HW3_ROUNDROBIN_H

void CheckIncoming(std::vector<Process>& myVector, std::queue<Process>& myQueue)
{
    for (int i = added; i < myVector.size(); i++) {
        if (myVector[i].getArrivalTime() == gTime) {
            myQueue.push(myVector[i]);
            ++added;
        }
    }
}

void RoundRobin(std::vector<Process>& myVector, int timeQuantum)
{
    std::queue<Process> myQueue;
    double average = 0;

    std::ofstream outfile("../output.txt");
    outfile<<"RR " << timeQuantum << "\n";

    while (!(myQueue.empty() && gTime > myVector[myVector.size()-1].getArrivalTime())) {

        CheckIncoming(myVector, myQueue);

        if(!myQueue.empty()) {
            for (int i = 0; i < timeQuantum; i++) {
                if(i == 0)
                    outfile << gTime << " " << myQueue.front().getPID() << "\n";

                --myQueue.front();

                //std::cout << "\nPID " << myQueue.front().getPID() << " Time Remaining " << myQueue.front().getRemainingTime();

                ++gTime;
                CheckIncoming(myVector, myQueue);

                if (myQueue.front().getRemainingTime() == 0)
                    break;
            }

            if(myQueue.front().getRemainingTime() == 0) {
                average += gTime - (myQueue.front().getArrivalTime() + myQueue.front().getCPUBT());
                myQueue.pop();
            } else{
                myQueue.push(myQueue.front());
                myQueue.pop();
            }
        }
        else{
            ++gTime;
        }
    }
    average /= myVector.size();
    outfile<<"Average: " << average << "\n";
}

#endif //HW3_ROUNDROBIN_H
