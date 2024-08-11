#include <stdint.h>
#include <thread>

#include "memmap.h"

class cpu6502 {
  public:
    cpu6502();

    void reset();

    void run();

    void dump();

    void interrupt();
    
  private:
    void execute();
    std::thread execution_thread;

    uint8_t reg_A;
    uint8_t reg_P;
    uint16_t reg_PC;
    uint8_t reg_S;
    uint8_t reg_X;
    uint8_t reg_Y;

    memmap mem;
    
    void panic(bool invalid_instruction = false);

    uint8_t address_mode(uint8_t opcode);


    // INSTRUCTIONS
    // TRANSFER

    // STACK
    void op_PHP(uint8_t opcode);

    // DECREMENT INCREMENT

    // ARITHMETIC

    // LOGICAL
    void op_ORA(uint8_t opcode);

    // SHIFT && ROTATE
    void op_ASL(uint8_t opcode);

    // FLAG

    // COMPARISON

    // CONDITIONAL BRANCH

    // JUMP SUBROUTINE

    // INTERRUPTS

    // OTHER
};
