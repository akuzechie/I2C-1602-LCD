//-------------------------------------------------------
// LCD_1602_I2C.cpp - Header File
// Library for Programming 1602 LCD via PCF8574 Expander
// by: Anas Kuzechie (June, 2022)
//-------------------------------------------------------
#include <Arduino.h>
#include <LCD_1602_I2C.h>
//========================================================================
// Assembly Function Prototypes
//========================================================================
extern "C"
{
   /*function prototypes calling assembly subroutines in .S file*/
  void I2C_init();              /*I2C SCL freq = 100kHz enabled*/
  void I2C_start();             /*send I2C START condition*/
  void I2C_write(byte);         /*send data byte via SDA line*/
  void I2C_stop();              /*send I2C STOP condition*/
  void delay_short();           /*0.45us delay*/
  void delay_us();              /*40us delay*/
  void delay_ms();              /*1.6ms delay*/
}
//========================================================================
// Constructor
//========================================================================
LCD_1602_I2C::LCD_1602_I2C(byte address)
{
  _address = address;           /*assign I2C write address*/
}
//========================================================================
// Public Methods
//========================================================================
void LCD_1602_I2C::Initialize()
{
  I2C_init();                   /*initialize I2C of ATmega328*/
  writeChar(0, 0x33);           /*initialize LCD for 4-bit data*/
  delay_ms();
  writeChar(0, 0x32);
  delay_ms();
  writeChar(0, 0x28);           /*LCD 2 lines, 5x7 matrix*/
  delay_ms();
  writeChar(0, 0x0C);           /*display ON, cursor OFF*/
  writeChar(0, 0x01);           /*clear LCD*/
  delay_ms();
  writeChar(0, 0x06);           /*shift cursor right*/
}
//========================================================================
void LCD_1602_I2C::writeText(unsigned char text[])
{
  byte i = 0;
  while(text[i] != '\0')
  {
    writeChar(1, text[i]);
    i++;
  }
}
//========================================================================
void LCD_1602_I2C::writeChar(byte mode, byte value)
{
  byte highnib = value & 0xF0;          /*extract high and*/
  byte lownib  = (value << 4) & 0xF0;   /*low nibbles*/
  send4bits(highnib | mode);            /*then send nibble*/
  send4bits(lownib  | mode);            /*ORed with mode*/
}
//========================================================================
// Private Methods
//========================================================================
void LCD_1602_I2C::send4bits(byte value)
{
  PCF8574_sendByte(value);
  PCF8574_sendByte(value | 0b00000100);  /*EN = 1*/
  delay_short();                         /*0.45us delay*/
  PCF8574_sendByte(value & ~0b00000100); /*EN = 0*/
  delay_us();                            /*40us delay*/
}
//========================================================================
void LCD_1602_I2C::PCF8574_sendByte(byte data)
{
  I2C_start();                  /*send START condition*/
  I2C_write(_address);          /*send write address of PCF8574*/
  I2C_write(data);              /*send data byte*/
  I2C_stop();                   /*send STOP condition*/
}