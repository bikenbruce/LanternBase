
void playLed(byte which, byte r, byte g, byte b) {
   
  if ( testbed ) {
     // Serial.print(r);  Serial.print(" - "); Serial.print(g); Serial.print(" - "); Serial.println(b);
    
    pixels.setPixelColor(which, pixels.Color(r, g, b)); // color function for neopixel
    pixels.show(); // This sends the updated pixel color to the hardware.
  } else {
    DmxSimple.write(which * 4 + 1, r);
    DmxSimple.write(which * 4 + 2, g);
    DmxSimple.write(which * 4 + 3, b);
  }
  
}




void offLed() {
  
  for (byte i = 0; i < boards; i++) {
    if (testbed) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show();
    } else {
      DmxSimple.write(i * 4 + 1, 0);
      DmxSimple.write(i * 4 + 2, 0);
      DmxSimple.write(i * 4 + 3, 0);
    }
 }
}
