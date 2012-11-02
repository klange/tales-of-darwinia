#ifndef LIVINGSTATS_H_
#define LIVINGSTATS_H_

#include <nds.h>

class LivingStats
{
public:
	LivingStats(s16 health, s16 attack, s16 speed, s16 maxHealth, s16 points);
	void Print(char *prefix);

	s16 health;
	s16 attack;
	s16 speed;
	s16 maxHealth;
	s16 points;
};


#endif /* LIVINGSTATS_H_ */
