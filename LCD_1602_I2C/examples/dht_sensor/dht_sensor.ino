//--------------------------------------------
// DHT Sensor Temp & Humidity on I2C 1602 LCD
// using LCD_1602_I2C.h & DHT.h Libraries
// by: Anas Kuzechie (June, 2022)
//--------------------------------------------
#include <LCD_1602_I2C.h>
#include <DHT.h>
//------------------------------------------------------------
LCD_1602_I2C lcd(0x40);   /*I2C write address: 0x40*/
DHT dht(2, DHT22);        /*DHT22 sensor connected to pin 2*/
//============================================================
void setup()
{
  dht.begin();            /*initialize DHT sensor*/
  lcd.Initialize();       /*initialize 16x2 LCD*/
  delay(1000);
  //------------------------------------------------------
  lcd.writeText("--DHT22 Sensor--");
  lcd.writeChar(0, 0xC0); /*beginning of 2nd line*/
  lcd.writeText("Temp & Humidity");
  delay(2000);
  lcd.writeChar(0, 0x01); /*clear LCD*/
}
//============================================================
void loop()
{
  delay(2000);
  //---------------------------------------------------
  float temp = dht.readTemperature();
  int temp_MSD = int(temp)/10 + 48;
  int temp_LSD = int(temp)%10 + 48;
  int temp_fraction = (temp - int(temp))*10 + 48;
  //---------------------------------------------------
  lcd.writeText("Temp    : ");
  lcd.writeChar(1, temp_MSD);
  lcd.writeChar(1, temp_LSD);
  lcd.writeChar(1, '.');
  lcd.writeChar(1, temp_fraction);
  lcd.writeText(" C");
  //---------------------------------------------------
  float hum = dht.readHumidity();
  int hum_MSD = int(hum)/10 + 48;
  int hum_LSD = int(hum)%10 + 48;
  int hum_fraction = (hum - int(hum))*10 + 48;
  //---------------------------------------------------
  lcd.writeChar(0, 0xC0); /*beginning of 2nd line*/
  //---------------------------------------------------
  lcd.writeText("Humidity: ");
  lcd.writeChar(1, hum_MSD);
  lcd.writeChar(1, hum_LSD);
  lcd.writeChar(1, '.');
  lcd.writeChar(1, hum_fraction);
  lcd.writeText(" %");
  //---------------------------------------------------
  lcd.writeChar(0, 0x80); /*beginning of 1st line*/
}