/* @Author
Student Name: Ceren Yaşar
Student ID : 150210013
Date: 26.10.22 
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    mpRunningProcess = nullptr;
    mpProcessFIFO[0] = new FIFORep();
    mpProcessFIFO[1] = new FIFORep();
    mpProcessFIFO[2] = new FIFORep();
    pCpuObj = new CPURep();
    timeSliceCount = 0;
    totalTime = 0;
}

SchedulerRep::~SchedulerRep()
{
    delete this->mpProcessFIFO[0];
    delete this->mpProcessFIFO[1];
    delete this->mpProcessFIFO[2];
    delete this->pCpuObj;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    this->mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    if (p == nullptr)
        return;

    int idx; // this variable keeps the index in which we will be making additions

    if (p->getProcessType() == "A") {
        idx = 0;
    } else if (p->getProcessType() == "B") {
        idx = 1;
    } else {
        idx = 2;
    }

    this->mpProcessFIFO[idx]->queue(p);
}

ProcessRep* SchedulerRep::popProcess()
{
    // pop the process with the highest priority by starting to search from the first process fifo.
    // do null checks each time to avoid segmentation fault
    if (mpProcessFIFO[0]->getHead() != nullptr) {
        return mpProcessFIFO[0]->dequeue();
    } else if (mpProcessFIFO[1]->getHead() != nullptr) {
        return mpProcessFIFO[1]->dequeue();
    } else if (mpProcessFIFO[2]->getHead() != nullptr) {
        return mpProcessFIFO[2]->dequeue();
    }
    return nullptr;
}

bool SchedulerRep::checkTimeSlice() 
// returns true if the process has reached its quantum limit or is already finished, false otherwise
{
    if (mpRunningProcess == nullptr || mpRunningProcess->remainingTime <= 0){
        return true;
    }

    int limit;

    if (mpRunningProcess->getProcessType() == "A") {
        limit = 2;
    } else if (mpRunningProcess->getProcessType() == "B") {
        limit = 4;
    } else {
        limit = 8;
    }

    if (timeSliceCount >= limit) {
        return true;
    }
    return false;
}

ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p)
{
    if (p == nullptr) {
        return nullptr;
    }

    if (p == mpRunningProcess) {
        // if p was already running in the cpu, increase its quantum
        timeSliceCount++;
    } else {
        // if p is sent just now, set timeSliceCount to 1.
        // not 0 because p is already sent to cpu and guaranteed to run for 1 step
        timeSliceCount = 1;
        mpRunningProcess = p;
    }

    ProcessRep* temp = pCpuObj->runCPU(p, totalTime);

    mpRunningProcess->setNext(nullptr);

    if (temp == nullptr) {
        // if runCPU returned null, p is finished so we need to update the running process and set timeSliceCount to 0
        // because it will be increased when sent to the CPU as it should be
        mpRunningProcess = popProcess();
        timeSliceCount = 0;
    }
    return p;
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{

    ProcessRep* arrivingProcess = new ProcessRep(type, id, arrivalTime, processTime);

    if (mpRunningProcess == nullptr || checkTimeSlice()) { 
        /*
        if the running process has reached its limit or there is no running process at the moment, we enter this code block.
        either way, arriving process should be sent to the fifo first.
        because if there was a running process that reached its limit and arrived scheduler, and if the types of these two
        processes are the same, arriving process should be prioritized.
        */

        timeSliceCount = 0;
        pushProcess(arrivingProcess);

        if (mpRunningProcess != nullptr)
            pushProcess(mpRunningProcess);

        sendProcessToCPU(popProcess());
    } else {
        /*
        if there is a running process that hasn't reached its quantum limit yet, we enter this code block.
        in this case, a priority comparison is required because if the arriving process has higher priority, current running process
        must be suspended and arriving process must be sent to the cpu.
        here, we do this check by comparing the ascii values of type characters.
        'A' = 65
        'B' = 66
        'C' = 67
        if a character with lower ascii value arrives, it should be prioritized.
        otherwise, it should wait its turn and current running process should be sent to the cpu again.
        */
        if (mpRunningProcess != nullptr && mpRunningProcess->getProcessType()[0] > type[0]){
            pushProcess(arrivingProcess);
            pushProcess(mpRunningProcess);
            
            sendProcessToCPU(popProcess());
        } else {
            pushProcess(arrivingProcess);

            sendProcessToCPU(mpRunningProcess);
        }
    } 
    totalTime++;
}

void SchedulerRep::schedule(ProcessRep* p)
{
    
    if (mpRunningProcess == nullptr) {
        totalTime++;
        return;
    }

    else if (!checkTimeSlice()) {
        // if the running process hasn't yet reached its limit
        sendProcessToCPU(mpRunningProcess);
    }

    else {
        // this means that checkTimeSlice() == true, which tells us that the running process is either finished or reached its quantum
        timeSliceCount = 0;

        // if it is not yet finished, put back to the fifo.
        if (mpRunningProcess != nullptr)
            pushProcess(mpRunningProcess);
        sendProcessToCPU(popProcess());
    }

    totalTime++;
}
