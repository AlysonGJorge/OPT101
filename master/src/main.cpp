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
// Request To Send (RTS)
//===-----------------------------------------------------------------------===

bool rts_message(uint8_t value) {
  uint64_t timer = micros();
  uint64_t retrieve = 0;

  while (micros() - timer < TIMEOUT_RTS) {
    send_msg(WORKER_LED_ADDR, RTS, value);

    if (receive_msg(WORKER_LED_ADDR, CTS, value)) {
      return true;
    }

    retrieve++;
    delayMicroseconds(DELAY_RTS * retrieve);
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

uint8_t brightness = 0;

void loop(void) {
  bool canReceive = cts_message(WORKER_SENSOR_ADDR);
  if (canReceive) {
    if (receive_msg(WORKER_SENSOR_ADDR, DTA, brightness)) {
      Serial.println(brightness);
    }
  }
  
  rts_message(brightness);
  delay(WAIT_LOOP);
}
