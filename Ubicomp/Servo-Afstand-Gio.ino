// Installeer de library voor de teller. Zoek op "elapsedMillis.h" by Peter Freerick. Via "Tools > Manage Libraies".
// Lukt het niet? Kijk dan naar de uitgebreide uitleg op de introductiepagina https://github.com/harmsel/Ubicomp-code
#include <elapsedMillis.h> //verwijzing naar de library (extra code voor de teller)
elapsedMillis timeElapsed; // maakt een teller aan met de naam "timeElapsed"

// Installeer de library voor de afstandsensor zoek op "Grove ultrasonic ranger" by Seeed Studio
#include "Ultrasonic.h" //verwijzing naar de library van de afstandsensor
Ultrasonic ultrasonic(6); //Steek de ultrasoon sensor in D6 van je Arduino

// De library voor de Servo (deze hoef je niet te installeren)
#include <Servo.h> //verwijzing naar de library van de servo
Servo mijnServo;  // Maakt een servoObject aan met de naam 'mijnServo"

int loopAmount = 0;
int loopString = "Loop amount";


void setup() {
  Serial.begin(9600);
  mijnServo.attach(8);  // //Steek de servo in D8 van je Arduino
}

void loop() {
  long afstand = ultrasonic.MeasureInCentimeters();
//  Serial.println(afstand);
  loopAddOne();  
  if (afstand < 10) { // hij is heel BANG!!!
    wiebel(10, 60, 100);// hoekStart,  hoekEinde,  snelheid

  } else if (afstand < 20) {
    wiebel(10, 30, 250);// hoekStart,  hoekEinde,  snelheid

  } else if (afstand < 30) {
    wiebel(10, 160, 500);// hoekStart,  hoekEinde,  snelheid

  }
  delay(30);
}


void loopAddOne() {

  loopAmount = loopAmount + 1;

  loopyLoop();
  
}

void loopyLoop() {
  Serial.println("LOOPY LOOP!");
   Serial.println(loopAmount);  
  }

// functie die laat wiebelen
void wiebel(int hoekStart, int hoekEinde, int snelheid)
{
  if (timeElapsed < snelheid) { //zolang de teller minder dan 1000 is, doe onderstaande
    mijnServo.write(hoekEinde);   // draai de servo naar 170 graden
  } else if (timeElapsed < (snelheid * 2)) { // zolang de teller niet onder 1000 wel onder de 2000 is:
    mijnServo.write(hoekStart);   // draai de servo naar 10 graden
  } else { // in de andere gevallen (dus NIET <1000 of <2000) doe dan:
    timeElapsed = 0; //begin opnieuw met tellen van Milliseconden
  }
}
