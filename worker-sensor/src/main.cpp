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
  /*bool canSend = rts_message();*/
  /*if (canSend) {*/
  /*  uint8_t value = analogRead(A0);*/
  /*  Serial.println(value);*/
  /*  send_msg(MASTER_ADDR, DTA, value);*/
  /*}*/

  int value = analogRead(SENSOR_PIN);
  Serial.print(value);
  if (value < 10) {
    Serial.println(" - Dark");
  } else if (value < 200) {
    Serial.println(" - Dim");
  } else if (value < 500) {
    Serial.println(" - Light");
  } else if (value < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  delay(WAIT_LOOP);
}
