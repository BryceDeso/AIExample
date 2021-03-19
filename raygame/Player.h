#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player() {};
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed = 5, float maxForce = 10);
	void update(float deltatime) override;
	void debug() override;

private:
	float m_health;
};