//
// Created by james on 10/25/2018.
//
#include <queue>
#include <vector>
#include <iostream>
#include "Globals.h"
#ifndef HW3_SHORTESTJOBFIRST_H
#define HW3_SHORTESTJOBFIRST_H

/*
 * When the arrival time is equal to the
 * global clock, add it to the queue
 */
void CheckIncomingPQ(std::vector<Process>& myVector, std::priority_queue<Process, std::vector<Process>, CompBT >& pq)
{
    for (int i = added; i < myVector.size(); i++) {
        if (myVector[i].getArrivalTime() == gTime) {
            pq.push(myVector[i]);
            ++added;
        }
    }
}

void ShortestJobFirst(std::vector<Process>& myVector)
{
    Process temp;
    std::priority_queue<Process, std::vector<Process>, CompBT > pq;
    double average = 0;

    std::ofstream outfile("../output.txt");
    outfile << "SJF\n";

    for (int completed = 0; completed < myVector.size();) {
        CheckIncomingPQ(myVector, pq);
        if (pq.size() == 0) {
            ++gTime;
            CheckIncomingPQ(myVector, pq);
        } else {
            temp = pq.top();
            pq.pop();
            outfile << gTime << " " << temp.getPID() << "\n";
            while (temp.getRemainingTime() != 0) {
                --temp;
                ++gTime;
                CheckIncomingPQ(myVector, pq);
                //std::cout << "\nPID " << temp.getPID() << " Time Remaining " << temp.getRemainingTime();
            }
            average += gTime - (temp.getArrivalTime() + temp.getCPUBT());
            ++completed;
        }
    }
    average /= myVector.size();
    outfile << "Average: " << average;
}

#endif //HW3_SHORTESTJOBFIRST_H
