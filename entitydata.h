#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "entity.h"

class EntityData
{
private:
	Entity* entity;

public:
	EntityData(Entity *entity);

	float getX();
	float getY();
	EntityType getType();
	float getRotation();

};

#endif
