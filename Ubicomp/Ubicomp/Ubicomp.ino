
//AfstandSensor
#include "Ultrasonic.h"    // Zoek de library "Grove Ultrasonic" en installeer deze
Ultrasonic ultrasonic(7);  //aansluiten op D6

// LED-strip
#include <Adafruit_NeoPixel.h>  // installeer "Adafruit_NeoPixel.h" via: Tools > Manage Libraies
#define PIN 3                   // De ledstrip aansluiten op D3
#define NUMPIXELS 16            // het aantal ledjes in je strip,
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include <elapsedMillis.h>  /// installeer, als je dat nog niet gedaan had bij ToDo1,: "elapsedMillis.h" van Paul via: Tools > Manage Libraies
elapsedMillis timeElapsed;  //maak een timer object aan met deze naam

int teller = 0;


int trilPin = 2;  //sluit de trilmotor aan op D2

//ChainableLED
#include <ChainableLED.h>           // Installeer de 'Grove-Chanaable RGB LED"
#define NUM_LEDS 1 //aantal LEDS die je gaat aansluiten
ChainableLED leds(5, 6, NUM_LEDS);  //Sluit aan op D5. Eerste is de input pin. Dus sluit aan
byte power = 0;

//comp-DHT-TempHumidity
#include "DHT.h"  //Required libraries
#define DHTpin 4  //Connect the sensor to D4

DHT dht(DHTpin, DHT11);  //If you don't have a default sensor you can change to DHT22

//LED KNOP
int ledPin = 8;  //Sluit de blauwe LED/KNOP aan op D7
int ledBtn = 9;

bool timerStarted = false;





// Variables will change:
int buttonPushCounter = 0;  // counter for the number of button presses
int showerState = 0;        // current state of the button
int lastShowerState = 0;    // previous state of the button

bool showerOn = false;

void setup() {


  // LED-strip
  pixels.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();             // Turn OFF all pixels ASAP
  pixels.setBrightness(10);  // Set helderheid naar 1/5 (max = 255)


  //comp-DHT-TempHumidity
  dht.begin();

  //LED KNOP
  pinMode(ledPin, OUTPUT);
  pinMode(ledBtn, INPUT);

  Serial.begin(9600);
}



void loop() {
  int fakeTemp;

  int coldWater = "green";
  int regularWater = "orange";
  int hotWater = "red";




  //   //AfstandSensor
  //   long afstand;  //variable for storing the distance
  //   afstand = ultrasonic.MeasureInCentimeters();
  //   Serial.print("Afstand: ");
  //   Serial.println(afstand);  //
  //   delay(50);                //even wachten tussen de metingen voor leebaarheid

  // /// --  code waardoor het niveau in groene leds is weergegeven
  //   int pixNr = (afstand / 2);
  //   pixels.clear();  // Set all pixel colors to 'off'
  //   pixels.setPixelColor(pixNr, pixels.Color(0, 150, 0));
  //   pixels.show();  // Stuur bovenstaande pixel update naar de strip

  //   // ---  Code die de positieve feedback start
  //   // We gaan er van uit dat de afstandsensor in de dop van de fles zit. Deze afstand meet de afstand tot het vloeistof oppervlakte
  //   // Als je een slok uit de fles neemt 'ziet' de sensor de bodem van de fles. Dan krijg je positieve feedback op je slok.
  //   // doe je de fles weer rechtop, dan meet de sensor niet meer de bodem van de fles
  //   // Als je de fles leeg hebt, blijft ook de feedback doorgaan

  //   if (afstand < 30) {    // we gaan er van uit dat de fles 30cm diep is
  //     rainbowCycle(5, 1);  // functie aanroep met waarden: (snelheid, herhalingen)
  //   }
  //   delay(30);  // om de serial monitor leesbaarder te maken





  //ChainableLED
  //  for (byte i=0; i<NUM_LEDS; i++)
  //   {
  //     if (i%2 == 0){
  //       leds.setColorRGB(i, 255-power, 0, 0);
  //     } else {
  //       leds.setColorRGB(i, 0, 255-power, 0);
  //     }
  //   }
  //   power+= 10;

  //   delay(10);

  // LED KNOP
  // int BtnPressed = !digitalRead(ledBtn);

  showerState = digitalRead(ledBtn);

  // Serial.print("Btn Pressed ");
  // Serial.println(BtnPressed);
  Serial.print("timeElapsed ");
  Serial.println(timeElapsed);


  if (showerState != lastShowerState) {

    if (showerState == LOW) {
      buttonPushCounter++;

      Serial.println("The Shower is On!");
      timerStarted = true;
      Serial.print("timerStarted ");
      Serial.println(timerStarted);
      digitalWrite(ledPin, HIGH);  // Zet de led aan (bij deze led: LOW = aan, HIGH = uit)

    //      fakeTemp = coldWater;
    // setColorTemp(fakeTemp);
      // leds.setColorRGB(0, 0, 255, 0);

      Serial.print("buttonPushCounter ");
      Serial.println(buttonPushCounter);
      

    } else {
      Serial.println("The Shower is Off!");
    }
    delay(500);
  }
  lastShowerState = showerState;





 if (buttonPushCounter % 2 == 0) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
if (buttonPushCounter == 3) {
    fakeTemp == coldWater;
    // setColorTemp(coldWater);
    leds.setColorRGB(0, 0, 255-power, 0);
    
    return;
  } if (buttonPushCounter == 4) {
    fakeTemp = regularWater;
    // setColorTemp(regularWater);
     leds.setColorRGB(0, 242-power, 153-power, 0);
    delay(50);
    return;
  } if (buttonPushCounter == 5) {
    fakeTemp = hotWater;
    leds.setColorRGB(0, 255-power, 0, 0);
    // setColorTemp(hotWater);
    delay(50);
    buttonPushCounter = 0;
  }

  // } if (timerStarted && BtnPressed) {
  // timerStarted = false;
  //   digitalWrite(ledPin, HIGH);    // Zet de led aan (bij deze led: LOW = aan, HIGH = uit)
  //   fakeTemp = coldWater;
  //   setColorTemp(fakeTemp);
  //   timeElapsed = 0;

  // } else if (timerStarted && BtnPressed && (timeElapsed < 2000)) {  // zolang de teller niet onder 1000 wel onder de 2000 is:
  //   digitalWrite(ledPin, HIGH);
  //   timeElapsed = 0;
  // }
  // delay(1);  // zorg dat de output in Serial monitor beter leeesbaar is



  //comp-DHT-TempHumidity
  //Read the values from the sensor
  // float h = dht.readHumidity();
  // float t = dht.readTemperature();

  // Display the values in the serial monitor
  // Serial.print("temperature ");
  // Serial.println(t, 1); //,1 to display the rounded temperature
  // Serial.print("humidity ");

  // Serial.println(h, 1); //display rounded humidity
  // delay(100); //only useful to make the output readable (for us humans)
}



//Regenboog theater effect
void rainbowCycle(uint8_t wait, int herhalingen) {
  uint16_t i, j;
  for (j = 0; j < 256 * herhalingen; j++) {  // 2 cycles of all colors on wheel
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}




// Deze functie wordt door andere kleurenfuncties gebruikt.

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



// void setColorTemp(int temp) {
//   Serial.print("temp is ");
//   Serial.println(temp);
//   float hue = 0.0;

//   byte led = 0;


// for (byte i=0; i<NUM_LEDS; i++){
//     if (i%2 == 0){
//   if (temp = "green") {
//     // leds.setColorHSB(led, 133, 100, 100);
//         leds.setColorRGB(0, 0, 255-power, 0);
//     Serial.println("green");
//   } else if (temp = "orange") {
//     // leds.setColorHSB(led, 28, 69, 95);
//       leds.setColorRGB(i, 242-power, 153-power, 0);
//     Serial.println("orange");
//   }
//   else if (temp = "red") {
//     // leds.setColorHSB(led, 3, 100, 100);
//      leds.setColorRGB(i, 255-power, 0, 0);
//     Serial.println("red");
//   } 
//   // } else {
//   //   leds.setColorRGB(i, 0, 255-power, 0);
//   //   // leds.setColorHSB(led, 28, 69, 10);
//   //   Serial.println(temp);
//   // }
// }
//  power-= 100;
  
//   delay(10);
// }
// }


//   switch (temp) {
//   case "green":
//     leds.setColorRGB(0, 0, 255, 56);
//     break;
//   case "orange":
//     leds.setColorRGB(0, 242, 153, 74);
//     break;
//   case "red":
//     // statements
// leds.setColorRGB(0, 255, 56, 1);
//   break;
//   default:
//     leds.setColorRGB(0, 255, 255, 255);
//     break;
//   }

// }




// void setColorTemp(long temp) {
//   switch (temp) {
//   case "green":
//     leds.setColorRGB(0, 0, 255, 56);
//     break;
//   case "orange":
//     leds.setColorRGB(0, 242, 153, 74);
//     break;
//   case "red":
//     // statements
// leds.setColorRGB(0, 255, 56, 1);
//   break;
//   default:
//     leds.setColorRGB(0, 255, 255, 255);
//     break;
//   }

// }
