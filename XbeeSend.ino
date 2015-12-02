////// status events events ///////
void sendXbeeStatusRequest(int poleDestination) {
  uint8_t message[] = {0, POLE};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeStatusReply(int poleDestination, uint8_t status) {
  uint8_t message[] = {1, POLE, status};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeSetStatus(int poleDestination, uint8_t status) {
  uint8_t message[] = {2, POLE, status};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}


////// push button events ///////
void sendXbeeButtonOnEvent(int poleDestination, uint8_t velocity) {
  uint8_t message[] = {10, POLE, velocity};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}

void sendXbeeButtonOffEvent(int poleDestination) {
  uint8_t message[] = {11, POLE};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);
}


// Send array of colors / RGB
void sendXbeeAllColors(int poleDestination, RGB colors[10]) {
  uint8_t message[31];
  message[0] = 12;
  int m;

  for (int i = 0; i < 10; i++) {
    m = i * 3 + 1;
    message[m] = colors[i].r;
    message[m + 1] = colors[i].b;
    message[m + 2] = colors[i].g;

  }

  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, message, sizeof(message));
  sendXbee(msgToPole, poleDestination);

}

// Send single color / RGB
void sendXbeeSingleColor(int poleDestination, RGB color) {
  uint8_t buttonPressed[] = {13, POLE, color.r, color.b, color.g};
  ZBTxRequest msgToPole = ZBTxRequest(pole[poleDestination].address, buttonPressed, sizeof(buttonPressed));
  sendXbee(msgToPole, poleDestination);

}


void sendXbee(ZBTxRequest msgToPole, int poleDestination) {
  xbee.send(msgToPole);
  Serial.print("Message sent to pole ");
  Serial.println(poleDestination);

  //Not srue what the digit is for.
  if (xbee.readPacket(500)) {
  // got a response!
    if (xbee.getResponse().isAvailable()) {
      // should be a znet tx status             
      if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
        xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
        if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
          Serial.println("confirmation received.");

        } else {
          // the remote XBee did not receive our packet. is it powered on?
          Serial.println("confirmation not received.");
        
        }
      } else if (xbee.getResponse().isError()) {
        Serial.print("Error reading packet.  Error code: ");  
        Serial.println(xbee.getResponse().getErrorCode());

      }
    }
  }
}