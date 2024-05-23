#include <ThreeWire.h>    
#include <RtcDS1302.h>
#include <LiquidCrystal.h>
#include <AFMotor.h>        

ThreeWire myWire(26,24,28); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal lcd(30, 32, 34, 36, 38, 40);

AF_Stepper stepper1(20,1);
AF_Stepper stepper2(20,2); 

const int taster1=52,taster2=50,taster3=48,dioda=44,buzzer=22;  

struct inputs {
  int brt;
  String h;
  String min; 
  bool done;
};
struct inputs vremena[10];
int i=0,prva_tableta=6,druga_tableta=6;

void setup () 
{
 lcd.begin(16,2);
 stepper1.setSpeed(200);
 stepper2.setSpeed(200);
 Serial.begin(9600);
 Rtc.Begin();
 RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
 int sati=0,minute=0,b=0;
 pinMode (taster1, INPUT);
 pinMode (taster2, INPUT);
 pinMode (taster3, INPUT);
 pinMode (dioda, OUTPUT);
 pinMode (buzzer, OUTPUT);
 for(int brtab=1;brtab<3;brtab++){
  delay(500);
  b=1;   
  while(1){
   //početak unosa
   lcd.clear();
   lcd.print("Unos tablete ");
   lcd.print(brtab);
   lcd.setCursor(0,1);
   lcd.print(sati);
   lcd.print(":");
   lcd.print(minute);
    if(digitalRead(taster1)==HIGH){
     if(b==1)
       sati++;
     if(b==2)
       minute=minute+5;
     if(sati>23)
       sati=0;
     if(minute>58)
       minute=0;

     while(1){
       if(digitalRead(taster1)==LOW)
        break;
     }
    }
   
    if(digitalRead(taster2)==HIGH){

     if(sati==0)
        break;
  
     b++;

     while(1){
  
       if(digitalRead(taster2)==LOW)
          break;
      }

     if(b>2){
       vremena[i].brt=brtab;
       vremena[i].h=String(sati);
       vremena[i].min=String(minute);
       vremena[i].done=false;
       i++;
       b=1;
       sati=0;
       minute=0;
      }
    }
    delay(100);
  }
}
}
void loop () 
{
  String sati,minute;
  
  RtcDateTime now = Rtc.GetDateTime();
  sati=now.Hour();
  minute=now.Minute();
  if(prva_tableta==0 || druga_tableta==0){
    digitalWrite(dioda,HIGH);
    lcd.clear();
    lcd.print("NAPUNITE");
    lcd.setCursor(0,1);
    lcd.print("SPREMNIK");
    delay(2000);
  }
  for(int j=0;j<i;j++){

    if((sati==vremena[j].h)&&(minute==vremena[j].min)){

      if(vremena[j].brt==1 && vremena[j].done==false && prva_tableta>0){

        stepper1.step(32,FORWARD,MICROSTEP);
        stepper1.release();
        vremena[j].done=true;
        prva_tableta--;
        lcd.clear();
        lcd.print("UZMITE TABLETU");

        while(1){
          digitalWrite(dioda,HIGH);
          digitalWrite(buzzer,HIGH);

          if(digitalRead(taster3)==HIGH){
            digitalWrite(buzzer,LOW);
            if(digitalRead(taster3)==LOW){
              digitalWrite(dioda,LOW);
              break;
            }
          }
        
        }

      }
      
      if(vremena[j].brt==2 && vremena[j].done==false && druga_tableta>0){
        stepper2.step(35,FORWARD,MICROSTEP);
        stepper2.release();
        vremena[j].done=true;
        druga_tableta--;
        lcd.clear();
        lcd.print("UZMITE TABLETU");

        while(1){
          digitalWrite(dioda,HIGH);
          digitalWrite(buzzer,HIGH);

          if(digitalRead(taster3)==HIGH){
            digitalWrite(buzzer,LOW);
            if(digitalRead(taster3)==LOW){
              digitalWrite(dioda,LOW);
              break;
            }
          }
       }
      }
    }
   else
     vremena[j].done=false;
  }
 if(digitalRead(taster1)==HIGH){
   for(int j=0;j<6-prva_tableta;j++){
     stepper1.step(32,BACKWARD,MICROSTEP);
     stepper1.release();
   }
  prva_tableta=6;
  digitalWrite(buzzer,LOW);
  digitalWrite(dioda,LOW);
 }
 if(digitalRead(taster2)==HIGH){
  for(int j=0;j<6-druga_tableta;j++){
  stepper2.step(35,BACKWARD,MICROSTEP);
  stepper2.release();
  }
  druga_tableta=6;
  digitalWrite(buzzer,LOW);
  digitalWrite(dioda,LOW);
 }
 lcd.clear();
 lcd.print(sati);
 lcd.setCursor(16-prva_tableta,0);
 for(int j=0;j<prva_tableta;j++)
    lcd.print("*");
 lcd.setCursor(0,1);
 lcd.print(minute);
 lcd.setCursor(16-druga_tableta,1);
 for(int j=0;j<druga_tableta;j++)
    lcd.print("*");
 delay(2000); 
}



// CONNECTIONS:
// DS1302 CLK/SCLK --> 24
// DS1302 DAT/IO --> 26
// DS1302 RST/CE --> 28
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND
//The circuit:
 //LCD RS pin to digital pin 30
 //LCD Enable pin to digital pin 32
 //LCD D4 pin to digital pin 34
 //LCD D5 pin to digital pin 36
 //LCD D6 pin to digital pin 38
 //LCD D7 pin to digital pin 40
 //LCD R/W pin to ground
 //LCD VSS pin to ground
 //LCD VCC pin to 5V
 //10K resistor:
   //ends to +5V and ground
   //wiper to LCD VO pin (pin 3)
//desni taster -->50
//lijevi taster -->52
//taster za ladicu -->44
//dioda -->48
