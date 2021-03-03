#include "FleeBehavior.h"
#include "Agent.h"
#include "Actor.h"

FleeBehavior::FleeBehavior()
{
	m_target = nullptr;
	m_fleeForce = 1;
}

FleeBehavior::FleeBehavior(Actor* target, float fleeForce)
{
	m_target = target;
	m_fleeForce = fleeForce;
}

MathLibrary::Vector2 FleeBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() + agent->getWorldPosition());

	//Scale the direction vector by fleeForce
	MathLibrary::Vector2 desiredVelocity = direction * m_fleeForce;

	//Add current velocity from desired velocity to find steering force;
	MathLibrary::Vector2 steeringForce = desiredVelocity + agent->getVelocity();
	return steeringForce;
}

void FleeBehavior::update(Agent* agent, float deltaTime)
{
	//IF agent isnt equal to null, calculate a new force and apply it.
	if (agent)
	{
		agent->addForce(calculateForce(agent));
	}
}