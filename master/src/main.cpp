#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include "queue.h"

QueueChannels queue(10);

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  Serial.print("Teste: ");
  Serial.println(queue.getNext());
  delay(200);
}
