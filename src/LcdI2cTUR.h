#ifndef _LCDI2CTUR_H
#define _LCDI2CTUR_H
#include "Arduino.h"
#include "Wire.h"
class LcdI2cTUR : public Print
{
  public:
  LcdI2cTUR(uint8_t address=0x27) {_address = address; Wire.begin(); }
  void begin();
  void displayOFF();
  void displayON();
  void displayClear();
  void cursorON();
  void cursorOFF();
  void blinkON();
  void blinkOFF();
  void addChar(uint8_t location, uint8_t charSet[], bool userDefined=true);
  void setCursor(uint8_t col, uint8_t row);
  void backlightsON();
  void backlightsOFF();
  void goHome();
  void autoScroll();
  void NoAutoScroll();
  void displayShiftLeft();
  void displayShiftRight();

  virtual size_t write(uint8_t Chr);
  
  private:
    void I2CWrite(uint8_t data);
    void LCDWriteCmd(uint8_t data);
    void LCDWriteData(uint8_t temp);
    void setEntryMode();
    void cursorMode();
    void InitLCD();
    
  private:
    uint8_t _rs = 0;
    uint8_t _rw = 0;
    uint8_t _data = 0;
    uint8_t _led = 8;
    uint8_t _en =  4;
    uint8_t _address;
    uint8_t _cursor = 2;
    uint8_t _display = 4;
    uint8_t _blink = 1;
    uint8_t _increment = 2;
    uint8_t _scroll = 0;

     bool f196 = 0;
    bool f197 = 0;
    uint8_t cTr[8] = {
      0b00000,
      0b01110,
      0b10001,
      0b10000,
      0b10000,
      0b10001,
      0b01110,
      0b00100
    };
    uint8_t GTr[8] = {
      0b01110,
      0b00000,
      0b01110,
      0b10001,
      0b10000,
      0b10111,
      0b10001,
      0b01111
    };
    uint8_t STr[8] = {
      0b00000,
      0b00000,
      0b01110,
      0b10000,
      0b01110,
      0b00001,
      0b01110,
      0b00100
    };
    uint8_t _gTr[8] = {
      0b01110,
      0b00000,
      0b01111,
      0b10001,
      0b10001,
      0b01111,
      0b00001,
      0b01110
    };
    uint8_t ITr[8] = { //büyük İ
      0b00100,
      0b00000,
      0b01110,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b01110
    };
    uint8_t _iTr[8] = { //küçük ı
      0b00000,
      0b00000,
      0b01100,
      0b00100,
      0b00100,
      0b00100,
      0b01110,
      0b00000
    };
};

#endif
