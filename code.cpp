/* Arduino uno r3 code
it should have the RFID library


// #include<LiquidCrystal.h>
// LiquidCrystal lcd(13,12,11,10,9,8);
#define in 5
#define out 4
#define relay 2
int count=0;
void IN()
{
count++;
Serial.println("Person In Room:");
Serial.println(count);
Serial.println("lights are on");
delay(100);
}
void OUT()
{
if(count>0)
count--;
Serial.println("Person In Room:");
Serial.println(count);
delay(100);
}
void setup()
{
Serial.begin(9600);
Serial.println("Visitor Counter");
delay(2000);
pinMode(in, INPUT);
pinMode(out, INPUT);
pinMode(relay,OUTPUT);
}
void loop()
{
if(digitalRead(in))
IN();
if(digitalRead(out))
OUT();
if(count<=0)
{
digitalWrite(relay, LOW);
Serial.println("Nobody In Room");
Serial.println("Light Is Off");
delay(10);
}
else
digitalWrite(relay, HIGH);
delay(500);
}
