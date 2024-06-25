#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define SS_PIN 10
#define RST_PIN 9
String UID = "C0 D8 9E 13";
String UID1 =  "72 BE 7E 51";
byte lock = 0;

MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
 pinMode(6, OUTPUT);
 pinMode(3, OUTPUT);
 digitalWrite(6, HIGH); 
  SPI.begin();
  rfid.PCD_Init();
  lcd.begin();
   lcd.backlight();
   lcd.clear();
   lcd.print("  RFID DOOR ");
   lcd.setCursor(0,1);
    lcd.print("   LOCK ");
    delay(1000);
     lcd.clear();
}

void loop() {
 lcd.setCursor(0,0);
   lcd.print(" place the card ");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

 
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
   
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == UID ) {
      digitalWrite(6, LOW); 
   digitalWrite(3, LOW); 
   Serial.print("Door is open");
    lcd.setCursor(0,0);
    lcd.print("Door is open ");
delay(3000);
lcd.clear();
 digitalWrite(6, HIGH); 
     Serial.print("Door is locked");
    lcd.setCursor(0,0);
    lcd.print("Door is locked ");
    delay(4000);
     digitalWrite(3, LOW);
   
   
  } else if (ID.substring(1) == UID1  ) {
   digitalWrite(6, LOW); 
   digitalWrite(3, LOW); 
   Serial.print("Door is open");
    lcd.setCursor(0,0);
    lcd.print("Door is open ");
delay(3000);
lcd.clear();
 digitalWrite(6, HIGH); 
     Serial.print("Door is locked");
      lcd.setCursor(0,0);
    lcd.print("Door is locked ");
    delay(4000);
     digitalWrite(3, LOW);
   
   
  } else {
     digitalWrite(3, HIGH); 
    Serial.print("Wrong card!");
   lcd.clear();
     lcd.setCursor(0,0);
    lcd.print("Wrong card! ");
   delay(2000);
    digitalWrite(3, LOW); 
  }
}