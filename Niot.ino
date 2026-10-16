/*
amruthav436@gmail.com
blynk password: Projectiot2023
 */

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3OYYl3drX"
#define BLYNK_TEMPLATE_NAME "waterquality"
#define BLYNK_AUTH_TOKEN "LLXBIn26Jhs3ac0uwMGcBPnm3wUb5cpI"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Projectiot";
char pass[] = "";


//Change the virtual pins according the rooms
#define VPIN_1    V0  // TDS_Status
#define VPIN_2    V1  // TDS_Value 
#define VPIN_3    V2  // Turbitity 
#define VPIN_4    V3  // Ph // acid
#define VPIN_5    V4  // Ph // base
#define VPIN_6    V5  // ph // normal


BLYNK_CONNECTED()
{
  Blynk.syncVirtual(VPIN_1);
  Blynk.syncVirtual(VPIN_2);
  Blynk.syncVirtual(VPIN_3);
  Blynk.syncVirtual(VPIN_4);
  Blynk.syncVirtual(VPIN_5);
  Blynk.syncVirtual(VPIN_6);

}


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  if (Serial.available()>0) 
  {
  char a=Serial.read();
   Serial.print(a);
    
    if(a=='B') 
    {  
      Blynk.virtualWrite(VPIN_1,HIGH);  // TDS
    }
    if(a=='b')
    {  
      Blynk.virtualWrite(VPIN_1,LOW); 
    }

     if(a=='W') //// Tds Value
     {  
      int d=Serial.parseInt(); 
      Blynk.virtualWrite(VPIN_2,d); 
    }

    if(a=='C')
    {  
      Blynk.virtualWrite(VPIN_3,HIGH); // Turbitity 
    }
    if(a=='c')
    {  
      Blynk.virtualWrite(VPIN_3,LOW); 
    }
    
    if(a=='X')
    {  
      Blynk.virtualWrite(VPIN_4,HIGH); //Ph Acid High
    }
    if(a=='x')
    {  
      Blynk.virtualWrite(VPIN_4,LOW); //Ph Acid Low
    }

    if(a=='Y')
    {  
      Blynk.virtualWrite(VPIN_5,HIGH); //Ph Base High
    }
    if(a=='y')
    {  
      Blynk.virtualWrite(VPIN_5,LOW); //Ph Base Low
    }

    if(a=='Z')
    {  
      Blynk.virtualWrite(VPIN_6,HIGH); //ph Normal
    }
    if(a=='z')
    {  
      Blynk.virtualWrite(VPIN_6,LOW); //ph normal
    }    
     
    }
 }
