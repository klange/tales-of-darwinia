#include "livingstats.h"

LivingStats::LivingStats(u16 health, u16 attack, u16 speed, u16 maxHealth, u16 points)
{
	this->health = health;
	this->attack = attack;
	this->speed = speed;
	this->maxHealth = maxHealth;
	this->points = points;
}
