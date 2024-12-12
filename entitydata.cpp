#include "entitydata.h"

EntityData::EntityData(Entity* entity)
{
	this->entity = entity;
}

float EntityData::getX()
{
	return entity->getX();
}

float EntityData::getY()
{
	return entity->getY();
}

EntityType EntityData::getType()
{
	return entity->getType();
}

float EntityData::getRotation()
{
	return entity->getRotation();
}
