#pragma once

#include <queue>
#include "Semaphore.h"
#include <iostream>
#include <fstream>

std::ofstream    outFile;
int syncValue = 1;
int count = 0;

class Buffer
{
public:
    Buffer(int count) :maxSize(count + 1), m_Full(count), m_empty(0), m_serialize(1) {}

    void push()
    {
        m_Full.down();
        m_serialize.down();
        outFile << "Produced: " << syncValue << "     Items count : " << ++count << std::endl;
        m_Queue.push(syncValue++);
        if (syncValue == maxSize)  outFile << "Producer is waiting " << std::endl;
        m_serialize.up();
        m_empty.up();
    }

    void pop()
    {
        m_empty.down();
        m_serialize.down();
        outFile << "Consumed : " << m_Queue .front() << "     Items count : " << --count << std::endl;
        --syncValue;
        if (syncValue == 1) outFile << "Consumer is waiting " << std::endl;
        m_Queue.pop();
        m_serialize.up();
        m_Full.up();
    }

private:

    Semaphore m_Full;
    Semaphore m_empty;
    Semaphore m_serialize;
    int maxSize;
    std::queue<int> m_Queue;
};