#pragma once
#include "Enemy.h"
#include "Player.h"

class WanderBeahvior;
class PursuitBehavior;
class EvadeBehavior;


class ComplexEnemy : public Enemy
{
public:
	using Enemy::Enemy;
	void start() override;
	void setTarget(Actor* target) override;
	void onCollision(Actor* other) override;
	//void update(float deltaTime) override;
	WanderBeahvior* getWander() { return m_wanderBehavior; }
	PursuitBehavior* getPursuit() { return m_pursuitBehavior; }
	EvadeBehavior* getEvade() { return m_evadeBeavior; }

	bool checkTargetInSight(float angle = 2);
	bool checkTargetinRange(float range);

private:
	WanderBeahvior* m_wanderBehavior;
	PursuitBehavior* m_pursuitBehavior;
	EvadeBehavior* m_evadeBeavior;
};

