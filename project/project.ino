#include <Wire.h>
#include <Adafruit_MLX90614.h> //includerea librariei pentru senzorul de temperatura fara contact
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 

#define LEDr 4      //pin circuit LED-uri rosii
#define LEDv 5      //pin circuit LED-uri verzi
#define buzzer 7    //pin buzzer 
#define trigPin 8   //pin Trigger senzor ultrasunete
#define echoPin 9   //pin Echo senzor ultrasunete
#define pinButon 10 //pin buton on/off
#define LEDon 11    //pin LED on/off

float temp;      //variabile pt calculul temperaturii
int contor = 0;
float sumaTemp;

int distMin = 2; //variabile utilizata pt intervalul de scanare
int distMax = 8;
int data1 = 0;   //variabila utilizata pt citirea de pe seriala
int input = 0; 

long durata, distanta;

bool btn = false; //stare initiala buton
bool led = true;  //var pt dezactivarea/activarea LED-urilor si a sunetului
bool buzz = true;

byte stareLEDon = LOW; //stare initiala led

void setup(){
  
  Serial.begin(9600); //initializare comunicatie seriala
  mlx.begin();        //initializare interfata I2C
  
  pinMode(trigPin, OUTPUT); //setarea pin-ului ca pin de iesire
  pinMode(echoPin, INPUT);  //setarea pin-ului ca pin de intrare
  pinMode(buzzer, OUTPUT);
  pinMode(LEDv, OUTPUT);
  pinMode(LEDr, OUTPUT);
  
  digitalWrite(buzzer ,HIGH);
  pinMode(pinButon, INPUT);
  pinMode(LEDon, OUTPUT);
  
  digitalWrite(pinButon,HIGH);      //activare rezistență de pull-up
  digitalWrite(LEDon, stareLEDon);  //setare stare inițială LED
}

void loop(){

  if(digitalRead(pinButon) == LOW) //verificare daca butonul este apasat
  {    
    while(digitalRead(pinButon) == LOW){} //se așteapta ca butonul să nu mai fie apăsat
                                          //mai exact atâta timp cât pin-ul este în stare LOW
                                          
    btn = !btn;                        //schimbare stare buton 
    stareLEDon = !stareLEDon;          //schimbare stare LED
    digitalWrite(LEDon, stareLEDon);   //setarea noii stari a LED-ului

    digitalWrite(buzzer, LOW);         //activare sunet de confirmare a pornitii
    delay(100);                        //asteptare 100ms 
    digitalWrite(buzzer, HIGH);        //dezactivare sunet
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
  }

  if(btn) //daca sistemul este pornit, adica btn = true    
  {       
      if(Serial.available() > 0) //se verifica daca sunt receptionate date care sunt transmise de la aplicatie prin interfata seriala 
          data1 = Serial.read(); //preluarea caracterului receptionat, la fiecare ciclu al buclei.

      switch(data1){
          case 'A': led = false;  //dezactivare LED-uri
                    //Serial.println("A");
                    break;     
          case 'B': led = true;   //activare LED-uri
                    //Serial.println("B");
                    break;
          case 'C': buzz = false; //dezactivare sunet 
                    //Serial.println("C");
                    break;
          case 'D': buzz = true;  //activare sunet
                    //Serial.println("D");
                    break;
          case 'E': led = false;  //dezactivare LED-uri + sunet
                    buzz = false;
                    //Serial.println("E");
                    break;
          case 'X': distMin = 2;  //modificarea capetelor intervalului de scanare
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
      
      digitalWrite(buzzer, HIGH);      //dezactivare sunet sistem
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);     //aplicare impuls pentru 10 microsecunde pe pinul Trig
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      durata = pulseIn(echoPin, HIGH); //măsurarea lățimii impulsului generat de pinul Echo
      
      distanta = durata*0.034/2;       //calcul distanta cu formula v=d/t

      temp = mlx.readObjectTempC();    //determinarea temperaturii

      if(distanta > distMax){                        //daca mana este detectata inafara intervalului
          Serial.println("Apropiați mâna!-...-..."); //trimitere mesaj pe interfata seriala
          delay(2000);
      }
  
      if(distanta < distMin){    //mâna este detectată prea aproape de sistem
          Serial.println("Mâna este prea aproape!-...-..."); 
          delay(2000);
      }
  
      if((distanta >= distMin) && (distanta <= distMax)){  //daca mana este pozitionata corect
          if(contor == 5){                                 //verificare valoare contor
              afisareTemp();                               //apelare functie pentru afisarea datelor pe interfata seriala 
          }
          else{
              sumaTemp = sumaTemp + temp;    //in caz contrar, se realizeaza suma temperaturilor
              contor++;                      //incrementare contor la fiecare scanare
              delay(200);                    //200 ms intre scanari, in total 5*200 = 1s   
          }
      }
      else{
          delay(100);
          sumaTemp = 0;  //resetarea valorilor 
          contor = 0;
      } 
  }
}
 
void afisareTemp(){
 
  temp = sumaTemp/5;    //calulul mediei aritmetice a temperaturilor detectate intr-o secunda
  
  contor = 0;           //resetare valori contro si suma
  sumaTemp = 0;

  if(temp >= 37.3){     //verificare valoare determinata
      Serial.println("Atenționare!-" + String(temp) + "-" + String(distanta));    //transmitere mesaj pe interfata seriala 
      sunetAtentionare(led,buzz);      //activare modului de atentionare                                           
   }
   else{
      Serial.println("Se primesc informații...-" + String(temp) + "-" + String(distanta));  //transmitere mesaj pe interfata seriala 
      sunetNormal(led,buzz);           //confirmarea scanarii
   }
  delay(2000); //2s
}

void sunetNormal(bool led,bool buzz){

    if(led == true && buzz == true)     //verificare daca LED-urile si sunetul sunt activate din setarile aplicatiei
    {
        for(int i=1; i<=3; i++)         //realizarea modului de confirmare a unei scanari 
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
    if(led == false && buzz == true)    //cazul in care LED-urile sunt dezactivate din setari 
    {
         for(int i=1; i<=3; i++)
         {
            digitalWrite(buzzer, LOW);
            delay(150);
            digitalWrite(buzzer, HIGH);
            delay(250);
         }      
    }
    if(led == true && buzz == false)    //cazul in care LED-urile si sunetul sunt dezactivate din setari
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
    
     if(led == true && buzz == true)    //verificare daca LED-urile și sunetul sunt activate 
     {
        for(int i=1; i<=4; i++)         //realizarea modului de alertă, atunci cand temperaturii detectata este ridicata
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
     if(led == false && buzz == true)   //cazul in care LED-urile sunt dezactivate din setari
     {
        for(int i=1; i<=4; i++)
        {
            digitalWrite(buzzer, LOW);
            delay(200);
            digitalWrite(buzzer, HIGH);
            delay(250);
         } 
     }
     if(led == true && buzz == false)   //cazul in care LED-urile si sunetul sunt dezactivate din setari
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
