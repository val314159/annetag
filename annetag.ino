#include "rgb_lcd.h"
#include <Wire.h>
#include <ADXL345.h>
extern ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
#include "acc.h"
rgb_lcd lcd;
int colorR = 255;
int colorG = 0;
int colorB = 0;

const char *quotes[] = {
  "Im Award bitchz",
  "I luv SEO&rock.",
  NULL };

void forwardColors(){
  if(colorR){
    colorR=0;
    colorG=255;
  }else if(colorG){
    colorG=0;
    colorB=255;
  }else if(colorB){
    colorB=0;
    colorR=255;
  }
  lcd.setRGB(colorR, colorG, colorB);
}

const int ledPin    = 4;
const int touchPin  = 3;

int lastSensorValue = -99;
int sensorValue = 0;

void msg(char*message){
  lcd.setCursor(15, 0);
  lcd.print(message);
}

int mode = 0;

void xmsg(int x, int y, int z, double i, double j, double k){
  lcd.setCursor(0, 0);
  if(mode==0){
    lcd.printf("%d,%d,%d;       ",x,y,z);
    mode++;
  }else if(mode==1){
    lcd.printf(quotes[0]);
    mode++;
  }else if(mode==2){
    lcd.printf(quotes[1]);
    mode++;
  }else{
    lcd.printf("%d,%d,%d;",x,y,z);
    mode = 0;
  }
  lcd.setCursor(0, 1);
  //lcd.printf("%.2lf,%.2lf,%.2lf;",i,j,k);
  lcd.printf("- @annebot says.");
}

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(touchPin, INPUT);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  setup_acc();
  delay(100);
}

void senseTouch(){
  sensorValue = digitalRead(touchPin);
  if (sensorValue!=lastSensorValue){
    forwardColors();
    if (sensorValue==1){
      digitalWrite(ledPin, HIGH);
      msg("Y");
    } else {
      digitalWrite(ledPin, LOW);
      msg("N");
    }
    lastSensorValue = sensorValue;
  }
}

void loop(){
  loop_acc();
  for (int ndx=0;ndx<10;ndx++){
    senseTouch();
    delay(100);
  }
}
