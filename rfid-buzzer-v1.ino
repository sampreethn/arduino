# Sampreeth's RFID with LCD and buzzer project
# This uses Elegoo Mega Board


#include <LiquidCrystal.h>
#include <SPI.h>
#include <RFID.h>
#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53  
 
#define GREEN 2
#define RED 3

int redValue;
int greenValue;


RFID rfid(SS_PIN, RST_PIN);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
String rfidCard;
void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
  pinMode(14, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN,HIGH);
  digitalWrite(RED,LOW);
   digitalWrite(GREEN,LOW);

  
}
void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      if (rfidCard == "18 6 13 40") {   // This uses my RFID card's UID in order for the program to work give your RFID card's UID code by going to examples and MFRC-522>>write_personell_data and running that code, clicking on the serial monitor and scanning the card in front of the reader 
         Serial.println("Family member:granted");
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        delay(100);
        digitalWrite(GREEN, HIGH);
        lcd.begin(17, 2);
        lcd.print("Family Member:");
        lcd.setCursor(0, 1);
        lcd.print("Granted...");
        delay(1000);
        lcd.begin(17, 2);
        lcd.print("");
        digitalWrite(GREEN,LOW);
        
      }
      
      if (rfidCard == "136 4 36 179") {// This uses my RFID card's UID in order for the program to work give your RFID card's UID code by going to examples and MFRC-522>>write_personell_data and running that code, clicking on the serial monitor and scanning the card in front of the reader
         Serial.println("Sampreeth:granted");
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        digitalWrite(GREEN, HIGH);
        lcd.begin(17, 2);
        lcd.print("Sampreeth:");
        lcd.setCursor(0, 1);
        lcd.print("Granted...");
        delay(1000);
        lcd.begin(17, 2);
        lcd.print("");
        digitalWrite(GREEN,LOW);
      }
            
      if (rfidCard == "103 37 187 28") {// This uses my RFID card's UID in order for the program to work give your RFID card's UID code by going to examples and MFRC-522>>write_personell_data and running that code, clicking on the serial monitor and scanning the card in front of the reader
         Serial.println("Intruder:Denied");
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        delay(100);
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        delay(100);
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        delay(100);
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        delay(100);
        digitalWrite(14, HIGH);
        delay(100);
        digitalWrite(14, LOW);
        delay(100);
        lcd.begin(17, 2);
        digitalWrite(RED, HIGH);
        lcd.print("Intruder:");
        lcd.setCursor(0, 1);
        lcd.print("Denied...");
        delay(1000);
        lcd.begin(17, 2);
        lcd.print("");
        digitalWrite(RED, LOW);

      }


    rfid.halt();
  }
  }}
