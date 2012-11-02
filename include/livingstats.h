#ifndef LIVINGSTATS_H_
#define LIVINGSTATS_H_

#include <nds.h>

class LivingStats
{
public:
	LivingStats(u16 health, u16 attack, u16 speed, u16 maxHealth, u16 points);
	u16 health;
	u16 attack;
	u16 speed;
	u16 maxHealth;
	u16 points;
};


#endif /* LIVINGSTATS_H_ */
