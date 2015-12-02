//#ifndef LantSine_H
//#define LantSine_H

#include "Arduino.h"

class LantSine {
  public:
    LantSine(boolean u,int c,int ys, float amp, int w, float p, byte b);
    ~LantSine();
    void calcWave(int buf[10][3]);
    void changeWave(boolean u,int c,int ys, float amp, int w, float p, byte b);
    void fadeOutWave(byte spd);
    void fadeInWave(byte lvl, byte spd);
    void off();
  private:
    boolean up;
    byte channel;
    int yspacing;
    float amplitude;  // Height of wave
    int width;
    float period;  // How many pixels before the wave repeats
    byte brd;
    int dirval;
    byte brdcnt;
    float theta;  // Start angle at 0
    float dy;  // Value for incrementing X, a function of period and xspacing
   
};


//#endif
