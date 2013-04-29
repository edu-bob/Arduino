#include <LiquidCrystal.h>

#define LEDPIN 13
#define INTERVAL 250

int led = 1;
unsigned long nextTime;

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
void setup() {
  // set up the heartbeat LED
  pinMode(LEDPIN,OUTPUT);
  nextTime = millis();
  
  // set up the runn mode switch
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);

  // set up the LCD display
  lcd.begin(20, 4);
  lcd.clear();
  lcd.home();
  lcd.print("Liquid crystal test");
  
  // set up the interface to the scoreboard
  Serial1.begin(9600);
}

void loop() {
  if ( millis() >= nextTime ) {
    nextTime += INTERVAL;
    digitalWrite(LEDPIN, led);
    led = !led;
    
    // update the lcd
    lcd.setCursor(0,1);
    lcd.print(millis());
    
    Serial1.print("s");
    Serial1.println(millis()%10000);
    
    // Show the SCSI switch on the LCD
    int val = (((digitalRead(12)<<1) | digitalRead(11))<<1) | digitalRead(12);
    lcd.setCursor(0,2);
    lcd.print("SCSI switch: ");
    lcs.print(val);
  }
}
