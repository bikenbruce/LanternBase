struct PoleComm {
  XBeeAddress64 address;
  int status;
};

struct PoleBuff {
	ZBTxRequest zbMessage;
	uint8_t msgNumber;
	int destination;

};
