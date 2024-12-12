#include <map>
#include <string>
#include "entity_view.h"
#include "textures.h"

struct SpriteSheetInfo
{
	string fileName;
	int numFrames = 0;
};

map<EntityType, SpriteSheetInfo> spriteMapping = {
	{TankA, {"resources/tankA.png", 1}},
	{TankB, {"resources/tankB.png", 1}},
	{TankC, {"resources/tankC.png", 1}},
	{TankD, {"resources/tankD.png", 1}},
	{Tree, {"resources/tree.png", 1}},
	{WallNS, {"resources/wallns.png", 1}},
	{WallEW, {"resources/wallew.png", 1}},
	{WallN, {"resources/walln.png", 1}},
	{WallS, {"resources/walls.png", 1}},
	{WallE, {"resources/walle.png", 1}},
	{WallW, {"resources/wallw.png", 1}},
	{CornerEN, {"resources/corneren.png", 1}},
	{CornerES, {"resources/corneres.png", 1}},
	{CornerWN, {"resources/cornerwn.png", 1}},
	{CornerWS, {"resources/cornerws.png", 1}},
	{Tower, {"resources/tower.png", 1}},
	{Rock1, {"resources/rock1.png", 1}},
	{Rock2, {"resources/rock2.png", 1}},
	{Exit, {"resources/exit.png", 1}},
};

EntityView::EntityView(Entity *entity)
{
	this->entity = entity;
	texture = Textures::loadTexture(spriteMapping[entity->getType()].fileName);
	frame = 0;
	delay = 20;
}

bool EntityView::isViewFor(Entity* entity)
{
	return this->entity == entity;
}

void EntityView::draw()
{
	int animationDelay = 20;
	int numFrames = spriteMapping[entity->getType()].numFrames;

	if (entity->getMoving())
	{
		delay--;

		if (delay == 0)
		{
			frame = (frame + 1) % numFrames;
			delay = animationDelay;
		}
	}
	else
	{
		frame = 0;
		delay = animationDelay;
	}

	float frameWidth = texture.width / numFrames;
	// Do we need to adjust this for different animations?
	int row = 0; 
	Rectangle frameRec = { frame * frameWidth, row * frameWidth, frameWidth, frameWidth };

	float x = entity->getX();
	float y = entity->getY();

	// With DrawTexturePro, the origin is in sprite coords and the x,y of where it
	// gets drawn is where the origin is drawn.
	DrawTexturePro(texture, frameRec, { x + frameWidth / 2, y + frameWidth / 2, frameWidth, frameWidth }, { frameWidth / 2, frameWidth / 2 }, entity->getRotation(), WHITE);
}