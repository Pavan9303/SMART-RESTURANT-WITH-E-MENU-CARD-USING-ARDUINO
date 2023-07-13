#include <string.h>
#include <SoftwareSerial.h>
SoftwareSerial bluetoothSerial(2, 3); // RX, TX
String voice;
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x3F,16,2);
#define BUZZER_PIN 12
#define sw 14
void buz()
{
for(int k =0;k<2;k++)
{
digitalWrite(BUZZER_PIN, HIGH);
delay(800); 
digitalWrite(BUZZER_PIN, LOW);
delay(300);
}
}
void setup()
{
pinMode(sw, INPUT_PULLUP);
// pinMode(led, OUTPUT);
lcd.backlight();
lcd.init();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("SMART RESTAURENT");
lcd.setCursor(0,1);
lcd.print(" E-MENU CARD ");
delay(3000);
Serial.begin(9600);
bluetoothSerial.begin(9600); //Set the baud rate to your Bluetooth module.
Serial.println("SMART RESTAURENT E-MENU CARD");
bluetoothSerial.println("SMART RESTAURENT E-MENU CARD");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Waiting for ");
lcd.setCursor(0,1);
lcd.print(" input...... ");
delay(1000);
}
void loop()
{
while (bluetoothSerial.available()){
delay(10);
char c = bluetoothSerial.read();
voice += c;
}
if(voice.length() > 0)
{
if(voice[0] == '*')
{
//forward();
voice.remove(0,1);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(voice);
Serial.println(voice);
bluetoothSerial.print(voice);
bluetoothSerial.println(" ORDER RECEIVED");
buz();
}
else
{
}
voice=""; //Reset the variable after initiating
}
if(digitalRead(sw)==0)
{
lcd.setCursor(0,0);
lcd.print("Waiting for ");
lcd.setCursor(0,1); 
lcd.print("input ...... ");
delay(1000);
}
}