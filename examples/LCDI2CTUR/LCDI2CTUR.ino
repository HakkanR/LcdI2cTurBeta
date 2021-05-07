#include <LcdI2cTUR.h>
LcdI2cTUR lcd();
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup() {

lcd.begin();
  delay(500);
 lcd.setCursor(0,0);
 lcd.print("Giriş Yapınız!");
 delay(2000);
 lcd.displayClear();
 lcd.print("Giriş Yapmayınız!");

}

void loop() {

}
