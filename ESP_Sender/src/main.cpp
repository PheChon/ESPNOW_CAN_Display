#include <SPI.h>
#include <mcp_can.h>

// Define SPI pins for ESP32
#define CAN_CS   5   // Chip Select pin
// ESP32 hardware SPI default pins: SCK = 18, MISO = 19, MOSI = 23

MCP_CAN CAN0(CAN_CS);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for Serial to initialize
  }
  Serial.println("ESP32 with MCP2515 CAN Receiver");

  // Initialize MCP2515 at 250kbps using an 8MHz oscillator
  if (CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515...");
    while (1) {
      delay(100);
    }
  }
  
  CAN0.setMode(MCP_NORMAL);
  Serial.println("CAN Bus Receiver Ready...");
}

void loop() {
  if (CAN0.checkReceive() == CAN_MSGAVAIL) {
    unsigned long id;
    unsigned char len = 0;
    unsigned char buf[8];
    CAN0.readMsgBuf(&id, &len, buf);

    Serial.print("Received CAN ID: 0x");
    Serial.print(id, HEX);
    Serial.print(" | Data: ");
    for (int i = 0; i < len; i++) {
      if (buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
