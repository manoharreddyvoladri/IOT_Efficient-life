#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
 #include <EEPROM.h>
 int flag=0;
 int ir=7;
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 3
Servo myservo;
int led=5;
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
void setup()
{
pinMode(led,OUTPUT);
Serial.begin(9600); // Initiate a serial communication
SPI.begin(); // Initiate SPI bus
mfrc522.PCD_Init(); // Initiate MFRC522
myservo.attach(SERVO_PIN);
// myservo.write( 70 );
// delay(7500);
myservo.write( 0 );
pinMode(ir,INPUT);
Serial.println("Put your card to the reader...");
Serial.println();
}
void loop()
{

if(!digitalRead(ir)){
  digitalWrite(led,LOW);
  myservo.write( 0 );
  delay(500);
  // Serial.println("motion detected");
}

// Look for new cards+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
//Show UID on serial monitor
Serial.print("UID tag :");

String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
Serial.print("Message : ");
content.toUpperCase();
if (content.substring(1) == "F5 D8 FB 5B") //change here the UID of the card  93 6D 3E A6,    08 0D 8A AD
{
Serial.println("Authorized access");
Serial.println();
digitalWrite(led,HIGH);
myservo.write( 180 );
delay(500);
}
else {
Serial.println(" Access denied");

delay(DENIED_DELAY);

}

}
