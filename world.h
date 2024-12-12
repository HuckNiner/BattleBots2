#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "entity.h"
#include "pubsub.h"
#include "botdata.h"

using namespace std;

class World: public Subscriber
{
private:
	vector<Entity*> entities;
	vector<Entity*> collisions;
	vector<Entity*> deletions;

	void checkCollision(Entity* entity, Entity* entity2);

public:
	World();
	void clearWorld();
	vector<BotData *> initWorld(int width, int height);

	bool isClear(int x, int y);
	bool isOnExit(int x, int y);
	EntityData scan(int x, int y, int rotation);

	void tick();
	void receiveMessage(string channel, string message, void* data);
};

#endif
