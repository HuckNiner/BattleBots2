#include <iostream>
#include <algorithm>
#include "entity.h"

// We need to complete the animation sooner to allow
// for inconsistencies in the frames per second measurement
const int ticksToAdjust = ticksPerTurn - 10;

Entity::Entity(float x, float y, int width, int height, EntityType type, float rotation)
{
	this->x = x;
	this->y = y;
	this->rotation = rotation;
	this->targetX = x;
	this->targetY = y;
	this->targetRotation = rotation;
	this->width = width;
	this->height = height;
	this->type = type;
	this->moving = false;
	this->falling = false;
	this->tickCounter = -1;
	this->adjustAmount = 0;
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

int Entity::getWidth()
{
	return width;
}

int Entity::getHeight()
{
	return height;
}

void Entity::setX(float x)
{
	this->x = x;
}

void Entity::setY(float y)
{
	this->y = y;
}

void Entity::setTargetX(float x)
{
	if (this->x != x)
	{
		this->targetX = x;
		tickCounter = ticksToAdjust;
		adjustAmount = (x - this->x) / ticksToAdjust;
	}
}

void Entity::setTargetY(float y)
{
	if (this->y != y)
	{
		this->targetY = y;
		tickCounter = ticksToAdjust;
		adjustAmount = (y - this->y) / ticksToAdjust;
	}
}

EntityType Entity::getType()
{
	return type;
}

float Entity::getRotation()
{
	return rotation;
}

void Entity::setRotation(float rotation)
{
	this->rotation = rotation;
}

void Entity::setTargetRotation(float rotation)
{
	if (this->rotation != rotation)
	{
		this->targetRotation = rotation;
		tickCounter = ticksToAdjust;
		adjustAmount = (rotation - this->rotation) / ticksToAdjust;
	}
}

bool Entity::getMoving()
{
	return moving;
}

bool Entity::getFalling()
{
	return falling;
}

void Entity::setMoving(bool moving)
{
	this->moving = moving;
}

void Entity::setFalling(bool falling)
{
	this->falling = falling;
}

void Entity::tick()
{
	if (tickCounter == 0)
	{
		tickCounter = -1;
		x = targetX;
		y = targetY;
		rotation = (int) targetRotation % 360;
		targetRotation = rotation;
	}

	if (x != targetX)
	{
		x += adjustAmount;
		tickCounter--;
	}

	if (y != targetY)
	{
		y += adjustAmount;
		tickCounter--;
	}

	if (rotation != targetRotation)
	{
		rotation += adjustAmount;
		tickCounter--;
	}

}

void Entity::addCollision(Entity* entity)
{
	if (find(collisions.begin(), collisions.end(), entity) == collisions.end())
		collisions.push_back(entity);
}

bool Entity::handleCollisions()
{
	collisions.clear();
	return false;
}
