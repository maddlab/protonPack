//  Outlook: https://outlook.office.com/mail/inbox/id/AAQkADNmOTNkZmM0LTU4MzQtNDY0NC1iNzEwLWRiZDZhNGQwZDhiZAAQAOwjM4hhuNFOqF2UJ7bxtRw%3D
//  Jim's Shared: https://onedrive.live.com/?authkey=%21AFoBHaLVqdAewYw&id=2BA0FC22D912B07E%21122362&cid=2BA0FC22D912B07E

#include <Adafruit_NeoPixel.h>

// For the pack lights
#define POWERCELL_PIN 2
#define CYCLOTRON_PIN 3
#define WANDTIP_PIN 4               // this is for the wand tip neopixel
#define WAND_AUX_PIN 6
#define N_FILTER_PIN 8

// Switches
#define WAND_BOOTUP_PIN 5
#define SWITCH_4_PIN 10
#define TRIGGER_PIN 11               // input for wand firing
#define PACK_POWER_PIN 12

// For pack sounds
#define SFX_POWERUP 9

int current_state, prev_state;

/************** Animation Speeds ********************/
int pwrInterval = 45;               // powercell animation speed
int cycloInterval = 700;           // cyclotron animation speed
int wandtipInterval = 500;          // wand tip animation speed

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use
Adafruit_NeoPixel powercell(16, POWERCELL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclotron(28, CYCLOTRON_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wandtip(7, WANDTIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wand_aux(5, WAND_AUX_PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel vent_light(4, VENT_LIGHT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel n_filter(4, N_FILTER_PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  // Initialize serial
  Serial.begin(9600);

  // Initialize pinModes
  pinMode(TRIGGER_PIN, INPUT);
  pinMode(PACK_POWER_PIN, INPUT);
  pinMode(SFX_POWERUP, OUTPUT);

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

  wand_aux.begin();
  wand_aux.show();
  wand_aux.setBrightness(255);

  n_filter.begin();
  n_filter.show();
  n_filter.setBrightness(255);

  // Initialize SFXs pins to HIGH
  digitalWrite(SFX_POWERUP, HIGH);

  // Initialize state
  current_state = 0;
  prev_state = current_state;
}


/************************* Main **********************/
void loop() {
  //wandtip.fill(wandtip.Color(255,255,255));
  //wandtip.show();
  // if pack power is on
  Serial.println(digitalRead(PACK_POWER_PIN));
  if (digitalRead(PACK_POWER_PIN) == 1)
  {
    Serial.println(digitalRead(PACK_POWER_PIN));
    digitalRead(PACK_POWER_PIN);
    if (current_state == 0)
    {
      digitalWrite(SFX_POWERUP, LOW);
      current_state = 1;
      Serial.println(current_state);
    }

    int currentMillis = millis();
    powerCell_normalMode(currentMillis, pwrInterval);
    cyclotron_normalMode(currentMillis, cycloInterval);
    
    n_filter.setPixelColor(0, n_filter.Color(255,255,255));
    n_filter.setPixelColor(1, n_filter.Color(255,255,255));
    n_filter.setPixelColor(2, n_filter.Color(255,255,255));
    n_filter.setPixelColor(3, n_filter.Color(255,255,255));
    n_filter.show();

    wand_aux.setPixelColor(0, wand_aux.Color(255, 255, 255));
    wand_aux.setPixelColor(1, wand_aux.Color(235, 213, 52));
    wand_aux.setPixelColor(2, wand_aux.Color(255, 255, 255));
    wand_aux.setPixelColor(3, wand_aux.Color(255, 255, 255));
    wand_aux.setPixelColor(4, wand_aux.Color(255, 255, 255));
    wand_aux.show();

    wandtip_normalMode();
    if (digitalRead(TRIGGER_PIN) == 1)
    {
      //wandtip_fire();
      fireStrobe(currentMillis);
    }
  }

  // if pack power is off
  else
  {
    digitalWrite(SFX_POWERUP, HIGH);
    powercell.clear();
    powercell.show();

    cyclotron.clear();
    cyclotron.show();

    wand_aux.clear();
    wand_aux.show();

    n_filter.clear();
    n_filter.show();
  }
}
/************************ End Main ***************************/

/****************** Boot-up Sequence *********************/
void boot_up_sequence()
{
  digitalWrite(SFX_POWERUP, LOW);
  digitalWrite(SFX_POWERUP, HIGH);
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
        cyclotron.fill(cyclotron.Color(255, 0, 0), 0, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 7, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 14, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 21, 7);
        cycloSeqNum++;
        break;

      case 1:
        cyclotron.fill(cyclotron.Color(0, 0, 0), 0, 7);
        cyclotron.fill(cyclotron.Color(255, 0, 0), 7, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 14, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 21, 7);
        cycloSeqNum++;
        break;

      case 2:
        cyclotron.fill(cyclotron.Color(0, 0, 0), 0, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 7, 7);
        cyclotron.fill(cyclotron.Color(255, 0, 0), 14, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 21, 7);
        cycloSeqNum++;
        break;

      case 3:
        cyclotron.fill(cyclotron.Color(0, 0, 0), 0, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 7, 7);
        cyclotron.fill(cyclotron.Color(0, 0, 0), 14, 7);
        cyclotron.fill(cyclotron.Color(255, 0, 0), 21, 7);
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




/*************** Nose Jewel Firing Animations *********************/
unsigned long prevFireMillis = 0;
const unsigned long fire_interval = 500;     // interval at which to cycle lights (milliseconds).
int fireSeqNum = 0;
int fireSeqTotal = 5;

//wandtip.fill(wandtip.Color(134,253,258));

void clearFireStrobe() {
  for ( int i = 0; i < 7; i++) {
    wandtip.setBrightness(255);
    wandtip.setPixelColor(i, 0);
  }
  wandtip.show();
  fireSeqNum = 0;
}

void fireStrobe(unsigned long currentMillis) {
  if ((unsigned long)(currentMillis - prevFireMillis) >= fire_interval) {
    prevFireMillis = currentMillis;

    switch ( fireSeqNum ) {
      case 0:
        wandtip.setPixelColor(0, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(1, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(2, 0);
        wandtip.setPixelColor(3, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(4, 0);
        wandtip.setPixelColor(5, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(6, 0);
        break;
      case 1:
        wandtip.setPixelColor(0, wandtip.Color(0, 0, 255));
        wandtip.setPixelColor(1, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(2, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(3, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(4, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(5, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(6, wandtip.Color(255, 255, 255));
        break;
      case 2:
        wandtip.setPixelColor(0, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(1, 0);
        wandtip.setPixelColor(2, wandtip.Color(0, 0, 255));
        wandtip.setPixelColor(3, 0);
        wandtip.setPixelColor(4, wandtip.Color(0, 0, 255));
        wandtip.setPixelColor(5, 0);
        wandtip.setPixelColor(6, wandtip.Color(255, 0, 0));
        break;
      case 3:
        wandtip.setPixelColor(0, wandtip.Color(0, 0, 255));
        wandtip.setPixelColor(1, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(2, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(3, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(4, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(5, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(6, wandtip.Color(255, 255, 255));
        break;
      case 4:
        wandtip.setPixelColor(0, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(1, 0);
        wandtip.setPixelColor(2, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(3, 0);
        wandtip.setPixelColor(4, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(5, 0);
        wandtip.setPixelColor(6, wandtip.Color(255, 255, 255));
        break;
      case 5:
        wandtip.setPixelColor(0, wandtip.Color(255, 0, 255));
        wandtip.setPixelColor(1, wandtip.Color(0, 255, 0));
        wandtip.setPixelColor(2, wandtip.Color(255, 0, 0));
        wandtip.setPixelColor(3, wandtip.Color(0, 0, 255));
        wandtip.setPixelColor(4, wandtip.Color(255, 0, 255));
        wandtip.setPixelColor(5, wandtip.Color(255, 255, 255));
        wandtip.setPixelColor(6, wandtip.Color(0, 0, 255));
        break;
    }

    wandtip.show();

    fireSeqNum++;
    if ( fireSeqNum > fireSeqTotal ) {
      fireSeqNum = 0;
    }
  }
}
