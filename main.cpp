#include "Buffer.h"

Buffer buffer(5);

void producer()
{

    for (int i = 0; i < 100; ++i)
    {
        buffer.push();
    }
}

void consumer()
{
    for (int i = 0; i < 100; ++i)
    {
        buffer.pop();
    }
}

int main()
{
    outFile.open("outputConsumerProducer.txt");
    std::thread threadConsumer(consumer);
    std::thread threadProducer(producer);

    threadConsumer.join();
    threadProducer.join();

    outFile.close();
    return 0;
}