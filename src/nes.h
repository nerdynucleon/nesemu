#pragma once
#include "cpu6502.h"
#include "ppu.h"

class nes; 

class nes {
  public:
    nes();
    void init();
    void run();

    void dump();

    static void signalHandler(int sig);

    const void * videoBuffer();
    int32_t videoBufferWidth();
    int32_t videoBufferHeight();

  private:
    cpu6502 cpu;
    ppu ppu;
};
