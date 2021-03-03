#pragma once
#include "SteeringBehavior.h"
class Actor;

class WanderBehavior :	public SteeringBehavior
{
public:
	WanderBehavior();
	WanderBehavior(Actor* target, float maxForce);

	void setTarget(Actor* actor) { m_target = actor; }
	Actor* getTarget() { return m_target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;

private:
	Actor* m_target;
	float m_wanderForce;

};

