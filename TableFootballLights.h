#ifndef TABLE_FOOTBALL_LIGHTS_H
#define TABLE_FOOTBALL_LIGHTS_H

#include "ColourArray.h"

void Startup();

struct InputState
{
	bool m_scorePlayer0;
	bool m_scorePlayer1;
};

const ColourArray& Update( const InputState& inputs );

#endif