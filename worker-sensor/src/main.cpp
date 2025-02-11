#include "config.h"
#include "message.h"
#include "radio.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <RF24.h>
#include <SPI.h>

//===-----------------------------------------------------------------------===
// Request To Send (RTS)
//===-----------------------------------------------------------------------===

bool rts_message() {
  uint8_t tmp = 0;
  uint64_t timer = micros();
  uint64_t retrieve = 0;

  while (micros() - timer < TIMEOUT_RTS) {
    send_msg(MASTER_ADDR, RTS, tmp);

    if (receive_msg(MASTER_ADDR, CTS, tmp)) {
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
  pinMode(SENSOR_PIN, INPUT);
}

void loop(void) {

  bool canSend = rts_message();
  if (canSend) {
    int value = analogRead(0);
    if (value > 800) {
      Serial.println("Muito claro");
      send_msg(MASTER_ADDR, DTA, 0);
    } else if (value <= 800 && value > 500) {
      Serial.println("Claro");
      send_msg(MASTER_ADDR, DTA, 60);
    } else if (value <= 500 && value > 200) {
      Serial.println("Escuro");
      send_msg(MASTER_ADDR, DTA, 127);
    } else {
      Serial.println("Muito Escuro");
      send_msg(MASTER_ADDR, DTA, 255);
    }
  }

  delay(WAIT_LOOP);
}
