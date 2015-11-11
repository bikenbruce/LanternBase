#include <DmxSimple.h>
#include <XBee.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include <TaskScheduler.h>

#include <EEPROM.h>

#include "_rgb.h"
#include "_comm.h"

int POLE;

Scheduler runner;

void t1Callback() {
  sendXbeeHello(10);
}

void t2Callback() {
  readXbee();
}

Task t1(1000, -1, &t1Callback);
Task t2(5,    -1, &t2Callback);

void setup() {
  //setup logging
  Serial.begin(115200);
  Serial.println("SETUP Start");

  POLE = EEPROM.read(0);
  
  Serial.print("I am pole ");
  Serial.println(POLE);
  
  setupDMX();
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
