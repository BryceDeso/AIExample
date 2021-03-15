#include "PursuitBehavior.h"
#include "Agent.h"
#include "Actor.h"

PursuitBehavior::PursuitBehavior()
{
	m_target = nullptr;
	m_seekForce = 1;
}

PursuitBehavior::PursuitBehavior(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}

MathLibrary::Vector2 PursuitBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());

	//Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;

	//Subtract current velocity from desired velocity to find steering force;
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void PursuitBehavior::update(Agent* agent, float deltaTime)
{
	//IF agent isnt equal to null, calculate a new force and apply it.
	if (agent)
	{
		agent->addForce(calculateForce(agent));
	}
}
