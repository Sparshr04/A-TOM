#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x3B, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);
int buz = 8;
int led = 9;

const int aqsensor = A0;
int threshold = 36;
int alpha = 1;
void setup() {

  pinMode (buz,OUTPUT);
  pinMode (led,OUTPUT);
  pinMode (aqsensor,INPUT);

  Serial.begin (9600);

  lcd1.init();   
  lcd2.init();
  lcd1.backlight();
  lcd2.backlight();       
}

void loop() {

  int ppm = analogRead(aqsensor);
  lcd1.setCursor(0, 0);
  lcd1.print("Breathing Air.....");
  Serial.print("Air Quality: ");
  Serial.println(ppm);
 while (alpha < 100) {
  lcd2.setCursor(1, 0);
  lcd2.print("Hello I'm ATOM ");
  lcd2.setCursor(0, 1);
  lcd2.print("Let's OXygenate!");
  alpha = alpha +1;
 }
  lcd1.setCursor(0, 0);
  lcd1.print("Air Quality: ");
  lcd1.print(ppm);
  lcd2.setCursor(0, 0);
  lcd2.print("  Lung Health: ");
  if (ppm > 50 & ppm < 98){
      lcd1.setCursor(0,1);
      lcd1.print("AQ Lv: Bad      ");
      Serial.println("AQ Lv: Bad");     
      tone(led,1000,200);       
      digitalWrite(buz,HIGH);
      digitalWrite(led,LOW);
      lcd2.setCursor(0, 1);
      lcd2.print("Poor : below 40%      "); 
  }
  else if (ppm < threshold){
      digitalWrite(buz,LOW);
      digitalWrite(led,LOW);
      lcd1.setCursor(0,1);        
      lcd1.print("AQ Lv: Good    ");
      Serial.println("AQ Lv: Good");     
      tone(led,1000,200);
      lcd2.setCursor(0, 1);
      lcd2.print(" Best : 60%-80%       ");         
  }
  else if (ppm > threshold & ppm <50){
      lcd1.setCursor(0,1);
      Serial.println("AQ Level Moderate");
      lcd1.print("AQ Lv: Moderate");     
      tone(led,1000,200);       
      digitalWrite(buz,LOW);  
      lcd2.setCursor(0, 1);
      lcd2.print("Average: 50%-60%        ");
  }
  else{
      digitalWrite(buz,LOW);
      digitalWrite(led,LOW);
      lcd1.setCursor(0,1);        
      lcd1.print("AQ Lv: NaN     ");
      Serial.println("AQ Lv: NaN"); 
      lcd2.setCursor(0, 1);
      lcd2.print("      NaN          ");
  }
  delay (500);
}