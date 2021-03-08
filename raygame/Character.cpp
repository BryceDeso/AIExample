#include "Character.h"

Character::Character(float x, float y, float collisionRadius, const char* spriteFilePath, float health, float damage, float maxSpeed, float maxForce)
{
	m_damage = damage;
	m_health = health;
}
