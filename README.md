# I2C 1602 LCD
This library works with IC PCF8574 (I2C write address: 0x40) interfaced with 1602 LCD. The library should work with modules using IC PCF8574A, assuming the I2C address is known.

List of public functions:
1. Initialize(): initializes both ATmega328 I2C and LCD
2. writeChar(): displays an alphanumeric character on LCD
3. writeText(): displays up 16 characters of text on selected line of LCD
