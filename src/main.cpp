/*
  Titre      : Controle de servo moteur
  Auteur     : Yvan Tankeu
  Date       : 29/01/2022
  Description: Controler la rotation d'un servo moteur avec 2 capteurs et un actuateur
  // Je me suis servi du code fournit par arduino àfin de peaufiner pour avoir cette solution
  Version    : 0.0.1
*/

#include <Arduino.h>
#include <Servo.h>

// Déclaration des broches
const int TactilPin = 1;   // Connect Touch sensor on Digital Pin 1
const int ButtonPin = 2;   // Connect sensor to input pin 2
const int ServoPin = 3;   // Connect Servo moteur on Digital Pin 3

Servo servo;  // creation de l'objet Servo

int angle = 90;    // variable pour stocker l'angle
int sautAngle = 5; // variable d'angle final

bool StatuTactil ; // statut du capteur tactil 0 ou 1
bool StatuBtn;    // statut du bouton 0 ou 1

const int delai = 50 ; // delai pris par le servo pour atteindre l'angle qui lui sera communiqué
const int angleMax = 180;
const int angleMin = 0;

void setup() {

  pinMode(ButtonPin, INPUT);     // declare pushbutton as input
  pinMode(TactilPin, INPUT);       //Set touch sensor pin to input mode
  servo.attach(ServoPin);  // attaches the servo on pin 3 to the servo object
  
}

void loop() {

  StatuBtn = digitalRead(ButtonPin);  // Signal lu par le boutton stocké dans StatuBtn
  if (StatuBtn == HIGH) // Si on presse le bouton, le servo ira de la gaucher vers la droite de 1 à 180
  {
    angle = angle + 1; // suivant un pas de 1
    servo.write(angle); // positionne le servo sur l'angle passé en paramètre
    delay(delai);

    sautAngle = servo.read();
    if (angle > angleMin && angle  <= angleMax ){
      Serial.print("Se déplacer vers: ");
      Serial.print(angle); // print the angle
      Serial.println(" degrée");
    }
    else
    {
      Serial.println("ne peut se déplacer à cet angle, veuillez réaguster ");    
    }
    
    if (StatuBtn == HIGH && sautAngle == 180)
    {
       // Des qu'on atteint la valeur max, on fait du bruit
      tone(8, 600, 500);
      delay(100);
      noTone(8);
    } 
  }
  
  // Si on pese sur le capteur tactile, voici ce qui va suivre
  StatuTactil = digitalRead(TactilPin); 
  if (StatuTactil == HIGH)
  {
    angle = angle - 1;
    servo.write(angle);
    delay(delai);

    sautAngle = servo.read();
    if (angle > angleMin && angle <= angleMax)
    {
      Serial.print("Se déplacer vers: ");
      Serial.print(angle); // print the angle
      Serial.println(" degrée");
    }
    else
    {
      Serial.println("ne peut se déplacer à cet angle, veuillez réaguster ");
    }
      
      // Des qu'on atteint la valeur max, on fait du bruit.
      if (StatuTactil == HIGH &&  sautAngle == 0){
        tone(8, 300, 500); 
        delay(100);
        noTone(8);
       }
  }
}