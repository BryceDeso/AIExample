#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"
#include "raylib.h"

WanderBehavior::WanderBehavior()
{
	m_target = nullptr;
	m_wanderForce = 1;
}

WanderBehavior::WanderBehavior(Actor* target, float maxForce)
{
	m_target = target;
	m_wanderForce = maxForce;
}

MathLibrary::Vector2 WanderBehavior::calculateForce(Agent* agent)
{
	float wanderRadius = 10;
	float wanderDistance = 5;
	float wanderJitter = 1;
	float randomNum = GetRandomValue(0, 20);

	MathLibrary::Vector2::normalize(m_target->getWorldPosition()

	//Find the direction ot move in.
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());

	//Scale the direction vector by seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_wanderForce;

	//Subtract current velocity from desired velocity to find steering force;
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	//IF agent isnt equal to null, calculate a new force and apply it.
	if (agent)
	{
		agent->addForce(calculateForce(agent));
		DrawCircleLines(agent->getForward().x * 36, agent->getForward().y * 36, 1, WHITE);
	}
}