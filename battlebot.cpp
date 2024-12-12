#include "battlebot.h"

BattleBot::BattleBot()
{

}

void BattleBot::turnLeft()
{
	data->turnLeft();
}

void BattleBot::turnRight()
{
	data->turnRight();
}

bool BattleBot::frontIsClear()
{
	return data->frontIsClear();
}

bool BattleBot::rightIsClear()
{
	return data->rightIsClear();
}

bool BattleBot::leftIsClear()
{
	return data->leftIsClear();
}

bool BattleBot::amOnExit()
{
	return data->amOnExit();
}

bool BattleBot::facingNorth()
{
	return data->facingNorth();
}

bool BattleBot::facingSouth()
{
	return data->facingSouth();
}

bool BattleBot::facingEast()
{
	return data->facingEast();
}

bool BattleBot::facingWest()
{
	return data->facingWest();
}

EntityData BattleBot::scan()
{
	return data->scan();
}

void BattleBot::move()
{
	data->move();
}
