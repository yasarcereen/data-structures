/* @Author
Student Name: Ceren Yaşar
Student ID : 150210013
Date: 26.10.22
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"

using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;

    startTime = -1;
    endTime = -1;
    remainingTime = processTime;
}

ProcessRep::~ProcessRep()
{
}

ProcessRep* ProcessRep::getNext()
{
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    this->mpNext = next;
    if (next != nullptr)
        this->mpNext->mpNext = nullptr;
}

string ProcessRep::getProcessType()
{
    return this->mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    this->mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    this->mProcessTime = ProcessTime;
}
