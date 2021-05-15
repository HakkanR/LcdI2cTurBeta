#include "LcdI2cTUR.h"
LcdI2cTUR lcd(0x27);   // i2c adresiniz 0x27 den farklıysa parantez içindeki değeri değiştirin.
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
lcd.addChar(6,heart);   // 6 cgram bölgesine kalp şeklindeki karakteri atar
lcd.addChar(7,armsUp);  // 7 cgram bölgesine eller havada şeklindeki karakteri atar
lcd.cursorOFF();        // imleçi kapatır.
lcd.blinkOFF();         // üzerine yaz işaretini kapatır.
lcd.setCursor(4,0);     // imleci 0. satır 4. sutuna konumlandırır.
lcd.print("Made  in");  // ekrana "Made in" yazar..
delay(3000);
lcd.backlightsOFF();    // ışıkları kapatır
lcd.setCursor(4,1);
lcd.print("Türkiye!");
delay(3000);
lcd.backlightsON();     // ışıkları açar
delay(500);
lcd.setCursor(2,1);
lcd.write(6);           // cgRam'in 6 hanesine yazılan kalp simgesini ekrana yazar.
delay(500);
lcd.setCursor(13,1);
lcd.write(7);
for (char a = 1; a<3; a++)
{
  lcd.backlightsOFF();
  delay(200);
  lcd.backlightsON();
  delay(200);
}
lcd.goHome();           //ddram adres sayacını sıfırlar, imleci 0,0 a adresler
}

void loop() {
 lcd.displayClear();    //ekranı temizler
  lcd.setCursor(5,0);
  lcd.print("OtoKaydır.");
  lcd.setCursor(8,1);
  lcd.autoScroll();     //otomatik yazı kaydırmayı aktif eder.
  for (uint8_t i=0; i < 7; i++)
  {
    lcd.print(i);
    delay(500);
  }
  lcd.NoAutoScroll();   //otomatik yazı kaydırmayı pasif eder.
  lcd.displayClear();
  lcd.cursorON();       //imleç gösterimini aktif eder.
  delay(2000);
  lcd.blinkON();        //üzerine yaz işaretini açar
  delay(2000);
  lcd.goHome();
  lcd.displayClear();
  lcd.setCursor(10,0);
  lcd.print("<< Sola Kaydır");
  for (uint8_t i=0; i < 10; i++)
  {
    lcd.displayShiftLeft();       //ekranı sola kaydırır.
    delay(500);
  }
  delay(3000);
  lcd.goHome();
  lcd.displayClear();
  lcd.print(">> sağa kaydır");
  for (uint8_t i=0; i < 10; i++)
  {
    lcd.displayShiftRight();      //ekranı sağa kaydırır.
    delay(500);
  }
  
}
