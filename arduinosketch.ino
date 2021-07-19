#include <SPI.h>

#define ADDRLATCH 7
#define OE 3
#define CE 4
#define WE 5

void setup() {
  Serial.begin(115200);
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
  pinMode(ADDRLATCH, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(WE, OUTPUT);
  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(WE, HIGH);
}

uint16_t address = 0;

void loop() {
  writeData(address & 0xFF, address);
  Serial.println(readData(address));
  
  address++;
  delay(500);
}

void writeAddr(uint16_t address){
  SPI.transfer16(address);
  digitalWrite(ADDRLATCH, LOW);
  digitalWrite(ADDRLATCH, HIGH);
  digitalWrite(ADDRLATCH, LOW);
}

void writeData(uint8_t data, uint16_t address){
  SPI.transfer(data);
  writeAddr(address);
  digitalWrite(CE, LOW);
  digitalWrite(WE, LOW);
  delayMicroseconds(10);
  digitalWrite(WE, HIGH);
  digitalWrite(CE, HIGH);
}

uint8_t readData(uint16_t address){
  writeAddr(address);
  digitalWrite(CE, LOW);
  digitalWrite(OE, LOW);
  digitalWrite(OE, HIGH);
  delayMicroseconds(10);
  return SPI.transfer(0x00);
  digitalWrite(CE, HIGH);
}