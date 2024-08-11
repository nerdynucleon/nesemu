#include "ppu.h"

ppu::ppu() {

}


void ppu::reset() {

}


void ppu::run() {
  execution_thread = std::thread(&ppu::render, this);
}


void ppu::render() {

}


void ppu::dump() {

}
