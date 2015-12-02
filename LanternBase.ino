#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TaskScheduler.h>
#include <EEPROM.h>
#include <DmxSimple.h>
#include <Adafruit_NeoPixel.h>
#include "_rgb.h"
#include "_comm.h"
#include "_LantSine.h"

#define DMX_PUSH_BUTTON_PIN 1 //analog
#define DMX_LED_PIN 8

uint8_t POLE;
boolean wakestate = true;
boolean testbed = false;
byte boards = 10;

//////////////////// LANTERN PIN I/O & VAR START UP CODE
const int cs = 53; //chip select
const int led13pin = 13, inLedpin = 34, exLedpin = 24;
//digital inputs and array,
const int bigBtnpin = 28, pir2pin = EEPROM.read(3), pir1pin = 36;
//items are btn, pir1, pir2
byte dArrRaw[] = {0, 0, 0};
boolean buttonStillOn = false;

////////////// Led Buffer // used globally with other classes
int ledBuf[10][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

///////////// SineWave Led player ///////////////
//       direction,channel,yspacing,amplitude, width,period,brd
LantSine rsine(false, 0, 10, 170, 180, 100, boards);
LantSine gsine(false, 1, 10, 60, 120, 100, boards);
LantSine bsine(false, 2, 70, 20, 2800, 500, boards);

//////////////////// NEOPIXEL TESTBED Startup Code
// Which pin on the Arduino is connected to the NeoPixels?
int neopixelPin =  25;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(boards, neopixelPin, NEO_GRB + NEO_KHZ800);

Scheduler runner;

void t1Callback();
void t2Callback();
void cbPlaySeq();

Task t1(40, -1, &t1Callback); // check buttons
Task t2(5,  -1, &t2Callback); // xbee / wireless
Task playSeq(100, -1, &cbPlaySeq);


void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("Setup");

  POLE = EEPROM.read(0);
  
  Serial.print("I am pole ");
  Serial.println(POLE);
  
  // setupDMX();
  //simpleTest();
  setupXbee();

  t1.enable();
  Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");


  runner.init();

  runner.addTask(t1);
  Serial.println("added t1");
  runner.addTask(t2);
  Serial.println("added t2");

  delay(1000);
  
}

void loop() {
  runner.execute();

}

void t2Callback() {
  readXbee();
}

void t1Callback() {
  if (dArrRaw[0] == HIGH) { // a btn
    if (buttonStillOn == false ) {
      buttonStillOn = true;
      //rsine.calcWave(ledBuf);
      //playSeq.setInterval(300 - anaArrRaw[0]);
       //playSeq.setInterval(5);
     // playSeq.restart();
      //Serial.println("Enabled t1 Again");
      //Serial.print("#ON# ");
    }
  } else {
    buttonStillOn = false;
    //playSeq.setInterval(25);
    // Serial.println("/btn OFF/ ");
  }
}

void cbPlaySeq() {
  rsine.calcWave(ledBuf);
  gsine.calcWave(ledBuf);
 // bsine.calcWave(ledBuf);
  render();
  // delay(20);

}

void render() {
  for (byte leds = 0; leds < boards; leds++) {
    playLed(leds, ledBuf[leds][0], ledBuf[leds][1], ledBuf[leds][2]);
    // playLed(leds, 0, ledBuf[leds][1], ledBuf[leds][2]);
    // Serial.println(ledBuf[leds][2]);
  }
}
