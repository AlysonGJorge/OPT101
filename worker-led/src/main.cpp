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

int brightness = 0;
int fadeAmount = 5;

void led_blink() {
  analogWrite(LED_PIN, brightness);

  brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
}

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
  pinMode(LED_PIN, OUTPUT);
}

void loop(void) {
  /*bool canSend = rts_message();*/
  /*if (canSend) {*/
  /*  send_msg(MASTER_ADDR, DTA, value);*/
  /*}*/
  led_blink();
  delay(WAIT_LOOP);
}
