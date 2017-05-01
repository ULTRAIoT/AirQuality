#include "TinyWireS.h"    

#define I2C_SLAVE_ADDR  0x26         
int airQuality;
uint8_t master_data[2];
// global variable to number of bytes sent from the master.
uint8_t master_bytes;
byte two,one;
// Gets called when the ATtiny receives an i2c write slave request
void receiveEvent(uint8_t num_bytes)
{
  uint8_t i;
  master_bytes = num_bytes;
  for (i = 0; i < master_bytes; i++)
    master_data[i] = TinyWireS.receive();

}

void requestEvent()
{
    TinyWireS.send(one);
    TinyWireS.send(two);  
}

void setup()
{
  TinyWireS.begin(I2C_SLAVE_ADDR);      
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

void loop()
{
 airQuality  = analogRead(A3);
 one = (airQuality>>8) & 0xFF;
 two = airQuality & 0xFF;
 TinyWireS_stop_check();  
}
