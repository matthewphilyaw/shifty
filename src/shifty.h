#ifndef SHIFTY_H
#define SHIFTY_H

#include "WProgram.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

void shifty_init(uint8_t clk, uint8_t data, uint8_t latch);
void shifty_write(uint8_t *buffer, uint32_t length);
void shifty_write_no_latch(uint8_t *buffer, uint32_t length);
void shifty_clock();
void shifty_latch();

#ifdef __cplusplus
}
#endif

#endif
