#include "TableFootballLights.h"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define NEOPIXELS_PIN 3

#define PLAYER_0_SCORE_PIN 4
#define PLAYER_1_SCORE_PIN 5

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(kNumPixels, NEOPIXELS_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
	pixels.begin(); // This initializes the NeoPixel library.

	// Initialize serial communications (if there is a PC attached) at 57600 bps:
	Serial.begin(57600);
	randomSeed(analogRead(0));

	pinMode( PLAYER_0_SCORE_PIN, INPUT_PULLUP );
	pinMode( PLAYER_1_SCORE_PIN, INPUT_PULLUP );

	// Startup the app
	Startup();
}

void loop()
{
	// Update and get the ColourArray from TableFootballLights
	InputState inputState;
	inputState.m_scorePlayer0 = (digitalRead( PLAYER_0_SCORE_PIN ) == LOW);
	inputState.m_scorePlayer1 = (digitalRead( PLAYER_1_SCORE_PIN ) == LOW);
	const ColourArray& colourArray = Update( inputState );
	for( int i = 0; i < kNumPixels; i++ )
	{
		const Colour& colour = colourArray[i];
		pixels.setPixelColor( i, pixels.Color( colour.R(), colour.G(), colour.B() ) );
	}
	pixels.show();
}
