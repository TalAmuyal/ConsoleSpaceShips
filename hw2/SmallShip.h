#ifndef SMALL_SHIP_H_
#define SMALL_SHIP_H_

#include "Ship.h"

class SmallShip : public Ship
{
public:
	SmallShip(unsigned xPositin, unsigned yPosition);

	void rotate();
};

#endif /* BIG_SHIP_H_ */