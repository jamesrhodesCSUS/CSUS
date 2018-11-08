//
// Created by james on 10/25/2018.
//
#include <queue>
#include <vector>
#include <iostream>
#ifndef HW3_PR_NOPREMP_H
#define HW3_PR_NOPREMP_H

void CheckIncomingP(std::vector<Process>& myVector, std::priority_queue<Process, std::vector<Process>, CompPriority >& pq)
{
    for (int i = added; i < myVector.size(); i++) {
        if (myVector[i].getArrivalTime() == gTime) {
            pq.push(myVector[i]);
            std::cout << "\nAdded Process " << myVector[i].getPID() << " @ " << gTime;
            ++added;
        }
    }
}

void PrNoPre(std::vector<Process>& myVector)
{
    Process temp;
    std::priority_queue<Process, std::vector<Process>, CompPriority > pq;
    double average=0;

    std::ofstream outfile("../output.txt");
    outfile << "PR_noPREMP\n";

    for (int completed = 0; completed < myVector.size();) {
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
                CheckIncomingP(myVector, pq);
                //std::cout << "\nPID " << temp.getPID() << " Time Remaining " << temp.getRemainingTime();
            }
            average += gTime - (temp.getArrivalTime() + temp.getCPUBT());
            ++completed;
        }
    }
    average /= myVector.size();
    outfile << "Average: " << average;
}

#endif //HW3_PR_NOPREMP_H
