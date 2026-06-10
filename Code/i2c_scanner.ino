#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  Serial.println("I2C Scanner");
}

void loop()
{
  byte error, address;
  int count = 0;

  for(address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if(error == 0)
    {
      Serial.print("Device found at 0x");
      Serial.println(address, HEX);
      count++;
    }
  }

  if(count == 0)
    Serial.println("No devices found");

  delay(3000);
}
