#include "_LantSine.h" //include the declaration for this class

//<<constructor>> setup the LED, make pin 13 an OUTPUT
LantSine::LantSine(boolean u, int c, int ys, float amp, int w, float p, byte b) {
  up = u;
  channel = c;
  yspacing = ys;
  amplitude = amp;  // Height of wave
  width = w;
  period = p;  // How many pixels before the wave repeats
  brd = b;
  dy = (TWO_PI / period) * yspacing;



  //  Serial.print(channel); Serial.print(" - ");
  //  Serial.print(yspacing); Serial.print(" - ");
  //  Serial.print(amplitude); Serial.print(" - ");
  //  Serial.print(width); Serial.print(" - ");
  //  Serial.print(period); Serial.print(" - ");
  //  Serial.print(brd); Serial.print(" - ");
  //  Serial.print(dy); Serial.print(" - ");
  //  Serial.println("LantSine started");
}

//<<destructor>>
LantSine::~LantSine() {
  /*nothing to destruct*/
}


//turn the LED on
void LantSine::calcWave(int buf[10][3]) {

  if (!up) {
    brdcnt = 0;
    dirval = 1;
  } else {
    brdcnt = brd - 1;
    dirval = -1;
  }

  // Increment theta (try different values for 'angular velocity' here
  theta += 0.08;


  // For every x value, calculate a y value with sine function
  float y = theta;
  int c = theta;
  for (byte i = 0; i < brd; i++) {

    buf[brdcnt][channel] = int(abs(sin(y) * amplitude));
    brdcnt += dirval;
    y += dy;
    //Serial.print(i); Serial.print(" / "); Serial.print(dy); Serial.print(" -// ");

  }

  //Serial.println("--////");

}

void LantSine::changeWave(boolean u,int c,int ys, float amp, int w, float p, byte b) {
  up = u;
  channel = c;
  yspacing = ys;
  amplitude = amp;  // Height of wave
  width = w;
  period = p;  // How many pixels before the wave repeats
  brd = b;
  dy = (TWO_PI / period) * yspacing;
}

void LantSine::fadeOutWave(byte spd) {
 if ( amplitude > 0 ) {
    amplitude = amplitude - spd;
 }
}
void LantSine::fadeInWave(byte lvl, byte spd) {
 if ( amplitude < lvl ) {
    amplitude = amplitude + spd;
 }
}

//blink the LED in a period equal to paramterer -time.
void LantSine::off() {
  amplitude = 0;
}
