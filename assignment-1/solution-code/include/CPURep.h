/* @Author
Student Name: Ceren Yaşar
Student ID : 150210013
Date: 26.10.22 
*/ 
#ifndef _CPUREP
#define _CPUREP

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

class CPURep
{
    /*
        The CPU representation class that run  processes.
    */  
private:
    FIFORep* mFinishedProcess; 
public:
    CPURep();
    ~CPURep();

    FIFORep* getFinishedProcess();
    void setFinishedProcess(FIFORep*);

    ProcessRep* runCPU(ProcessRep*, int);
};

#endif