#include "ppu.h"

ppu::ppu() {

}


void ppu::reset() {

}


void ppu::run() {
  execution_thread = std::thread(&ppu::render, this);
}


void ppu::render() {
  while (true) {
    for(int i = 0; i < 256; i++) {
      for(int j = 0; j < 240; j++) {
        int idx = (i * 240 + j) * 4;
        mData[idx + 0] = idx % 3 == 0 ? 0 : 100;
        mData[idx + 1] = idx % 10 == 0 ? 130 : 0;
        mData[idx + 2] = 126;
        mData[idx + 3] = 127;
      }
    }
  }
}


void ppu::dump() {

}

const void * ppu::videoBuffer() {
  return mData;
}
