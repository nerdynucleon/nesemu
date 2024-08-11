#include <thread>

class ppu {
  public:
    ppu();

    void reset();

    void run();

    void dump();
    
  private:
    std::thread execution_thread;
    void render();
};
