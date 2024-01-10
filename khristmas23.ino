/* Createdby Mr.FunnyPengin!, for 2023 holiday lights Thank you to Scott Marley 
for the YouTube tutorial on how to incorporate a blending function. */
#include "FastLED.h"

#define FASTLED_ALLOW_INTERRUPTS 0
#define DATA_PIN 11 //DATA PIN ON ARDUINO
#define SCALE 50 //NUMBER OF NODES
#define COLOR_ORDER RGB 
#define LED_TYPE WS2811

CRGB source1[SCALE];
CRGB source2[SCALE];
uint8_t source1Pattern = 0;
uint8_t source2Pattern = 1;
bool useSource1 = false;
CRGB output[SCALE];

uint8_t blendAmount = 0;
uint8_t patternCounter = 0;
uint8_t gHue = 80; //for sinelon and rainbow glitter

#define MAX_BRIGHTNESS          255 //BRIGHTNESS LIMIT - 255 IS MAX!  
#define FRAMES_PER_SECOND 120 //USE THIS TO CHANGE THE SPEED

void setup() {
  delay(5000); //KEEP ATLEAST 5000
  
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(output, SCALE);
  FastLED.setBrightness(MAX_BRIGHTNESS);

  Serial.begin(57600);

}
//If adding new patterns, add the name of the function for your pattern.



void loop()
{
  EVERY_N_MILLISECONDS(12) {
    blend(source1, source2, output, SCALE, blendAmount);   // Blend between the two sources

    if (useSource1) {
      if (blendAmount < 255) blendAmount++;                   // blendAmount 'up' to source 2
    } else {
      if (blendAmount > 0) blendAmount--;                     // blendAmount 'down' to source 1
    }
  }

  runPattern(source1Pattern, source1);                  // Run both patterns simultaneously
  runPattern(source2Pattern, source2);
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_SECONDS( 12 ) { nextPattern(); } // change patterns periodically
  EVERY_N_SECONDS( 0.5 ) { gHue++; }

  EVERY_N_SECONDS(2) {
    for (int i = 0; i < 4; i++) {
      blurld(LEDarray, SCALE)
    }
  }
}

void nextPattern() {
  patternCounter = (patternCounter + 1) % 10;           // Change the value (in this case the 8) to how ever many patterns you have.

  if (useSource1) source1Pattern = patternCounter;     // Determine which source array for new pattern
  else source2Pattern = patternCounter;

  useSource1 = !useSource1;                            // Swap source array for next time around
}

void runPattern(uint8_t pattern, CRGB *LEDArray) {
  switch (pattern) {
    case 0:
      movingDots(LEDArray);
      break;
    case 1:
      rainbowBeat(LEDArray);
      break;
    case 3:
      redYG(LEDArray);
      break;
    case 4:
      MagBlue(LEDArray);
      break;
    case 5:
      WhiteRed(LEDArray);
      break;
    case 6:
      LPurple(LEDArray);
      break;
    case 7:
      LCyan(LEDArray);
      break;
    case 8:
      YGreen(LEDArray);
      break;
    case 9:
      rainglitter(LEDArray);
      break;  
  }
}

//------- Put your patterns below -------//

void movingDots(CRGB *LEDarray) {
  
  uint16_t posBeat  = beatsin16(30, 0, SCALE - 1, 0, 0);
  uint16_t posBeat2 = beatsin16(60, 0, SCALE - 1, 0, 0);

  uint16_t posBeat3 = beatsin16(30, 0, SCALE - 1, 0, 32767);
  uint16_t posBeat4 = beatsin16(60, 0, SCALE - 1, 0, 32767);

  // Wave for LED color
  uint8_t colBeat  = beatsin8(45, 0, 255, 0, 0);

  LEDarray[(posBeat + posBeat2) / 2]  = CHSV(colBeat, 150, 255);
  LEDarray[(posBeat3 + posBeat4) / 2]  = CHSV(colBeat, 150, 255);

  fadeToBlackBy(LEDarray, SCALE, 10);
}


void rainbowBeat(CRGB *LEDarray) {
  
  uint16_t beatA = beatsin16(30, 0, 255);
  uint16_t beatB = beatsin16(20, 0, 255);
  fill_rainbow(LEDarray, SCALE, (beatA+beatB)/2, 8);
}


void redYG(CRGB *LEDarray) {

  uint16_t sinBeat   = beatsin16(30, 0, SCALE - 1, 0, 0);
  uint16_t sinBeat2  = beatsin16(30, 0, SCALE - 1, 0, 21845);
  uint16_t sinBeat3  = beatsin16(30, 0, SCALE - 1, 0, 43690);

  LEDarray[sinBeat]   = CHSV(0,150,255);
  LEDarray[sinBeat2]  = CHSV(42,150,255);
  LEDarray[sinBeat3]  = CHSV(86,150,255);
  
  fadeToBlackBy(LEDarray, SCALE, 10);
}

void MagBlue(CRGB *LEDarray) {


  uint16_t sinBeat2  = beatsin16(30, 0, SCALE - 1, 0, 21845);
  uint16_t sinBeat3  = beatsin16(30, 0, SCALE - 1, 0, 43690);


  LEDarray[sinBeat2]  = CHSV(171,150,255);
  LEDarray[sinBeat3]  = CHSV(214,150,255);
  
  fadeToBlackBy(LEDarray, SCALE, 10);
}

void WhiteRed(CRGB *LEDarray) {


  uint16_t sinBeat2  = beatsin16(30, 0, SCALE - 1, 0, 21845);
  uint16_t sinBeat3  = beatsin16(30, 0, SCALE - 1, 0, 43690);


  LEDarray[sinBeat2]  = CHSV(0,150,0);
  LEDarray[sinBeat3]  = CHSV(0,0,255);
  
  fadeToBlackBy(LEDarray, SCALE, 10);
}

void LPurple(CRGB *LEDarray) { //light purple

 
  uint16_t sinBeat2  = beatsin16(30, 0, SCALE - 1, 0, 21845);
  uint16_t sinBeat3  = beatsin16(30, 0, SCALE - 1, 0, 43690);


  LEDarray[sinBeat2]  = CHSV(190,120,255);
  LEDarray[sinBeat3]  = CHSV(0,0,0);
  
  fadeToBlackBy(LEDarray, SCALE, 10);
}

void LCyan(CRGB *LEDarray) { 


  uint16_t sinBeat2  = beatsin16(30, 0, SCALE - 1, 0, 21845);
  uint16_t sinBeat3  = beatsin16(30, 0, SCALE - 1, 0, 43690);

  // (Hue, Sat, Val)

  LEDarray[sinBeat2]  = CHSV(140,120,255);
  LEDarray[sinBeat3]  = CHSV(0,0,0);

  
  
  fadeToBlackBy(LEDarray, SCALE, 10);
}

void YGreen(CRGB *LEDarray) { 


  uint16_t sinBeat2  = beatsin16(30, 0, SCALE - 1, 0, 21845);
  uint16_t sinBeat3  = beatsin16(30, 0, SCALE - 1, 0, 43690);

  // (Hue, Sat, Val)

  LEDarray[sinBeat2]  = CHSV(70,102,255);
  LEDarray[sinBeat3]  = CHSV(0,0,0);
}






