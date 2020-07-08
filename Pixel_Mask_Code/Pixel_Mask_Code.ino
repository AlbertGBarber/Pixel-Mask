//This code is placed under the MIT license
//Copyright (c) 2019 Albert Barber
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

//code intended to run on esp8266, Wemos D1 mini
//requires lastest version of adafruit neopixel library (use the library manager)
#include <PixelStrip.h>
#include "segmentDefs.h"

//pin connections
#define PIXEL_PIN      D8
#define BUTTON_1       D6
#define BUTTON_2       D7
#define BUTTON_3       D5

//below vars are placeholders for possible bluetooth and mic board connections
#define MIC_IN         A0
#define RX_BT          D1
#define TX_BT          D2

//effects control vars
byte effectIndex = 0; //number of effect that's currently active
const byte numEffects = 40; //number of current effects - 1
boolean effectRota = true; //effects rotation on / off flag
boolean effectsStop = false; //stop all effects flag
boolean direct = true; //use for setting direction of effects
boolean breakCurrentEffect = false; //flag for breaking out of effects that use multiple sub effects / loops

//macro for implementing break for effects with multiple sub effects
#define breakEffectCheck() ({ \
    if( (breakCurrentEffect) ){ \
      (breakCurrentEffect) = false; \
      break; \
    } \
  })

//brightness vars
byte brightnessIndex = 1; //initial brightness, index of brightnessLevels array
//brightness levels array, max is 255, but 100 should be bright enough for amost all cases
//!!WARNING brightness is directly tied to power consumption, the max current per led is 60ma, this is for white at 255 brightness
//if you actually run all the leds at max, the glasses will draw 4.75 amps, this will overwhelm most power banks, and is beyond the rating of the jst connectors
const byte brightnessLevels[] = { 10, 20, 30, 50, 70, 100 };
const byte numBrightnessLevels = SIZE( brightnessLevels );

//Strip definitions
const uint16_t stripLength = 104;
const uint8_t stripType = NEO_GRB + NEO_KHZ800;
PixelStrip strip = PixelStrip(stripLength, PIXEL_PIN, stripType);

//Define some colors we'll use frequently
const uint32_t white =    strip.Color(255, 255, 255);
const uint32_t UCLAGold = strip.Color(254, 187, 54);
const uint32_t UCLABlue = strip.Color(83, 104, 149);
const uint32_t off =      strip.Color( 0, 0, 0 );
const uint32_t red =      strip.Color(255, 0, 0);
const uint32_t orange =   strip.Color(255, 43, 0);
const uint32_t ltOrange = strip.Color(255, 143, 0);
const uint32_t yellow =   strip.Color(255, 255, 0);
const uint32_t green =    strip.Color(0, 128, 0);
const uint32_t blue =     strip.Color(0, 0, 255);
const uint32_t indigo =   strip.Color( 75, 0, 130);
const uint32_t violet =   strip.Color(238, 130, 238);
const uint32_t purple =   strip.Color(123, 7, 197);
const uint32_t pink =     strip.Color(225, 0, 127);

const uint32_t pastelRainbow = strip.Color(130, 185, 226); //178,231,254,
const uint32_t pastelRainbow1 = strip.Color(110, 46, 145); //purple
const uint32_t pastelRainbow2 = strip.Color(54, 174, 218); //teal
const uint32_t pastelRainbow3 = strip.Color(120, 212, 96); //green
const uint32_t pastelRainbow4 = strip.Color(255, 254, 188); //yellow
const uint32_t pastelRainbow5 = strip.Color(236, 116, 70); //orange
const uint32_t pastelRainbow6 = strip.Color(229, 61, 84); //pink red

//define pallet array, contains 32bit representations of all colors used in patterns
uint32_t pallet[9] = { off, white, UCLAGold, UCLABlue, blue, yellow, red, green, purple };
//                   { -0-, --1--, ---2----, ----3---, -4--, ---5--, -6-, --7--, --8-- }

//pallet to match typical fairy light colors
uint32_t christmasPallet[5] = { red, blue, green, yellow, purple };

uint32_t pastelRainbowPallet[] = { pastelRainbow, pastelRainbow1 , pastelRainbow2, pastelRainbow3, pastelRainbow4, pastelRainbow5, pastelRainbow6 };
byte pastelRainbowPattern[] = {  6, 1, 2, 5, 4, 3, 0 };

uint32_t firePallet[3] = { red, ltOrange, white };

uint32_t firePallet2[3] = { purple, pink, white };
//byte wavepattern[]  = { 6, 1 };
//byte wavepattern2[] = { 5, 4 };
//byte wavepattern3[] = { 6, 7 };
//byte wavepattern4[] = { 8, 7 };
//byte christmasWavePattern[5] = { 0, 1, 2, 3, 4};

//below are spin patterns
//these are for use with the colorSpin function, which draws a pattern across segments (using the longest segment as the pattern basis)
//and then moves it along the longest segment
//you can make your own, their structure is the following
//(note that you'll have to understand how segments work in my library, you can find notes on segments in segmentSet.h)
//a spin pattern is comprised of two parts combined into one 1d array
// { 0, 1,   1, 2, 0, 0, 0, }
//  part 1       part 2
//part 1 indicates the leds on the longest segment that part 2 is to be drawn on (doesn't inculde the last index, so 1 above wouldn't be drawn)
//part 2 is the pattern of colors for each segment, made up of indeces for at pallet (ie 1 represents the second color in the pallet)

//this is confusing so I'll give an example
//for the glasses, using lenseRowSegments (each row of the glasses is a segment, excluding the center 6 leds so that all the rows are the same length)
//part 1 above indicates that, from the 0th led of the first segment, up to (not including) the 1st led, the color pattern of the segments is part 2
//the result is that the first led of each row are colored (using pallet above) row 0 -> white, row 1 -> uclaGold, row 2 -> off,  row 3 -> off, row 4 -> off
//note that leds indexs in part 1 are always defined using the longest segment, because colorSpin will map the pattern (part 1) onto shorter segments
//this works well on most led arrangments, but not so much on the glasses
//which is why I'm using lenseRowSegments, so that all segments are equal length, and the mapping is one to one

//as below, spin patterns can have multiple pattern sections
//you define the matrix as: spinPatternName[(5 + 2) * 8] -> [ (number of segments + 2) * number of rows in pattern ]
//you can also make patterns repeat using colorSpin, so you just have to define a single complete pattern (like I do with spinPatternWave)

//rowCenSegments
//two color sine wave pattern
byte spinPatternWave[(7 + 2) * 10] = {
  0, 1,   1, 2, 0, 0, 0, 0, 0,
  1, 2,   3, 1, 2, 0, 0, 0, 0,
  2, 3,   0, 3, 1, 2, 0, 0, 0,
  3, 4,   0, 0, 3, 1, 2, 0, 0,
  4, 5,   0, 0, 0, 3, 1, 2, 0,
  5, 6,   0, 0, 0, 0, 3, 1, 2,
  6, 7,   0, 0, 0, 3, 1, 2, 0,
  7, 8,   0, 0, 3, 1, 2, 0, 0,
  8, 9,   0, 3, 1, 2, 0, 0, 0,
  9, 10,  3, 1, 2, 0, 0, 0, 0,
};

//rowCenSegments
//two color sine wave pattern
byte spinPatternWave2[(7 + 2) * 8] = {
  0, 1,   0, 1, 2, 3, 0, 0, 0,
  1, 2,   0, 0, 1, 2, 3, 0, 0,
  2, 3,   0, 0, 0, 1, 2, 3, 0,
  3, 4,   0, 0, 0, 0, 1, 2, 3,
  4, 5,   0, 0, 0, 0, 1, 2, 3,
  5, 6,   0, 0, 0, 1, 2, 3, 0,
  6, 7,   0, 0, 1, 2, 3, 0, 0,
  7, 8,   0, 1, 2, 3, 0, 0, 0,
};

//rowCenSegments
//two color sine wave pattern
//byte spinPatternHeart[(7 + 2) * 7] = {
//  0, 1,   0, 0, 0, 0, 0, 0, 0,
//  1, 2,   0, 0, 1, 1, 0, 0, 0,
//  2, 3,   0, 1, 2, 2, 1, 1, 0,
//  3, 4,   0, 0, 1, 2, 2, 2, 1,
//  4, 5,   0, 1, 2, 2, 1, 1, 0,
//  5, 6,   0, 0, 1, 1, 0, 0, 0,
//  6, 7,   0, 0, 0, 0, 0, 0, 0,
//};

//rowCenSegments
//two color sine wave pattern
byte spinPatternHeart[(7 + 2) * 7] = {
  0, 1,   0, 0, 0, 0, 0, 0, 0,
  1, 2,   0, 0, 1, 1, 1, 0, 0,
  2, 3,   0, 1, 2, 2, 2, 1, 0,
  3, 4,   0, 0, 1, 2, 2, 2, 1,
  4, 5,   0, 1, 2, 2, 2, 1, 0,
  5, 6,   0, 0, 1, 1, 1, 0, 0,
  6, 7,   0, 0, 0, 0, 0, 0, 0,
  
};

//rowCenSegments
//two color sine wave pattern
byte spinPatternHelix[(7 + 2) * 10] = {
  0, 1,   0, 1, 0, 0, 0, 2, 0,
  1, 2,   0, 0, 1, 0, 2, 0, 0,
  2, 3,   0, 0, 0, 1, 0, 0, 0,
  3, 4,   0, 0, 2, 0, 1, 0, 0,
  4, 5,   0, 2, 0, 0, 0, 1, 0,
  5, 6,   0, 2, 0, 0, 0, 1, 0,
  6, 7,   0, 0, 2, 0, 1, 0, 0,
  7, 8,   0, 0, 0, 2, 0, 0, 0,
  8, 9,   0, 0, 1, 0, 2, 0, 0,
  9, 10,  0, 1, 0, 0, 0, 2, 0,
};


//for rowHalfCenSegments, we want rows seperated, so we can move the arrows in opposite directions
//two color arrows, moving horizontally
//if you want vertical arrows, you have to use columnSegments
byte spinPatternArrows[(14 + 2) * 5] = {
  0, 1,  1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
  1, 2,  2, 1, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 1, 2,
  2, 3,  0, 2, 1, 0, 1, 2, 0, 0, 2, 1, 0, 1, 2, 0,
  3, 4,  0, 0, 2, 1, 2, 0, 0, 0, 0, 2, 1, 2, 0, 0,
  4, 5,  0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
};

//for rowHalfCenSegments, we want rows seperated, so we can move the arrows in opposite directions
byte spinPatternCircles[(14 + 2) * 4] = {
  0, 1,  2, 1, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 1, 2,
  1, 2,  0, 2, 1, 1, 1, 2, 0, 0, 2, 1, 1, 1, 2, 0,
  2, 3,  0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0,
  3, 4,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

//for rowHalfCenSegments, we want rows seperated, so we can move the arrows in opposite directions
byte spinPatternX[(14 + 2) * 4] = {
  0, 1,  0, 0, 1, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0,
  1, 2,  0, 1, 2, 0, 2, 1, 0, 0, 1, 2, 0, 2, 1, 0,
  2, 3,  1, 2, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 2, 1,
  3, 4,  2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2,
};

//for colCenSegments, vertical arrows
byte spinPatternArrowsVert[(12 + 2) * 4] = {
  0, 1,   3, 4, 1, 2, 3, 4, 4, 3, 2, 1, 4, 3,
  1, 2,   2, 3, 4, 1, 2, 3, 3, 2, 1, 4, 3, 2,
  2, 3,   1, 2, 3, 4, 1, 2, 2, 1, 4, 3, 2, 1,
  3, 4,   4, 1, 2, 3, 4, 1, 1, 4, 3, 2, 1, 4,
};

//for colCenSegments, vertical arrows
byte spinPatternArrowsVert2[(12 + 2) * 6] = {
  0, 1,   0, 2, 2, 3, 3, 0, 0, 3, 3, 2, 2, 0,
  1, 2,   0, 0, 2, 2, 3, 3, 3, 3, 2, 2, 0, 0,
  2, 3,   3, 0, 0, 2, 2, 3, 3, 2, 2, 0, 0, 3,
  3, 4,   3, 3, 0, 0, 2, 2, 2, 2, 0, 0, 3, 3,
  4, 5,   2, 3, 3, 0, 0, 2, 2, 0, 0, 3, 3, 2,
  5, 6,   2, 2, 3, 3, 0, 0, 0, 0, 3, 3, 2, 2,
};

//for  rowCenSegments, USA flag
byte spinPatternUSflag[(7 + 2) * 5] = {
  0, 1,   4, 1, 4, 1, 6, 1, 6,
  1, 2,   1, 4, 1, 4, 6, 1, 6,
  2, 3,   4, 1, 4, 1, 6, 1, 6,
  3, 4,   1, 4, 1, 4, 6, 1, 6,
  4, 8,   6, 1, 6, 1, 6, 1, 6
};

//for  rowCenSegments, St George's cross (can't get blue right for Union Jack)
byte spinPatternStGeorgeCross[(7 + 2) * 3] = {
  0, 3,   1, 1, 1, 6, 1, 1, 1,
  3, 4,   6, 6, 6, 6, 6, 6, 6,
  4, 7,   1, 1, 1, 6, 1, 1, 1,
};

//storage for pallets we'll generate on the fly
uint32_t tempRandPallet[5]; //pallet for random colors (length sets number of colors used by randomColors effect)
uint32_t tempTwinklePallet[2]; //used for twinkle effect, we are only twinkling two colors at a time


//triggered by button 1, stops the current pattern, and switches to the next one, wrapping if needed
//if button 2 is also being held, turn effects on / off
void ICACHE_RAM_ATTR nextEffect() {
  strip.pixelStripStopPattern = true; //stop the current pattern
  breakCurrentEffect = true; //set flag to break out of current case statement
  //if button 2 is being held, stop/start the effect cycle
  //otherwise increase the index to start the next effect
  if ( digitalRead(BUTTON_2) == LOW) {
    effectsStop = !effectsStop;
  }
}

//triggered by button 2, turns effect rotation on / off
//(if rotation is off, the current effect will be repeated continuously)
//if button 1 is also being held, turn effects on / off
void ICACHE_RAM_ATTR effectRotaToggle() {
  if ( digitalRead(BUTTON_1) == LOW) {
    strip.pixelStripStopPattern = true;
    effectsStop = !effectsStop;
  } else {
    effectRota = !effectRota;
  }
}

//triggered by button 3, sets the strip brightness to the next
//brightness level in the brightnessLevels array (wrapping to the start if needed)
void ICACHE_RAM_ATTR brightnessAdjust() {
  brightnessIndex = (brightnessIndex + 1) % numBrightnessLevels;
  strip.setBrightness( brightnessLevels[ brightnessIndex ] );
}

//increments the effect index (wrapping if needed)
void incrementEffectIndex() {
  effectIndex = (effectIndex + 1) % numEffects;
}

void setup() {
  //initalize the led strip, and set the starting brightness
  strip.begin();
  strip.setBrightness( brightnessLevels[brightnessIndex] );

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  //because of the way my library currently works, effects occupy the processor until they end
  //so to break out of an effect, or change sytem values, we need to use interrupts
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), nextEffect, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), effectRotaToggle, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_3), brightnessAdjust, FALLING);

  strip.show();
  //Serial.begin(115200);

  randomSeed(ESP.getCycleCount()); //generate a random seed
  //fill in our random pallet
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
}

//!! If you want to change the main loop code, please read all the comments below and in the loop !!
//To remove an effect, simply change its case # to anything greater than the total number of effects (999 for ex)
//if you want to know about certain effects, please see comments in the library for said effect
//if you want to know how segments work, please see comments in segmentSet.h

//The main loop of the program, works as follows:
//if effectsStop is true, effects are "off", so we won't try to start the next effect
//otherwise we jump to the effect matching the effectIndex value using a switch statment
//we also "clean up" a bit by reseting direct to true and the breakCurrentEffect flag to false
//if we don't find an effect with the effectIndex, we increment the effectIndex until we do
//while an effect is running, button inputs can either lock the effect or skip to the next effect
//if we lock the effect (set effectRota to false), we do not increment effectIndex when the effect ends, essentially restarting the effect (with new colors if they're randomly choosen)
//if the effect is skipped, we set strip.pixelStripStopPattern and breakCurrentEffect to true
//strip.pixelStripStopPattern will stop the current effect, and breakCurrentEffect will break out of the current switch statement if needed (the switch case has more than one effect)
//once the effect ends (either naturally or from a button press), we incremented effectIndex (as long as effectRota is set true)
//and jump to the top of the main loop

void loop() {

  strip.fillStrip(RC(), false);
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  tempRandPallet[0] = 0; //background color for spin patterns (off)
  for (int i = 0; i < 2; i++) {
    //rowHalfCenSegments.flipSegDirectionEvery(1, true); //reverse the direction of each segment of rowLensesHalvesSegments
    breakEffectCheck();
    strip.colorSpin( rowHalfCenSegments, spinPatternX, SIZE(spinPatternX), tempRandPallet, 0, 1, true, 100, 100 );
  }

  tempRandPallet[0] = 0; //background color for spin patterns (off)
  tempRandPallet[1] = pink;
  tempRandPallet[2] = red; //background color for spin patterns (off)
  for (int i = 0; i < 2; i++) {
    rowCenSegments.flipSegDirectionEvery(1, true);
    breakEffectCheck();
    strip.colorSpin( rowCenSegments, spinPatternHeart, SIZE(spinPatternHeart), tempRandPallet, 0, 2, true, 100, 110 );
  }
  
  strip.patternSweepRand( 5, -1, 0, 1, 7, false, 0, 1, 70, 200 );
  
  strip.shooterSeg( colSegments, pallet, 5, 0, 8, 1, 1, 3, 2, false, false, 70, 150);

  strip.shooterSeg( rowHalfSegments, pallet, 5, 0, 8, 1, 1, 3, 2, true, false, 70, 150);
  
  //strip.colorSpinSimpleSet( colHalfSegments, pastelRainbowPattern, SIZE(pastelRainbowPattern), pastelRainbowPallet, 0, 5, -1, 0, 0, 1, 100, 80 );

  strip.waves( colSegments, pastelRainbowPallet, SIZE(pastelRainbowPallet),  pastelRainbowPattern, SIZE(pastelRainbowPattern), 100, false, 3, 45);
  
  strip.shooterSeg( rowHalfSegments, pallet, 5, 0, 8, 1, 3, 3, 4, true, false, 70, 150);

  strip.shooterSeg( colSegments, pallet, 5, 0, 8, 1, 3, 3, 4, false, false, 70, 150);

   strip.shooterSeg( colHalfFlipSegments, pallet, 3, 0, 5, 3, 1, 5, 4, true, false, 70, 150);
  
  strip.fillStrip(RC(), false);
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  tempRandPallet[0] = 0; //background color for spin patterns (off)
  for (int i = 0; i < 2; i++) {
    rowCenSegments.flipSegDirectionEvery(1, true);
    breakEffectCheck();
    strip.colorSpin( rowCenSegments, spinPatternHelix, SIZE(spinPatternHelix), tempRandPallet, 0, 1, true, 100, 100 );
  }
  
  strip.sonarWavesRand( rowSegments, 2, 0, 4, 8, false, true, true, false, 100, 110);

  //strip.sonarSpinRand( rowSegments, 6, 0, 4, 0, false, false, false, false, 100, 100);
  
  for (int i = 0; i < 2; i++) {
    colCenSegments.flipSegDirectionEvery(1, true);
    strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
    tempRandPallet[0] = 0; //background color for spin patterns (off)
  strip.fillStrip(tempRandPallet[2], false);
    breakEffectCheck();
    strip.colorSpin( colCenSegments, spinPatternArrowsVert2, SIZE(spinPatternArrowsVert2), tempRandPallet, 0, 1, true, 100, 110 );
  }

  //strip.fadingWavesRand( colSegments, 3, 4, 2, false, 200, 2, 40);
  for (int i = 0; i < 10; i++) {
    breakEffectCheck();
    strip.colorWipeRandomSeg( colSegments, 2, 7, 7, 90, true, true, true);
    breakEffectCheck();
    strip.colorWipeSeg(colSegments, 0, 7, 90, false, true, true);
    direct = !direct;
  }

  strip.doFireV2Seg( colSegments, firePallet, SIZE(firePallet), 25, 200, true, 300, 60);
  //strip.doFireV2Seg( colSegments, firePallet2, SIZE(firePallet2), 35, 120, 400, 60);

  //strip.sonar( rowHalfSegments, RC(), 1, 4, 50, 120 );

  strip.patternSweepRepeatRand(4, 0, 0, 2, 4, false, false, 0, 0, 1, 55, 100 );

  //strip.sonarWavesRand( colSegments, 1, 4, 8, 100, false, false, 30, 50);

 //strip.sonar( rowHalfSegments, RC(), 1, 4, 50, 120 );

  //strip.sonar( rowSegments, RC(), 1, 4, 50, 120 );

  //strip.doFireV2Seg( rowHalfSegments, firePallet, SIZE(firePallet), 45, 120, 400, 40);

  for (int i = 0; i < 5; i++) {
    uint32_t color = RC();
    strip.crossFadeColor(0, color, 30, 30);
    strip.crossFadeColor(color, 0, 30, 30);
  }

  strip.randomWaves( colSegments, 4, 3, 3, 50, direct, 7, 20);

  strip.randomWaves( rowSegments, 4, 2, 2, 50, direct, 7, 20);

  for (int i = 0; i < 4; i++) {
    breakEffectCheck();
    strip.colorWipeRandomSeg( rowHalfSegments, 2, 2, 0, 130, direct, false, true);
    breakEffectCheck();
    strip.colorWipeSeg(rowHalfSegments, 0, 0, 130, !direct, false, true);
    direct = !direct;
  }

  strip.colorSpinSimple( colHalfSegments, 5, 0, 0, 4, -1, 4, 0, 1, 170, 80 );

  strip.colorSpinSimple( colHalfSegments, 3, 0, 0, 7, -1, 7, 0, 1, 170, 60 );

  strip.colorSpinSimple( colHalfSegments, 1, 0, 0, 7, 3, 7, 0, 2, 170, 60 );

  strip.colorSpinSimple( rowHalfSegments, 5, 0, 0, 3, -1, 3, 0, 1, 170, 100 );

  strip.patternSweepRand( 12, white, -1, 0, 0, false, 0, 1, 60, 320 );

  strip.simpleStreamerRand( 5, 0, 7, 0, 0, true, 130, 70);

  strip.colorSpinSimple( rowSegments, 1, 0, 0, 5, 1, 0, 0, 2, 170, 80 ); //rainbow half

  strip.rainbowCycle(20, 3);

  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  strip.randomColorSet(off, true, tempRandPallet, SIZE(tempRandPallet), 100, 5, 12000);

  strip.rainbowWave( colSegments, 100, true, 8, 20);
  strip.rainbowWave( rowSegments, 100, true, 8, 20);

  strip.segGradientCycleRand(rowSegments, 3, 8, 150, true, 1, 100);
  strip.segGradientCycleRand(colSegments, 3, 8, 150, direct, 1, 100);

  strip.shooterSeg( colSegments, pallet, 3, 0, 8, 1, 1, 3, 4, false, false, 70, 150);

  strip.shooterSeg( rowHalfSegments, pallet, 3, 0, 8, 1, 1, 3, 4, true, false, 70, 150);

  //strip.segGradientCycle(colSegments, pastelRainbowPattern, SIZE(pastelRainbowPattern), pastelRainbowPallet, SIZE( pastelRainbowPallet ), 5, 100, true, 120);
  //strip.segGradientCycle(rowSegments, pastelRainbowPattern, SIZE(pastelRainbowPattern), pastelRainbowPallet, SIZE( pastelRainbowPallet ), 5, 100, true, 120);

  strip.fillStrip(RC(), false);
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  tempRandPallet[0] = 0; //background color for spin patterns (off)
  for (int i = 0; i < 2; i++) {
    rowCenSegments.flipSegDirectionEvery(1, true);
    breakEffectCheck();
    strip.colorSpin( rowCenSegments, spinPatternWave2, SIZE(spinPatternWave2), tempRandPallet, 0, 1, true, 100, 100 );
  }

  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  tempRandPallet[0] = 0; //background color for spin patterns (off)
  for (int i = 0; i < 2; i++) {
    rowCenSegments.flipSegDirectionEvery(1, true);
    breakEffectCheck();
    strip.colorSpin( rowCenSegments, spinPatternWave, SIZE(spinPatternWave), tempRandPallet, 0, 1, true, 100, 100 );
  }

  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  tempRandPallet[0] = 0; //background color for spin patterns (off)
  for (int i = 0; i < 2; i++) {
    //rowHalfCenSegments.flipSegDirectionEvery(1, true); //reverse the direction of each segment of rowLensesHalvesSegments
    breakEffectCheck();
    strip.colorSpin( rowHalfCenSegments, spinPatternArrows, SIZE(spinPatternArrows), tempRandPallet, 0, 1, true, 100, 110 );
  }

  strip.stripOff();
  strip.colorSpin( rowCenSegments, spinPatternUSflag, SIZE(spinPatternUSflag), pallet, 0, 1, false, 100, 100 );

  for (int i = 0; i < 4; i++) {
    strip.gradientCycleRand( 4, 8, 24 * 7, direct, 110);
    direct = !direct;
  }

}

//a quick shortening of the random color function, just to reduce the pattern function calls more readable
uint32_t RC() {
  return strip.randColor();
}
