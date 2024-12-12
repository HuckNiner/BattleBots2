#include "utility.h"
#include "entity.h"

Vector2 getForwardCoords(int x, int y, int rotation)
{
	if (rotation == 0)
		return { (float)x, (float)y - tileSize };

	if (rotation == 90)
		return { (float)x + tileSize, (float)y };

	if (rotation == 180)
		return { (float)x, (float)y + tileSize };

	if (rotation == 270)
		return { (float)x - tileSize, (float)y };

	return { (float)x, (float)y };
}
