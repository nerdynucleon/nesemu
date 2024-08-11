#include <stdint.h>

static const int kNesRamSize = 0x800;

class memmap {
  public:
    memmap() {};

    uint8_t read(uint16_t addr);

    void reset();
    void dump();

  private:
    uint8_t ram[kNesRamSize];

    uint8_t PPU_REG[8];

    uint8_t APU_IO_REG[0x18];

    uint8_t APU_IO_DISABLED[0x8];

    uint8_t cartrige[0xBFE0];
};
