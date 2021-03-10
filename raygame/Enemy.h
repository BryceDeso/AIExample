#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="icon">The symbol that will appear when drawn</param>
	Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, Actor* target, float health = 1, float damage = 1, float maxSpeed = 1, float maxForce = 1);

	void update(float deltaTime) override;

	virtual void setTarget(Actor* target) { m_target = target; }
	virtual Actor* getTarget() { return m_target; }

private:
	Actor* m_target;
};

