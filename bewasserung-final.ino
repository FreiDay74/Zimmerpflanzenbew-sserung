#include "arduino_secrets.h"

int sensorTopf1Pin = A1;
int sensorTopf2Pin = A2;
int sensorTopf3Pin = A3;

int pumpeTopf1Pin = 11;
int pumpeTopf2Pin = 12;
int pumpeTopf3Pin = 13;

// festlegen der Grenzwerte zum Pumpen
int sollTopf1 = 300;
int sollTopf2 = 300;
int sollTopf3 = 300;

//Startwerte festlegen
int istTopf1 = 700;
int istTopf2 = 700;
int istTopf3 = 700; 

void(* resetFunc) (void) = 0; // erstellt eine Neustartfunktion

void setup() {
  
  // Alle Sensorpins als EingÃ¤nge
  pinMode(sensorTopf1Pin, INPUT);
  pinMode(sensorTopf2Pin, INPUT);
  pinMode(sensorTopf3Pin, INPUT);

  //Alle Pumpenpins als AusgÃ¤nge
  pinMode(pumpeTopf1Pin, OUTPUT);
  pinMode(pumpeTopf2Pin, OUTPUT);
  pinMode(pumpeTopf3Pin, OUTPUT);

  //Pumpen am Anfang ausmachen
  digitalWrite(pumpeTopf1Pin,LOW);
  digitalWrite(pumpeTopf2Pin,LOW);
  digitalWrite(pumpeTopf3Pin,LOW);
  
  Serial.begin(9600); //Baudrate festlegen
  
}
      
void loop() {
  //Wartezeit fÃ¼r die Senoren zu Beginn
  delay(200);
  Serial.println(".");
  //Messen...
  istTopf1 = analogRead(sensorTopf1Pin);
  istTopf2 = analogRead(sensorTopf2Pin);
  istTopf3 = analogRead(sensorTopf3Pin);
  
  //... Werte seriell ausgeben...
  Serial.println("Wasser Topf 1: ");
  Serial.println(istTopf1);
  Serial.println("\t");   
  Serial.print("Wasser Topf 2: ");
  Serial.print(istTopf2);
  Serial.print("\t");   
  Serial.print("Wasser Topf 3: ");
  Serial.print(istTopf3);   
  Serial.println("\t");   

  //...und bei Bedarf pumpen
  if(istTopf1 > sollTopf1) 
    {
      digitalWrite(pumpeTopf1Pin, HIGH);
      Serial.println("Topf1 zu trocken!!!"   );
      Serial.println("\t");
      delay(3000);
      digitalWrite(pumpeTopf1Pin, LOW);
    } 
  else
    {
      Serial.println("Topf1 ist ok!"); 
      Serial.println("\t");
      Serial.println("\t");
    }
    
  if(istTopf2 > sollTopf2) 
    {
      digitalWrite(pumpeTopf2Pin, HIGH);
      Serial.print("Topf2 zu trocken!!!"   );
      Serial.print("\t");
      delay(3000);
      digitalWrite(pumpeTopf2Pin, LOW);
    } 
  else
    {
      Serial.print("Topf2 ist ok!"); 
      Serial.print("\t");
      Serial.print("\t");
    }

  if(istTopf3 > sollTopf3) 
    {
      digitalWrite(pumpeTopf3Pin, HIGH);
      Serial.println("Topf3 zu trocken!!!"   );
      delay(3000);
      digitalWrite(pumpeTopf3Pin, LOW);
    } 
  else
    {
      Serial.println("Topf3 ist ok!"); 
    }
    
delay(1000);
resetFunc();  // Arduino zurÃ¼cksetzen, um AufhÃ¤ngen zu vermeiden
}