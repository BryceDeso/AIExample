#include "EvadeBehavior.h"
#include "Agent.h"
#include "Actor.h"

EvadeBehavior::EvadeBehavior()
{
	m_target = nullptr;
	setForceScale(1);
}

EvadeBehavior::EvadeBehavior(Actor* target, float fleeForce)
{
	m_target = target;
	setForceScale(fleeForce);
}

MathLibrary::Vector2 EvadeBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize((m_target->getWorldPosition() + agent->getWorldPosition()) + (m_target->getVelocity() * 2));

	//Scale the direction vector by fleeForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();

	//Add current velocity from desired velocity to find steering force;
	MathLibrary::Vector2 steeringForce = desiredVelocity + agent->getVelocity();
	return steeringForce;
}

void EvadeBehavior::update(Agent* agent, float deltaTime)
{
	//IF agent isnt equal to null, calculate a new force and apply it.
	if (agent)
	{
		agent->addForce(calculateForce(agent));
	}
}