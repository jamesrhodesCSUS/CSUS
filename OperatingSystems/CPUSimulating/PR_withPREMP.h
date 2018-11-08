//
// Created by james on 10/25/2018.
//
#include <queue>
#include <vector>
#include <iostream>
#include "Globals.h"
#ifndef HW3_PR_WITHPREMP_H
#define HW3_PR_WITHPREMP_H

void PrWithPre(std::vector<Process>& myVector)
{
    Process temp;
    std::priority_queue<Process, std::vector<Process>, CompPriority > pq;
    double average=0;

    std::ofstream outfile("../output.txt");
    outfile << "PR_withPREMP\n";

    for (int completed = 0; completed < myVector.size(); ) {
        CheckIncomingP(myVector, pq);
        if (pq.size() == 0) {
            ++gTime;
            CheckIncomingP(myVector, pq);
        } else {
            temp = pq.top();
            pq.pop();
            outfile << gTime << " " << temp.getPID() << "\n";
            while (temp.getRemainingTime() != 0) {
                --temp;
                ++gTime;
                //std::cout << "\nPID " << temp.getPID() << " Time Remaining " << temp.getRemainingTime();
                CheckIncomingP(myVector, pq);
                if (pq.top().getPriority() < temp.getPriority()) {
                    pq.push(temp);
                    break;
                }
            }

            if(temp.getRemainingTime() == 0){
                average += gTime - (temp.getArrivalTime() + temp.getCPUBT());
                ++completed;
            }
        }
    }
    average /= myVector.size();
    outfile << "Average: " << average;
}

#endif //HW3_PR_WITHPREMP_H
