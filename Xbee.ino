XBee xbee = XBee();

PoleComm pole[12];

ZBTxStatusResponse txStatus = ZBTxStatusResponse();
ZBRxResponse rx = ZBRxResponse();

void setupXbee() {
  Serial3.begin(57600);
  xbee.setSerial(Serial);

  pole[0].address = XBeeAddress64(0x00000000, 0x0000ffff);  // broadcast
  pole[1].address = XBeeAddress64(0x0013a200, 0x408d9e0e);  // pole 1, corodinator
  pole[2].address = XBeeAddress64(0x0013a200, 0x409140b6);  // pole 2
  pole[3].address = XBeeAddress64(0x0013a200, 0x40914018);  // pole 3
  pole[4].address = XBeeAddress64(0x0013a200, 0x408d9e5f);  // pole 4
  pole[5].address = XBeeAddress64(0x0013a200, 0x40c91adf);  // pole 5
  pole[6].address = XBeeAddress64(0x0013a200, 0x40d61a48);  // pole 6
  pole[7].address = XBeeAddress64(0x0013a200, 0x40c91ae4);  // pole 7
  pole[8].address = XBeeAddress64(0x0013a200, 0x40c5f951);  // pole 8

  pole[9].address  = XBeeAddress64(0x0013a200, 0x408CDB42);  // Test Router 1
  pole[10].address = XBeeAddress64(0x0013a200, 0x407054ac);  // Test Router 2
  pole[11].address = XBeeAddress64(0x0013a200, 0x408cdb45);  // Test Router 3

}