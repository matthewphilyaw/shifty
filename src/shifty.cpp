#include "shifty.h"

static uint8_t shifty_pin_clk;
static uint8_t shifty_pin_data;
static uint8_t shifty_pin_latch;

void shifty_init(uint8_t clk, uint8_t data, uint8_t latch) {
  shifty_pin_clk   = clk;
  shifty_pin_data  = data;
  shifty_pin_latch = latch;

  pinMode(shifty_pin_clk, OUTPUT);
  pinMode(shifty_pin_data, OUTPUT);
  pinMode(shifty_pin_latch, OUTPUT);
}

void shifty_clock() {
  digitalWriteFast(shifty_pin_clk, HIGH);
  digitalWriteFast(shifty_pin_clk, LOW);
}

void shifty_latch() {
  digitalWriteFast(shifty_pin_latch, HIGH);
  digitalWriteFast(shifty_pin_latch, LOW);
}

void shifty_write(uint8_t *buffer, uint32_t length) {
  shifty_write_no_latch(buffer, length);
  shifty_latch();
}

/* NOTE: i will be bigger than length on over flow */
void shifty_write_no_latch(uint8_t *buffer, uint32_t length) {
  for (uint32_t i = (length - 1); i < length; i--) {
    digitalWriteFast(shifty_pin_data, (buffer[i] & 0x01));
    shifty_clock();
  }
}
