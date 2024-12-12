#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

using namespace std;

const int ticksPerTurn = 20;
const int tileSize = 64;

enum EntityType {TankA, TankB, TankC, TankD, WallNS, WallEW, WallN, WallS, WallE, WallW, Tower, CornerEN, CornerES, CornerWN, CornerWS, Tree, Rock1, Rock2, Exit};

class Entity
{
private:
	float x;
	float y;
	float rotation;
	float targetX;
	float targetY;
	float targetRotation;

	int width;
	int height;
	EntityType type;
	bool moving;
	bool falling;

	int tickCounter;
	float adjustAmount;

protected:
	vector<Entity*> collisions;

public:
	Entity(float x, float y, int width, int height, EntityType type, float rotation = 0);

	float getX();
	float getY();
	int getWidth();
	int getHeight();
	EntityType getType();
	float getRotation();
	bool getMoving();
	bool getFalling();

	void setX(float x);
	void setY(float y);
	void setRotation(float rotation);
	void setTargetX(float x);
	void setTargetY(float y);
	void setTargetRotation(float rotation);
	void setMoving(bool moving);
	void setFalling(bool falling);

	void addCollision(Entity* entity);
	virtual bool handleCollisions();

	virtual void tick();
};

#endif
