#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include "GravityTDS.h"
// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);


#define TdsSensorPin A1
GravityTDS gravityTds;
double temperature = 25, w = 0;


///////////////////////////////////////////////////////

float volt;
float ntu;
///////////////////////////





void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  sensors.begin();
  pinMode(A1,INPUT);  // TDS 
  pinMode(A0,INPUT); //ph
  pinMode(A2,INPUT);  // Turbidity sensor 
  
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("IOT Based Water");
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print(" Manag. System  ");
  delay(2000);
  lcd.clear();

}

void loop() {
  
   tdstemp();
   turbitity ();
   Ph();
   Serial.print("W");
   Serial.print(w); // Print ppm values
}



/////////////////////////////////////
void Ph ()
{
  int a=analogRead(A0);
//  Serial.println(a);
 
if(a>200 && a< 450)
{
 lcd.setCursor(7,0);
 lcd.print("PH:NOR ");
 //lcd.print("ACID HIGH  ");
 digitalWrite(A5,LOW);///buzzer
 Serial.print("X");// Normal
 delay(100); 
 Serial.print("y");
  delay(100); 
 Serial.print("z");
  delay(100); 
 }
   if(a>50 && a<200)
  {
        lcd.setCursor(7,0);
        lcd.print("PH:ACD ");
      
         Serial.print("x");
          delay(100); 
         Serial.print("Y");//ACID
          delay(100); 
         Serial.print("z");
          delay(100); 
    }
 if (a> 456 && a<500)
 
  {
    lcd.setCursor(7,0);
    lcd.print("PH:ALN ");
    digitalWrite(A5,HIGH);///buzzer
     Serial.print("x");
      delay(100); 
     Serial.print("y");
      delay(100); 
     Serial.print("Z");//ALKALINE
      delay(100); 
    }
  
}

 
void turbitity ()
{
  int sensorValue = analogRead(A2);
  float v = sensorValue * (5.0 / 1024.0);
  lcd.setCursor(0,1);
  lcd.print("WQ:");
  lcd.print(v);
  
 if (v<2.3)
 {
  lcd.setCursor(8,1);
  lcd.print("Not GOOD");

  Serial.print("C");
  delay(100); 
 }
  else if (v>3.0)
  {
    lcd.setCursor(8,1);
    lcd.print("  GOOD  ");

    Serial.print("c");
 delay(100); 
  }
  
  else 
  {
//  Serial.print("InsertSen");
  } 
//  Serial.println ("Sensor Output (V):");
//  Serial.println (v);
//  Serial.println();
//  delay(1000);
}

void tdstemp()
{
//temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
     w = gravityTds.getTdsValue();  // then get the value
    
    delay(100);
    
    // lcd.setCursor(0,1);
    // lcd.print(w);
    if (w > 300)
    {
    lcd.setCursor(14,0);
    lcd.print("T:B");
    Serial.print("B");
    delay(100);
    }
    else
    {
    lcd.setCursor(14,0);
    lcd.print("T:G");
    Serial.print("b");
    delay(100);
    } 
}
