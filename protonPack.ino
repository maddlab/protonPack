#include <Adafruit_NeoPixel.h>

// Which pin is connected to NeoPixels?
#define POWERCELL_PIN 2
#define CYCLOTRON_PIN 3

// How many NeoPixels are attached?
#define POWERCELL_COUNT 16
#define CYCLOTRON_COUNT 4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use
Adafruit_NeoPixel powercell(POWERCELL_COUNT, POWERCELL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cyclotron(CYCLOTRON_COUNT, CYCLOTRON_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize powercell LEDS to 'off' and set brightness
  powercell.begin();
  powercell.show();
  powercell.setBrightness(100);

  // Initialize cyclotron LEDS to 'off' and set brightness
  cyclotron.begin();
  cyclotron.show();
  cyclotron.setBrightness(255);
}

/*
  MAIN

  Color codes: Blue = 0,0,255
               Red = 150,0,0
               White = 255,255,255
*/
void loop() {
  powerCell_normalMode(powercell.Color(0, 0, 255), 45);
  cyclotron_normalMode(cyclotron.Color(150, 0, 0));
}
/*
  END MAIN
*/


/*
    Helper functions
*/
void cyclotron_normalMode(uint32_t color)
{
  cyclotron.setPixelColor(0, color);
  cyclotron.show();
}

void powerCell_normalMode(uint32_t color, int wait)
{
  powercell.clear();

  for (int i = 0; i < powercell.numPixels(); i++)
  {
    if (i == powercell.numPixels() - 1)
    {
      powercell.setPixelColor(i, color);
      powercell.show();
    }
    powercell.setPixelColor(i, color);
    powercell.show();
    delay(wait);
  }
}
