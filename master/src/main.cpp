#include "config.h"
#include "message.h"
#include "radio.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <RF24.h>
#include <SPI.h>

//===-----------------------------------------------------------------------===
// Clear to Send
//===-----------------------------------------------------------------------===

bool cts_message(uint8_t source) {
  uint8_t tmp = 0;
  uint64_t timer = micros();

  while (micros() - timer < TIMEOUT_CTS) {
    if (receive_msg(source, RTS, tmp)) {
      send_msg(source, CTS, 0);
      return true;
    }

    delayMicroseconds(DELAY_CTS);
  }

  return false;
}

//===-----------------------------------------------------------------------===
// Setup e Loop
//===-----------------------------------------------------------------------===

void setup(void) {
  Serial.begin(BAUD_RATE);
  init_radio();
}

void loop(void) {
  bool canReceive = cts_message(WORKER_LED_ADDR);
  if (canReceive) {
    uint8_t tmp = 0;
    if (receive_msg(WORKER_LED_ADDR, DTA, tmp)) {
      Serial.println(tmp);
    }
  }

  delay(WAIT_LOOP);
}
