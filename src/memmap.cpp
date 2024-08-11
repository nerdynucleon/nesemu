#include "memmap.h"
#include <cstring>
#include <cstdio>

void memmap::dump() {
  printf("Memory Dump:\n");
  for (int row = 0; row < 0x4020 / 16; row++) {
    printf("%04x:", row * 16 );
    for (int col = 0; col < 16 / 4; col ++) {
      printf("%02x %02x %02x %02x ", read(row * 16 + col * 4 + 0), read(row * 16 + col * 4 + 1), read(row * 16 + col * 4 + 2), read(row * 16 + col * 4 + 3));
    }
    printf("\n");
  }

}

void memmap::reset() {
  memset(ram, 0xff,  kNesRamSize);
}

uint8_t memmap::read(uint16_t addr) {
  if (addr < kNesRamSize * 4) {
    return ram[addr % kNesRamSize];
  } else if (addr < 0x4000) {
    return PPU_REG[(addr - 0x2000) % 8];
  } else if (addr < 0x4018) {
    return APU_IO_REG[addr - 0x4000];
  } else if (addr < 0x401F) {
    return APU_IO_DISABLED[addr - 0x4018];
  }
  return cartrige[addr - 0x4020];
}
