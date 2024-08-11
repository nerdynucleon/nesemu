#include <thread>
#include <OpenGL/gl3.h>

const static int kNesVideoWidth = 256;
const static int kNesVideoHeight = 240;
const static int kNesVideoSize = kNesVideoWidth * kNesVideoHeight;
const static int kNesVideoBytesPerPixel = 4;
const static int kNesVideoBufferSize = kNesVideoSize * kNesVideoBytesPerPixel;

class ppu {
  public:
    ppu();

    void reset();

    void run();

    void dump();

    const void * videoBuffer();

  private:
    std::thread execution_thread;
    void render();

    GLubyte mData[kNesVideoBufferSize];
};
