#include <Adafruit_NeoPixel.h>

// Which pin is connected to NeoPixels?
#define POWERCELL_PIN 2
#define CYCLOTRON_PIN 3

// How many NeoPixels are attached?
//#define POWERCELL_COUNT 16
//#define CYCLOTRON_COUNT 4


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use
Adafruit_NeoPixel powercell(16, POWERCELL_PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel cyclotron(CYCLOTRON_COUNT, CYCLOTRON_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize powercell LEDS to 'off' and set brightness
  powercell.begin();
  powercell.show();
  powercell.setBrightness(100);

}

/************************* Main **********************/
int pwrInterval = 45;               // powercell cycle speed
void loop() {
  int currentMillis = millis();
  powerCell_normalMode(currentMillis, pwrInterval);
}
/************************ End Main ***************************/


/****************** Powercell Animations *********************/
//int pwrInterval = 1000;               // powercell cycle speed
unsigned long prevPwrMillis = 0;      // last time we changed a light in the sequence

int powerSeqTotal = 16;               // number of led's in powercell
int powerSeqNum = 0;

void powerCell_normalMode(int currentMillis, int anispeed)
{
  if(currentMillis - prevPwrMillis > anispeed)
  {
    // save the last time we blinked an led
    prevPwrMillis = currentMillis;

    for(int i=0; i<powerSeqTotal; i++)
    {
      if(i <= powerSeqNum)
      {
        powercell.setPixelColor(i, powercell.Color(0,0,150)); 
      }
      else
      {
        powercell.setPixelColor(i, 0);
      }
    }
    powercell.show();
    if(powerSeqNum < powerSeqTotal)
    {
      powerSeqNum++;
    }
    else
    {
      powerSeqNum = 0;
    }
  }
}
