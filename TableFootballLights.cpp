#include "TableFootballLights.h"

static unsigned int numPoints[2];
static const unsigned int kMaxPoints = 10;

static const Colour kRed( 255, 60, 30 );
static const Colour kGreen( 50, 255, 50 );
static const Colour kBlue( 20, 40, 255 );

static ColourArray colourArray;
static InputState previousInputState;

void resetScores()
{
	numPoints[0] = numPoints[1] = 0;
}

void incrementScore( unsigned int team )
{
	numPoints[ team ]++;
}

void Startup()
{
	resetScores();
	memset( &previousInputState, 0, sizeof( previousInputState ) );
}

#define LATCH( field ) input.field = inputState.field && !previousInputState.field

const ColourArray& Update( const InputState& inputState )
{
	// Latch the inputs
	InputState input;
	LATCH( m_scorePlayer0 );
	LATCH( m_scorePlayer1 );
	previousInputState = inputState;

	if( input.m_scorePlayer0 )
	{
		numPoints[0]++;
		if( numPoints[0] > kMaxPoints )
		{
			numPoints[0] = 0;
		}
	}
	if( input.m_scorePlayer1 )
	{
		numPoints[1]++;
		if( numPoints[1] > kMaxPoints )
		{
			numPoints[1] = 0;
		}
	}

	colourArray.Clear();
	for( unsigned int i = 0; i < kMaxPoints; ++i )
	{
		if( i < numPoints[0] )
		{
			colourArray[i] = kRed;
		}
		if( i < numPoints[1] )
		{
			colourArray[kNumPixels - 1 - i] = kBlue;
		}
	}

	return colourArray;
}
