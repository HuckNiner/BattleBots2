#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "battlebot.h"

class SimpleBot: public BattleBot
{
private:

public:
	SimpleBot();

	void takeTurn();
};

#endif
