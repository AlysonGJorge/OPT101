#include "config.h"
#include "message.h"
#include "radio.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <RF24.h>
#include <SPI.h>

//===-----------------------------------------------------------------------===
// LED
//===-----------------------------------------------------------------------===

uint8_t brightness = 0;
int fadeAmount = 5;

void led_blink() {
  analogWrite(LED_PIN, brightness);

  brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
}

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
  pinMode(LED_PIN, OUTPUT);
}


void loop(void) {
  // led_blink();
  bool canReceive = cts_message(MASTER_ADDR);
  if (canReceive) {
    if (receive_msg(MASTER_ADDR, DTA, brightness)) {
      Serial.println(brightness);
    }
  }
  delay(WAIT_LOOP);
}
