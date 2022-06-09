//-------------------------------------------------------
// LCD_1602_I2C.h - Header File
// Library for Programming 1602 LCD via PCF8574 Expander
// by: Anas Kuzechie (June, 2022)
//-------------------------------------------------------
//header guards
#ifndef LCD_1602_I2C_h
#define LCD_1602_I2C_h
//----------------------------------------------------------------------
//class definition
class LCD_1602_I2C
{
    public:
        LCD_1602_I2C(byte address);
        void Initialize();
        void writeText(unsigned char text[]);
        void writeChar(byte mode, byte value);       
    private:
        byte _address;
        void send4bits(byte value);
        void PCF8574_sendByte(byte data);
};
//----------------------------------------------------------------------
#endif