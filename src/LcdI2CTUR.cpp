
#include "LcdI2cTUR.h"

void LcdI2cTUR::I2CWrite(uint8_t data)
{
  Wire.beginTransmission(_address);
  Wire.write(data);
  Wire.endTransmission();
  _data = data;
}

void LcdI2cTUR::LCDWriteCmd(uint8_t data)
{
  _rs=0;
  data = data << 4; //00110000
  data |= _led; //00001000
  I2CWrite(data); // 00111000
  delayMicroseconds(40);
  data |= _en; // 00111000 | EN = 00111100
  I2CWrite(data); //00111100
  delayMicroseconds(40);
  data &= ~_en;  // 00111100 & 11111011 = 00111000
  I2CWrite(data); //00111000
  delayMicroseconds(37);
}
void LcdI2cTUR::LCDWriteData(uint8_t temp)
{ 
  // temp = 01001000
  Serial.println(temp,BIN);
  uint8_t data = (temp >> 4);     //data = 00000100   
  Serial.println(data,BIN);
  data = data << 4; //00110000
  Serial.println(data,BIN);
  data |= _led; //00001000
  if (_rs != 1)
  { 
    _rs=1;
    I2CWrite(data); // 00111000
    delayMicroseconds(500);
  }
  data |= _rs; //0001001
  I2CWrite(data); // 00111000
  delayMicroseconds(37);
  Serial.println(data,BIN);
  data |= _en; // 00111000 | EN = 00111100
  I2CWrite(data); //00111100
  delayMicroseconds(37);
  data &= ~_en;  // 00111100 & 11111011 = 00111000
  I2CWrite(data); //00111000
  delayMicroseconds(37);
  
  data = temp & 0b00001111; // 00001000
  Serial.println(data,BIN);
  data = data << 4; //10000000
  Serial.println(data,BIN);
  data |= _led; //10001000
  data |= _rs; //10001001
  I2CWrite(data); // 10001001
  Serial.println(data,BIN);
  delayMicroseconds(40);
  data |= _en; // 00111000 | EN = 00111100
  I2CWrite(data); //00111100
  delayMicroseconds(40);
  data &= ~_en;  // 00111100 & 11111011 = 00111000
  I2CWrite(data); //00111000
  delayMicroseconds(37);
}

void LcdI2cTUR::displayOFF()
{
 _display = 0;
 _led = 0;
 LCDWriteCmd(0x0); 
 LCDWriteCmd(8 | _display | _cursor | _blink); 
}
void LcdI2cTUR::displayON()
{
 // 000 0 0 0 1 DCB   D:Display 0:off 1:on C:Cursor 0:off 1:on B:Blink 0:off 1:on
 _display = 4;
 _led =8;
 LCDWriteCmd(0x0); 
 LCDWriteCmd(8 | _display | _cursor | _blink); // | _cursor | _blink);  //1111    //1 D C B   
}
void LcdI2cTUR::displayClear()
{
   LCDWriteCmd(0x0);
   LCDWriteCmd(0x1);  
   delayMicroseconds(100);
}
void LcdI2cTUR::setEntryMode()
{
  LCDWriteCmd(0x0);
  LCDWriteCmd(0b00000111);
  //01 I/D S
  //01  1: Increment 0:decrement 
}
void LcdI2cTUR::InitLCD()
{
  delay(20);
  uint8_t data = 0b11;
  LCDWriteCmd(data); // 00111000
  delayMicroseconds(4200);
  LCDWriteCmd(data);
  delayMicroseconds(100);
  LCDWriteCmd(data);
  data = 0b10;
  LCDWriteCmd(data);
  LCDWriteCmd(data);
  data = 0b1000;
  LCDWriteCmd(data);
  displayON();
  displayClear();
}
void LcdI2cTUR::begin()
{
  InitLCD();
  delay(100);
  addChar(0, cTr);
  addChar(1, GTr);
  addChar(2, STr);
  addChar(3, _gTr);
  addChar(4, ITr);
  addChar(5, _iTr);
}
void LcdI2cTUR::writeData(uint8_t data)
{
   LCDWriteData(data);
}
void LcdI2cTUR::cursorON()
{
  // 000 0 0 0 1 DCB   D:Display 0:off 1:on C:Cursor 0:off 1:on B:Blink 0:off 1:on
 _cursor = 2;
 LCDWriteCmd(0x0); 
 LCDWriteCmd(8 | _display | _cursor | _blink); // | _cursor | _blink);  //1111    //1 D C B   
}
void LcdI2cTUR::cursorOFF()
{
  // 000 0 0 0 1 DCB   D:Display 0:off 1:on C:Cursor 0:off 1:on B:Blink 0:off 1:on
 _cursor = 0;
 LCDWriteCmd(0x0); 
 LCDWriteCmd(8 | _display | _cursor | _blink); // | _cursor | _blink);  //1111    //1 D C B   
}
void LcdI2cTUR::blinkON()
{
  // 000 0 0 0 1 DCB   D:Display 0:off 1:on C:Cursor 0:off 1:on B:Blink 0:off 1:on
 _blink = 1;
 LCDWriteCmd(0x0); 
LCDWriteCmd(8 | _display | _cursor | _blink); // | _cursor | _blink);  //1111    //1 D C B   
}
void LcdI2cTUR::blinkOFF()
{
  // 000 0 0 0 1 DCB   D:Display 0:off 1:on C:Cursor 0:off 1:on B:Blink 0:off 1:on
 _blink = 0;
 LCDWriteCmd(0x0); 
 LCDWriteCmd(8 | _display | _cursor | _blink); // | _cursor | _blink);  //1111    //1 D C B   
}
size_t LcdI2cTUR::write(uint8_t val)
{
  ///////////////////////////////////
   bool sent = 0;

  if (val == 195) sent = 0;
  else if (val == 182) { sent = 1; val = 239;}
  else if (val == 156) { sent = 1; val = 245;}
  else if (val == 188) { sent = 1; val = 245;}
  else if (val == 150) { sent = 1; val = 239;}
  else if (val == 135) { sent = 1; val = byte(0);}//Ç
  else if (val == 167) { sent = 1; val = byte(0);}//ç
  else if (val == 196) { sent = 0; f196 = 1; }
  else if (val == 197) { sent = 0; f197 = 1; }
  else if (val == 158) { sent = 1; if(f196==1) { val = byte(1); f196=0;} else if(f197==1) {val = byte(2); f197=0;} else sent = 0; }
  else if (val == 159) { sent = 1; if(f196==1) { val = byte(3); f196=0;} else if(f197==1) {val = byte(2); f197=0;} else sent = 0; }
  else if (val == 176) { if(f196==1) {sent = 1; val = byte(4); f196=0;} else sent=0;}
  else if (val == 177) { if(f196==1) {sent = 1; val = byte(5); f196=0;} else sent=0;}
  else sent=1;
  if(sent==1)LCDWriteData(val);
  return 1;
  
  
  
  ///////////////////////////////////
}
void LcdI2cTUR::addChar(uint8_t location, uint8_t charSet[])
{
  location &= 15;     //1 
  location = (location << 3);   //1000
  //0100 1000 
  uint8_t temp = 0b01000000;
  temp |= location; // 0100 1000
  LCDWriteCmd((temp & 0b11110000)>>4);
  LCDWriteCmd(temp & 0b00001111);
  
  for (uint8_t i=0; i<8;i++)
  {
    write(charSet[i]);
  }
  setCursor(0,0);
}
void LcdI2cTUR::setCursor(uint8_t col, uint8_t row)
{
  //00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11
  //40
  //1 AD AD AD AD AD AD AD
  uint8_t cursorAddr = 0b10000000; //*111 0000
  if (row == 1)
  cursorAddr = 0b11000000;  // 0100 0000
  cursorAddr+= col;
  
  //uint8_t temp = 0b10000001;
  LCDWriteCmd((cursorAddr & 0b11110000)>>4);
  LCDWriteCmd(cursorAddr & 0b00001111);
}
