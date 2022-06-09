//------------------------------------------
// Demo sketch using LCD_1602_I2C.h Library
// by: Anas Kuzechie (June, 2022)
//------------------------------------------
#include <LCD_1602_I2C.h>
//------------------------
LCD_1602_I2C lcd(0x40);              /*I2C write address: 0x40*/
//==================================================================
void setup()
{
  lcd.Initialize();                  /*initialize I2C & 1602 LCD*/
  delay(1000);
}
//==================================================================
void loop()
{
  lcd.writeText("Count: ");          /*display text*/
  //----------------------------------------------------------------
  for(byte i=0; i<=99; i++)          /*display count from 0 to 99*/
  {
    lcd.writeChar(1, 0x30+(i/10)%10);/*display MSD of count*/
    lcd.writeChar(1, 0x30+i%10);     /*display LSD of count*/
    lcd.writeChar(0, 0x87);          /*cursor line 1, position 7*/
    delay(300);
  }
  //----------------------------------------------------------------
  lcd.writeChar(0, 0xC0);            /*beginning of 2nd line*/
  lcd.writeText("end of count!");    /*display text*/
  //----------------------------------------------------------------
  delay(1000);
  lcd.writeChar(0, 0x01);            /*clear LCD*/
  delay(1000);
}