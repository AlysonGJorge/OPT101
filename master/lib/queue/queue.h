/**
 * Definição da fila circular para os canais
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define QUEUE_SIZE 5
#define MAX_CHANNEL 125

class QueueChannels
{
    uint8_t queue[QUEUE_SIZE];
    int current;

public:
    QueueChannels(int init);
    uint8_t getNext();
};

#endif // QUEUE_H
