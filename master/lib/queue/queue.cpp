/**
 * Implementação da fila circular para os canais
 */
#include "queue.h"

QueueChannels::QueueChannels(int init)
{
    int incremente = init;
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        queue[i] = incremente;
        incremente += 5;
    }

    this->current = 0;
}

uint8_t QueueChannels::getNext()
{
    this->current++;
    return this->queue[this->current % QUEUE_SIZE];
}
