#include "livingstats.h"
#include <stdio.h>

LivingStats::LivingStats(s16 health, s16 attack, s16 speed, s16 maxHealth, s16 points)
{
	this->health = health;
	this->attack = attack;
	this->speed = speed;
	this->maxHealth = maxHealth;
	this->points = points;
}

void LivingStats::Print(char* prefix)
{
	printf("%s ", prefix);
	if (health)
	{
		printf("htlh:%d ", health);
	}
	if (attack)
	{
		printf("atk:%d ", attack);
	}
	if (speed)
	{
		printf("spd:%d ", speed);
	}
	if (points)
	{
		printf("pts:%d ", points);
	}
	printf("\n");
}
