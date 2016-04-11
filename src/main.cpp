#include "WProgram.h"
#include "stdint.h"
#include "shifty.h"

#define BUFFER_LENGTH 16
#define write_buf() shifty_write(buffer, BUFFER_LENGTH)
#define zero_buf() set_buffer_range(0, BUFFER_LENGTH, LOW)
#define set_high(start, end) set_buffer_range((start), (end), HIGH)

static uint8_t buffer[BUFFER_LENGTH];

static void set_buffer_range(uint32_t start, uint32_t count, uint8_t value) {
  uint8_t end = start + count;

  if (end > BUFFER_LENGTH) {
    return;
  }

  for (uint32_t i = start; i < end; i++) {
    buffer[i] = value;
  }
}

static void run_for(void (*fn)(), uint32_t ms) {
  uint32_t tick = millis();

  while((millis() - tick) < ms) {
    fn();
  }
}

static void strobe_two() {
  zero_buf();
  set_high(0, 2);
  write_buf();
  delay(100);
  zero_buf();
  set_high(BUFFER_LENGTH - 2, 2);
  write_buf();
  delay(100);
}

static void strobe_eight() {
  zero_buf();
  set_high(0, 8);
  write_buf();
  delay(250);
  zero_buf();
  set_high(BUFFER_LENGTH - 8, 8);
  write_buf();
  delay(250);
}

static void single_chase_ping() {
  for (uint32_t i = 0; i < BUFFER_LENGTH; i++) {
    zero_buf();
    buffer[i] = HIGH;
    write_buf();
    delay(25);
  }
}

static void single_chase_pong() {
  for (uint32_t i = (BUFFER_LENGTH - 1); i < BUFFER_LENGTH; i--) {
    zero_buf();
    buffer[i] = HIGH;
    write_buf();
    delay(25);
  }
}

static void dual_pong() {
  uint32_t half_buf = BUFFER_LENGTH / 2;

  for (uint32_t i = 0; i < half_buf; i++) {
    zero_buf();
    buffer[half_buf - i] = HIGH;
    buffer[half_buf + i] = HIGH;
    write_buf();
    delay(100);
  }

  for (uint32_t i = 0; i < half_buf; i++) {
    zero_buf();
    buffer[i] = HIGH;
    buffer[(BUFFER_LENGTH - 1) - i] = HIGH;
    write_buf();
    delay(100);
  }
}

static void ping_pong() {
  single_chase_ping();
  single_chase_pong();
}

extern "C" int main(void)
{
  shifty_init(13, 11, 5);

  /* flash lights on boot */
  set_high(0, BUFFER_LENGTH);
  write_buf();
  delay(500);
  zero_buf();
  write_buf();
  delay(500);

  while(1) {
    run_for(&strobe_two, 5000);
    run_for(&strobe_eight, 5000);
    run_for(&ping_pong, 10000);
    run_for(&dual_pong, 10000);
  }
}
