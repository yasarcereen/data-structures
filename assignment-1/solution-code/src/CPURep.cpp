/* @Author
Student Name: Ceren Yaşar
Student ID : 150210013
Date: 26.10.22 
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h" 

using namespace std;

CPURep::CPURep()
{
    this->mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    delete this->mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{  
    // returns null if p is null or p is finished
    // returns p if p is not finished
    if (p == nullptr) {
        return p;
    }

    if (p->startTime == -1) {
        p->startTime = time;
    }

    p->remainingTime--;
    time++;

    if (p->remainingTime == 0) {
        p->endTime = time;
        mFinishedProcess->queue(p);
        return nullptr;
    }

    return p;

}

FIFORep* CPURep::getFinishedProcess()
{
    return mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    mFinishedProcess = finishedProcess;
}