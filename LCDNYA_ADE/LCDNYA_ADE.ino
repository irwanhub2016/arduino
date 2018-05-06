//CARA NGETESNYA BIARKAN POWER 5V NYALA
//ABIS ITU CABUT USB NODE DI LAPTOP 5 detik, 
//ABIS ITU COLOKIN LAGI DAH,,, ATAU GA RESTART NODE NYA

//scl->D1
//SDA->D2


#include <LiquidCrystal_I2C.h>

// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(1, 0);

  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HEY");

  lcd.setCursor(5, 1);      
  lcd.print("BELALANG");
 
}

void loop() {
}
