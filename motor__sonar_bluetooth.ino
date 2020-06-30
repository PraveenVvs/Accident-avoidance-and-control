#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // 10-tx 11-rx
AF_DCMotor motor(4);  
#define trig_pin 5 
#define echo_pin 6 
int ssensor=A0;   
int gsensor=A2;   
int gas_value;   
int sound_value;
int x=1;
int b=1;  
void setup()
{
  motor.setSpeed(200);
  motor.run(RELEASE);
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(ssensor,INPUT);
  pinMode(gsensor,INPUT);
  pinMode(2,OUTPUT);
   //mySerial.begin(9600);
  Serial.begin(9600);
   delay(100);
}
void loop() 
{
  long a,duration,distance;
  char c;
    gas_value=analogRead(gsensor);
    sound_value=analogRead(ssensor);
    
    digitalWrite(trig_pin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    duration = pulseIn(echo_pin, HIGH);
    distance = (duration/2) / 29.1;

    if(Serial.available())
    {
      c=Serial.read();
      if(c=='1')
      {

       b=1;
      
      }
      else if(c=='2')
      {
        b=2;
       
      }
      else if(c=='3')
      {
        b=3;
      
      }
      
    }
    if(b==1)
    {
       Serial.print(distance);
      Serial.println(" cm");
    }
    if(b==2)
    {
       Serial.print(gas_value);
        Serial.println(" mg");
    }
    if(b==3)
    {
       Serial.print(sound_value,DEC);
       Serial.println(" hz");
    }
   if(distance<5)
   {
    SendMessage();
   }
    
  
}
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918978716120\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Danger detected");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  x+=1;
  
}
