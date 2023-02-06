/* @Author
Student Name: Ceren Yaşar
Student ID : 150210012
Date: 26.10.22 
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->mpHead = nullptr;
    this->mpTail = nullptr;
    // FIFORep is initialized with no value, hence empty
}

FIFORep::FIFORep(ProcessRep* head)
{
    this->mpHead = head;
    this->mpTail = head;
    // if there is only one node when initialized, head == tail
}


FIFORep::~FIFORep()
{
    ProcessRep* cursor = this->mpHead;
    
    // while there are still nodes in the linked list (FIFORep), delete it and move on to the next one
    
    while (cursor != nullptr) {
        ProcessRep* temp = cursor->getNext();
        delete cursor;
        cursor = temp;
    }

}

void FIFORep::setHead(ProcessRep* head)
{
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    // The function add a process to the tail of the queue.

    // if the list is empty, set both head and tail to p
    if (mpHead == nullptr && mpTail == nullptr) {
        mpHead = p;
        mpTail = p;
        return;
    }
    
    mpTail->setNext(p);
    mpTail = mpTail->getNext();
}

ProcessRep* FIFORep::dequeue()
{   
    
    if (mpHead == nullptr) {
        return nullptr;
    }

    ProcessRep* temp = mpHead;
    if (mpHead == mpTail) {
        mpHead = nullptr;
        mpTail = nullptr;
    } else {
        mpHead = mpHead->getNext();
    }    
    temp->setNext(nullptr);
    return temp;
}

ProcessRep* FIFORep::searchID(int id)
{   
    // The function search a process by id and returns it if it exist otherwise returns NULL.
    
    ProcessRep* cursor = mpHead;
    while (cursor != nullptr)
    {
        if (cursor->getProcessID() == id)
        {
            return cursor;
        } else
        {
            cursor = cursor->getNext();
        }
    }
}

void FIFORep::printFIFO()
{
    // The function prints the proceses in the queue starting from Head to tail.
    
    ProcessRep* cursor = mpHead;

    while (cursor != nullptr)
    {
        cout << cursor->getProcessType() << cursor->getProcessID() << " " << cursor->startTime << " " << cursor->endTime << " ";
        cursor = cursor->getNext();
    }
}
