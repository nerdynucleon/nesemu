#include "nes.h"

#include <csignal>

nes* instance = nullptr;

nes::nes() {
  instance = this;
}

void nes::init() {
  cpu.reset();
  ppu.reset();
  signal(SIGINT, signalHandler);
}

void nes::run() {
  ppu.run();
  cpu.run();
}

void nes::signalHandler(int signal) {
  if (signal & SIGINT) {
    if (instance)
      instance->dump();
    exit(signal);
  }
}

void nes::dump() {
  cpu.dump();
  ppu.dump();
}
