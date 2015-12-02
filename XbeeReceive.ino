int readXbee() {

  xbee.readPacket();

  if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

    if (xbee.getResponse().isAvailable()) {

      Serial.println("Data is available.");
      
      // fill out zb rx class
      xbee.getResponse().getZBRxResponse(rx);
      
      Serial.println("message received.");

      Serial.print("length: ");
      Serial.println(rx.getDataLength());

      switch (rx.getData(0)) {
        case 0:
          // Status request received
          Serial.print("0");
          Serial.print(" Status Request Received ");
          Serial.println(rx.getData(1));

          // ToDo: have Status Reply indicate current status.
          sendXbeeStatusReply(rx.getData(1), 1);

          break;

        case 1:
          // Return Status
          Serial.print("1");
          Serial.println(" Return Current Status Received ");
   
          break;

        case 2:
          // Change current state
          Serial.println("2");
          Serial.println(" Set State Received ");
          if (rx.getData(1) == 1) {
            wakestate = true;

          } else if (rx.getData(1) == 0) {
            wakestate = false;

          }

          // ToDo: change state based upon this information
          break;

        case 3:
          Serial.print("3");
          Serial.println(" Set Color Array");

          // ToDo: change color array based upon information received.  Needs to be in testing state
          break;

        case 4:
          Serial.print("4");
          Serial.println(" Set Color single");

          // ToDo: change color based upon information received.  Needs to be in testing state
          break;


        case 10:
          // push button event
          Serial.print("10");
          Serial.print(" push button on event received from pole ");
          Serial.print(rx.getData(1));
          Serial.print(" with velocity of ");
          Serial.println(rx.getData(2));

          break;

        case 11:
          Serial.print("11");
          Serial.print(" push button off event received from pole ");
          Serial.println(rx.getData(1));

          break;


        default:
          Serial.print("Nothing set for this value, which is ");
          Serial.println(rx.getData(0));
          // Oups!
      }
    } else if (xbee.getResponse().isError()) {
      Serial.println("");
      Serial.print("Error reading packet.  Error code: "); 
      Serial.print(xbee.getResponse().getErrorCode()); 
      if (xbee.getResponse().getErrorCode() == CHECKSUM_FAILURE) {
        Serial.println(" Checksum Failure.");        
      } else if (xbee.getResponse().getErrorCode() == UNEXPECTED_START_BYTE) {
        Serial.println(" Unexpected start byte.");
      }
      
      Serial.println("");

    }
  }
}
