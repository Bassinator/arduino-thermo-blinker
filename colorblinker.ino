/*
   Example of using the ChainableRGB library for controlling a Grove RGB.
   This code cycles through all the colors in an uniform way. This is accomplished using a HSB color space.
*/
#include "ChainableLED.h"
#include "Seeed_BMP280.h"

#define NUM_LEDS 1

BMP280 bmp280;

// You must specify the correct PINS based on your setup
ChainableLED leds(8, 9, NUM_LEDS);


int colorR = 0;
int colorG = 0;
int colorB = 255;



// This must be correct pin based on your setup
const int buttonPin = 2;

// Button State
int buttonState = 0;
int lastButtonState = 0;

void setup()
{
      Serial.print("Temp: ");
  leds.init();
  leds.setColorRGB(0, colorR, colorG, colorB);

  Serial.begin(9600);
  if (!bmp280.init()) {
    Serial.println("Device error!");
  }
}

float hue = 0.0;
boolean up = true;

void loop() {
  // Main Sensor Function
  // Check if we press Button and change State
  buttonState = digitalRead(buttonPin);


  float temperature;
  temperature = bmp280.getTemperature();

  if ( buttonState != lastButtonState ) {
    if ( buttonState == 1 ) {
      Serial.print("Temp: ");
      Serial.print(temperature);
      Serial.println("C"); // The unit for  Celsius because original arduino don't support speical symbols
      Serial.println("\n");//add a line between output of different times.
      int offset = round(((temperature) - 24) * 24);
      int decisteps = (int) temperature / 10;
      int singelsteps = round(temperature - decisteps * 10);
      Serial.println(decisteps); // The unit for  Celsius because original arduino don't support speical symbols
      Serial.println(singelsteps); // The unit for  Celsius because original arduino don't support speical symbols
      Serial.println("\n");//add a line between output of different times.
      delay(250);
      for (int i = 0 ; i < decisteps; i++) {
        leds.setColorRGB(0, 255, 0, 0);
        delay(250);
        leds.setColorRGB(0, 0, 0, 0);
        delay(250);
      }
      for (int i = 0 ; i < singelsteps; i++) {
        leds.setColorRGB(0, 0, 255, 0);
        delay(125);
        leds.setColorRGB(0, 0, 0, 0);
        delay(125);
      }
      delay(250);
      leds.setColorRGB(0, colorR, colorG, colorB);
    }
  }

  lastButtonState = buttonState;

}

