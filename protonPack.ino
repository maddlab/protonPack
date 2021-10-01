#include <Adafruit_NeoPixel.h>

// Which pin is connected to NeoPixels?
#define POWERCELL_PIN 2
#define CYCLOTRON_PIN 3

/************** Animation Speeds ********************/
int pwrInterval = 45;               // powercell animation speed
int cycloInterval = 400;            // cyclotron animation speed

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use
Adafruit_NeoPixel powercell(16, POWERCELL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclotron(4, CYCLOTRON_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize powercell LEDS to 'off' and set brightness
  powercell.begin();
  powercell.show();
  powercell.setBrightness(100);

  cyclotron.begin();
  cyclotron.show();
  cyclotron.setBrightness(255);
}

/************************* Main **********************/
void loop() {
  int currentMillis = millis();
  
  powerCell_normalMode(currentMillis, pwrInterval);
  cyclotron_normalMode(currentMillis, cycloInterval);
//cyclotron.setPixelColor(0, cyclotron.Color(0,150,0));
//cyclotron.setPixelColor(1, cyclotron.Color(0,150,0));
//cyclotron.setPixelColor(2, cyclotron.Color(0,150,0));
//cyclotron.setPixelColor(3, cyclotron.Color(0,150,0));
//cyclotron.show();
}
/************************ End Main ***************************/

/****************** Cyclotron Animation *********************/
unsigned long prevCycloMillis = 0;

int cycloSeqTotal = 4;
int cycloSeqNum = 0;

void cyclotron_normalMode(int currentMillis, int anispeed)
{
 if(currentMillis - prevCycloMillis > anispeed)
 {
  // save the last time we blinked a cyclotron led
  prevCycloMillis = currentMillis;

  for(int i=0; i<cycloSeqTotal; i++)
  {
    if(i <= cycloSeqNum)
    {
      cyclotron.setPixelColor(i, cyclotron.Color(150,0,0));
    }
    else
    {
      cyclotron.setPixelColor(i, 0);
    }
  }
  cyclotron.show();
  if(cycloSeqNum < cycloSeqTotal)
  {
    cycloSeqNum++;
  }
  else
  {
    cycloSeqNum = 0;
  }
 }
}

/****************** Powercell Animation *********************/
unsigned long prevPwrMillis = 0;      // last time we changed a light in the sequence

int powerSeqTotal = 16;               // number of led's in powercell
int powerSeqNum = 0;

void powerCell_normalMode(int currentMillis, int anispeed)
{
  if(currentMillis - prevPwrMillis > anispeed)
  {
    // save the last time we blinked a powercell led
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
