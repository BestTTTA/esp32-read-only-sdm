#include <ModbusMaster.h>
#include <HardwareSerial.h>


void preTransmission() {
  delayMicroseconds(200);
}

void postTransmission() {
  delayMicroseconds(200);
}


#define modbusaddr 1

ModbusMaster node;


void setup() {
  Serial.begin(115200);
  //15 => RX , 4 => TX
  Serial2.begin(9600, SERIAL_8N1, 15, 4);

  node.begin(modbusaddr, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}



float reform_uint16_2_float32(uint16_t u1, uint16_t u2) {
  uint32_t num = ((uint32_t)u1 & 0xFFFF) << 16 | ((uint32_t)u2 & 0xFFFF);
  float numf;
  memcpy(&numf, &num, 4);
  return numf;
}



float getRTU(uint16_t m_startAddress) {
  uint8_t m_length = 2;
  uint16_t result;
  float x;

  node.clearResponseBuffer();

  result = node.readInputRegisters(m_startAddress, m_length);
  if (result == node.ku8MBSuccess) {
    return reform_uint16_2_float32(node.getResponseBuffer(0), node.getResponseBuffer(1));
  }
}



void loop() {
  float Vol = getRTU(0x0000);
  // float Wat = getRTU(0x000C);
  // float Cur = getRTU(0x0006);
  // float Fre = getRTU(0x0046);
  // float TotalWh = getRTU(0x0156);
  // float PF = getRTU(0x001E);

  Serial.print("Vol:");
  Serial.println(Vol);


  Serial.println("Wait 5s");
  delay(5000);
}
