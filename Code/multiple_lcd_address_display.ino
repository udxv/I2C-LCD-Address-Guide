#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define MAX_LCDS 8

byte lcdAddresses[MAX_LCDS];
byte lcdCount = 0;

void scanI2CDevices()
{
  lcdCount = 0;

  for (byte address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);

    if (Wire.endTransmission() == 0)
    {
      lcdAddresses[lcdCount] = address;
      lcdCount++;

      if (lcdCount >= MAX_LCDS)
        break;
    }
  }
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  scanI2CDevices();

  Serial.print("Devices Found: ");
  Serial.println(lcdCount);

  for (byte i = 0; i < lcdCount; i++)
  {
    Serial.print("Address: 0x");
    Serial.println(lcdAddresses[i], HEX);

    LiquidCrystal_I2C lcd(lcdAddresses[i], 16, 2);

    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("My Address:");

    lcd.setCursor(0, 1);
    lcd.print("0x");
    lcd.print(lcdAddresses[i], HEX);

    delay(500);
  }
}

void loop()
{
}
