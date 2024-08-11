#include "cpu6502.h"

#include <cstdio>
#include <cstdlib>

cpu6502::cpu6502() {
}

void cpu6502::reset() {
  reg_PC = 0xFFFC;
  reg_A = 0x00;
  reg_X = 0x00;
  reg_Y = 0x00;
  reg_S = 0x00;
  reg_P = 0x00; 
  mem.reset();
}

uint8_t cpu6502::address_mode(uint8_t opcode) {
  return opcode & 0b00011100; 
}

void cpu6502::run() {
  execution_thread = std::thread(&cpu6502::execute, this);
}

void cpu6502::execute() {
  while (true) {
    uint8_t opcode = mem.read(reg_PC);
    uint8_t address_mode = opcode & 0b00011100;
    reg_PC++;
    switch (opcode) {
      case 0x00: // BRK
        // interrupt();
        break;
      case 0x01:
        op_ORA(opcode);
        break;
      case 0x05:
        op_ORA(opcode);
        break;
      case 0x06:
        break;
      default:
        // panic(true);
        break;
    }
  }
}

void cpu6502::interrupt(){
  // TODO:
  panic();
}

void cpu6502::dump() {
  mem.dump();
  printf("-------------\nCPU 6502 dump:\n");
  printf("regA 0x%x\n", reg_A);
  printf("regP 0x%x\n", reg_P);
  printf("regPC 0x%x\n", reg_PC);
  printf("regS 0x%x\n", reg_S);
  printf("regX 0x%x\n", reg_X);
  printf("regY 0x%x\n", reg_Y);
}


void cpu6502::panic(bool invalid_instruction) {
  dump();
  if(invalid_instruction)
    printf("invalid instruction\n");
  exit(-1);
}

void cpu6502::op_ORA(uint8_t opcode) {
}
