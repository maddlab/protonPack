//  Outlook: https://outlook.office.com/mail/inbox/id/AAQkADNmOTNkZmM0LTU4MzQtNDY0NC1iNzEwLWRiZDZhNGQwZDhiZAAQAOwjM4hhuNFOqF2UJ7bxtRw%3D
//  Jim's Shared: https://onedrive.live.com/?authkey=%21AFoBHaLVqdAewYw&id=2BA0FC22D912B07E%21122362&cid=2BA0FC22D912B07E

#include <Adafruit_NeoPixel.h>

// Which pin is connected to NeoPixels?
#define POWERCELL_PIN 2
#define CYCLOTRON_PIN 3
#define WANDTIP_PIN 4
#define TRIGGER_PIN 5
#define WAND_CLIPPARD_LEFT 6
#define PACK_POWER_PIN 7
#define VENT_LIGHT_PIN 8

/************** Animation Speeds ********************/
int pwrInterval = 45;               // powercell animation speed
int cycloInterval = 700;           // cyclotron animation speed
int wandtipInterval = 500;          // wand tip animation speed

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use
Adafruit_NeoPixel powercell(16, POWERCELL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclotron(28, CYCLOTRON_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wandtip(7, WANDTIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wand_clippard_left(1, WAND_CLIPPARD_LEFT, NEO_GRB + NEO_KHZ800);  // orange light to the left of the clippard
Adafruit_NeoPixel vent_light(4, VENT_LIGHT_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize serial
  Serial.begin(9600);

  // Initialize pinModes
  pinMode(TRIGGER_PIN, INPUT);
  pinMode(PACK_POWER_PIN, INPUT);

  // Initialize powercell LEDS to 'off' and set brightness
  powercell.begin();
  powercell.show();
  powercell.setBrightness(255);

  cyclotron.begin();
  cyclotron.show();
  cyclotron.setBrightness(255);

  wandtip.begin();
  wandtip.show();
  wandtip.setBrightness(255);

  wand_clippard_left.begin();
  wand_clippard_left.show();
  wand_clippard_left.setBrightness(255);

  vent_light.begin();
  vent_light.show();
  vent_light.setBrightness(255);
}

/************************* Main **********************/
void loop() {

  // if pack power is on
  if (digitalRead(PACK_POWER_PIN) == 1)
  {
    int currentMillis = millis();
    powerCell_normalMode(currentMillis, pwrInterval);
    cyclotron_normalMode(currentMillis, cycloInterval);
    
    //cyclotron.fill(cyclotron.Color(255,0,0), 0, 7);
    //cyclotron.fill(cyclotron.Color(255,0,0), 7, 7);
    //cyclotron.fill(cyclotron.Color(255,0,0), 14, 7);
    //cyclotron.fill(cyclotron.Color(255,0,0), 21, 7);
    //cyclotron.show();
    
    wandtip_normalMode();
    if (digitalRead(TRIGGER_PIN) == 1)
    {
      wandtip_fire();
    }

    vent_light_normalMode();

    wand_clippard_left.setPixelColor(0, wand_clippard_left.Color(255, 50, 0));  // orange
    wand_clippard_left.show();
  }

  // if pack power is off
  else
  {
    powercell.clear();
    powercell.show();

    cyclotron.clear();
    cyclotron.show();

    wand_clippard_left.clear();
    wand_clippard_left.show();

    vent_light.clear();
    vent_light.show();
  }
}
/************************ End Main ***************************/

/****************** Vent light Animation *********************/
void vent_light_normalMode()
{
  vent_light.fill(vent_light.Color(255,255,255));
  vent_light.show();
}

/****************** Wand Tip Animation *********************/
void wandtip_normalMode()
{
  wandtip.clear();
  wandtip.show();
}

void wandtip_fire()
{
  wandtip.fill(wandtip.Color(255, 255, 255), 0, 0);
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
        cyclotron.fill(cyclotron.Color(255,0,0), 0, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 7, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 14, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 21, 7);
        cycloSeqNum++;
        break;

      case 1:
        cyclotron.fill(cyclotron.Color(0,0,0), 0, 7);
        cyclotron.fill(cyclotron.Color(255,0,0), 7, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 14, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 21, 7);
        cycloSeqNum++;
        break;

      case 2:
        cyclotron.fill(cyclotron.Color(0,0,0), 0, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 7, 7);
        cyclotron.fill(cyclotron.Color(255,0,0), 14, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 21, 7);
        cycloSeqNum++;
        break;

      case 3:
        cyclotron.fill(cyclotron.Color(0,0,0), 0, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 7, 7);
        cyclotron.fill(cyclotron.Color(0,0,0), 14, 7);
        cyclotron.fill(cyclotron.Color(255,0,0), 21, 7);
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
