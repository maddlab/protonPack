//  Outlook: https://outlook.office.com/mail/inbox/id/AAQkADNmOTNkZmM0LTU4MzQtNDY0NC1iNzEwLWRiZDZhNGQwZDhiZAAQAOwjM4hhuNFOqF2UJ7bxtRw%3D
//  Jim's Shared: https://onedrive.live.com/?authkey=%21AFoBHaLVqdAewYw&id=2BA0FC22D912B07E%21122362&cid=2BA0FC22D912B07E

#include <Adafruit_NeoPixel.h>

// Which pin is connected to NeoPixels?
#define POWERCELL_PIN 2
#define CYCLOTRON_PIN 3
#define WANDTIP_PIN 4
#define TRIGGER_PIN 5

/************** Animation Speeds ********************/
int pwrInterval = 45;               // powercell animation speed
int cycloInterval = 1000;           // cyclotron animation speed
int wandtipInterval = 500;          // wand tip animation speed

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use
Adafruit_NeoPixel powercell(16, POWERCELL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclotron(4, CYCLOTRON_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wandtip(7, WANDTIP_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize serial
  Serial.begin(9600);

  // Initialize pinModes
  pinMode(TRIGGER_PIN, INPUT);

  // Initialize powercell LEDS to 'off' and set brightness
  powercell.begin();
  powercell.show();
  powercell.setBrightness(100);

  cyclotron.begin();
  cyclotron.show();
  cyclotron.setBrightness(255);

  wandtip.begin();
  wandtip.show();
  wandtip.setBrightness(50);
}

/************************* Main **********************/
void loop() {
  int currentMillis = millis();
  powerCell_normalMode(currentMillis, pwrInterval);
  cyclotron_normalMode(currentMillis, cycloInterval);
  wandtip_normalMode();
  if (digitalRead(TRIGGER_PIN) == 1)
  {
    wandtip_fire();
  }
}
/************************ End Main ***************************/

/****************** Wand Tip Animation *********************/
void wandtip_normalMode()
{
  wandtip.clear();
  wandtip.show();
}

void wandtip_fire()
{
  wandtip.fill(255, 0, 0);
  wandtip.show();
}

/****************** Cyclotron Animation *********************/
unsigned long prevCycloMillis = 0;

int cycloSeqTotal = 4;
int cycloSeqNum = 0;

void cyclotron_normalMode(int currentMillis, int anispeed)
{
  if (currentMillis - prevCycloMillis > anispeed)
  {
    // save the last time we blinked a cyclotron led
    prevCycloMillis = currentMillis;
    Serial.println(cycloSeqNum);

    if (cycloSeqNum == cycloSeqTotal)
    {
      cycloSeqNum = 0;
    }

    switch (cycloSeqNum)
    {
      case 0:
        cyclotron.setPixelColor(0, cyclotron.Color(150, 0, 0));
        cyclotron.setPixelColor(1, 0);
        cyclotron.setPixelColor(2, 0);
        cyclotron.setPixelColor(3, 0);
        cycloSeqNum++;
        break;

      case 1:
        cyclotron.setPixelColor(0, 0);
        cyclotron.setPixelColor(1, cyclotron.Color(150, 0, 0));
        cyclotron.setPixelColor(2, 0);
        cyclotron.setPixelColor(3, 0);
        cycloSeqNum++;
        break;

      case 2:
        cyclotron.setPixelColor(0, 0);
        cyclotron.setPixelColor(1, 0);
        cyclotron.setPixelColor(2, cyclotron.Color(150, 0, 0));
        cyclotron.setPixelColor(3, 0);
        cycloSeqNum++;
        break;

      case 3:
        cyclotron.setPixelColor(0, 0);
        cyclotron.setPixelColor(1, 0);
        cyclotron.setPixelColor(2, 0);
        cyclotron.setPixelColor(3, cyclotron.Color(150, 0, 0));
        cycloSeqNum++;
        break;
    }

    cyclotron.show();

  }
}

/****************** Powercell Animation *********************/
unsigned long prevPwrMillis = 0;      // last time we changed a light in the sequence

int powerSeqTotal = 16;               // number of led's in powercell
int powerSeqNum = 0;

void powerCell_normalMode(int currentMillis, int anispeed)
{
  if (currentMillis - prevPwrMillis > anispeed)
  {
    // save the last time we blinked a powercell led
    prevPwrMillis = currentMillis;

    for (int i = 0; i < powerSeqTotal; i++)
    {
      if (i <= powerSeqNum)
      {
        powercell.setPixelColor(i, powercell.Color(0, 0, 150));
      }
      else
      {
        powercell.setPixelColor(i, 0);
      }
    }
    powercell.show();
    if (powerSeqNum < powerSeqTotal)
    {
      powerSeqNum++;
    }
    else
    {
      powerSeqNum = 0;
    }
  }
}
