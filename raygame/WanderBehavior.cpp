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
	float circleDistance = 2;
	MathLibrary::Vector2 circleCenter;
	circleCenter = agent->getWorldPosition() * circleDistance;
	

	MathLibrary::Vector2 shutUpErrorList;
	return shutUpErrorList;
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	//If agent isnt equal to null, calculate a new force and apply it.
	if (agent)
	{
		agent->addForce(calculateForce(agent));
	}
}

void WanderBehavior::draw(Agent* agent)
{

}