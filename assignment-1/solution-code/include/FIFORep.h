/* @Author
Student Name: Ceren Yaşar
Student ID : 150210013
Date: 26.10.22
*/
#ifndef _FIFOREP
#define _FIFOREP

#include <iostream>
#include <stdio.h>
#include "ProcessRep.h"
class FIFORep 
{
    /*
        The class construct a FIFO queue.
    */

private:
    ProcessRep* mpHead;
    ProcessRep* mpTail;
public:
    FIFORep();
    FIFORep(ProcessRep*);
    ~FIFORep();

    void setHead(ProcessRep*);
    ProcessRep* getHead();

    void setTail(ProcessRep*);
    ProcessRep* getTail();

    void queue(ProcessRep*);
    ProcessRep* dequeue();

    ProcessRep* searchID(int);
    void printFIFO();
};


#endif