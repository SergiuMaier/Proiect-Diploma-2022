#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 

#define LEDr 4
#define LEDv 5
#define buzzer 7
#define trigPin 8
#define echoPin 9
#define pinButon 10 
#define LEDon 11

float temp;     
int contor = 0;
float sumaTemp;

int distMin = 2;
int distMax = 8;
int data1 = 0;
int input = 0; 

long durata, distanta;

bool btn = false;
bool led = true;
bool buzz = true;

byte stareLEDon = LOW;

void setup(){
  
  Serial.begin(9600); 
  mlx.begin(); 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(LEDv, OUTPUT);
  pinMode(LEDr, OUTPUT);
  digitalWrite(buzzer ,HIGH);
 
  pinMode(pinButon, INPUT);
  pinMode(LEDon, OUTPUT);
  
  digitalWrite(pinButon,HIGH); 
  digitalWrite(LEDon, stareLEDon);  
}

void loop(){

  if(digitalRead(pinButon) == LOW)
  {    
    while(digitalRead(pinButon) == LOW){}
   
    btn = !btn;
    stareLEDon = !stareLEDon;
    digitalWrite(LEDon, stareLEDon);

    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
  }

  if(btn) //btn = true
  {           
      if(Serial.available() > 0)
          data1 = Serial.read();

      switch(data1){
          case 'A': led = false;
                    //Serial.println("A");
                    break;     
          case 'B': led = true;
                    //Serial.println("B");
                    break;
          case 'C': buzz = false;
                    //Serial.println("C");
                    break;
          case 'D': buzz = true;
                    //Serial.println("D");
                    break;
          case 'E': led = false;
                    buzz = false;
                    //Serial.println("E");
                    break;
          case 'X': distMin = 2;
                    distMax = 8;
                    break;
          case 'Y': distMin = 2;
                    distMax = 5;
                    break;
          case 'Z': distMin = 5;
                    distMax = 8;
                    break;
          default: break;
      }
      
      digitalWrite(buzzer, HIGH);
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      durata = pulseIn(echoPin, HIGH);
      
      distanta = durata*0.034/2;

      temp = mlx.readObjectTempC();

      if(distanta > distMax){
          Serial.println("Apropiați mâna!-...-..."); 
          delay(2000);
      }
  
      if(distanta < distMin){
          Serial.println("Mâna este prea aproape!-...-..."); 
          delay(2000);
      }
  
      if((distanta >= distMin) && (distanta <= distMax)){
          if(contor == 5){
              afisareTemp(); 
          }
          else{
              sumaTemp = sumaTemp + temp;
              contor++;
              delay(200);    //5*200 ms = 1s
          }
      }
      else{
          delay(100);
          sumaTemp = 0;  
          contor = 0;
      } 
  }
}
 
void afisareTemp(){
 
  temp = sumaTemp/5;
  
  contor = 0;
  sumaTemp = 0;

  if(temp >= 37.3){
      Serial.println("Atenționare!-" + String(temp) + "-" + String(distanta));
      sunetAtentionare(led,buzz);     
   }
   else{
      Serial.println("Se primesc informații...-" + String(temp) + "-" + String(distanta));
      sunetNormal(led,buzz);    
   }
  delay(2000); //2 sec
}

void sunetNormal(bool led,bool buzz){

    if(led == true && buzz == true)
    {
        for(int i=1; i<=3; i++)
        {
            digitalWrite(buzzer, LOW);
            delay(100);
            digitalWrite(buzzer, HIGH);
            delay(100);
        
            digitalWrite(LEDv, HIGH);
            delay(100);
            digitalWrite(LEDv, LOW);
            delay(100); 
         }
    }
    if(led == false && buzz == true)
    {
         for(int i=1; i<=3; i++)
         {
            digitalWrite(buzzer, LOW);
            delay(150);
            digitalWrite(buzzer, HIGH);
            delay(250);
         }      
    }
    if(led == true && buzz == false)
    {
         for(int i=1; i<=3; i++)
         {
            digitalWrite(LEDv, HIGH);
            delay(200);
            digitalWrite(LEDv, LOW);
            delay(200); 
         }   
    }
}

void sunetAtentionare(bool led,bool buzz){
    
     if(led == true && buzz == true)
     {
        for(int i=1; i<=4; i++)
        {
            digitalWrite(buzzer, LOW);
            delay(200);
            digitalWrite(buzzer, HIGH);
            delay(100);
                
            digitalWrite(LEDr, HIGH);
            delay(200);
            digitalWrite(LEDr, LOW);
            delay(100); 
         }
     }
     if(led == false && buzz == true)
     {
        for(int i=1; i<=4; i++)
        {
            digitalWrite(buzzer, LOW);
            delay(200);
            digitalWrite(buzzer, HIGH);
            delay(250);
         } 
     }
     if(led == true && buzz == false)
     {
        for(int i=1; i<=4; i++)
        {
            digitalWrite(LEDr, HIGH);
            delay(200);
            digitalWrite(LEDr, LOW);
            delay(100); 
         } 
     } 
}
