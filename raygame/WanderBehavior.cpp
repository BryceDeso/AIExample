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
	//Initalizing circle distance and radius as well as random values used to copy wandering behavior.
	float circleRadius = 10;
	float circleDistance = 50;
	float randomNumX = GetRandomValue(-50, 50);
	float randomNumY = GetRandomValue(-50, 50);
	MathLibrary::Vector2 circleCenter;
	MathLibrary::Vector2 displacementForce;
	MathLibrary::Vector2 wanderAngle;
	MathLibrary::Vector2 wanderForce;

	//Setting the circle's center to agent's forward multiplied by circle's distance then normalized to move circle away from agent. 
	circleCenter = m_target->getForward() * circleDistance;
	circleCenter.normalize(circleCenter);

	//Setting displacementForce to the vector2 cordinat
	displacementForce = MathLibrary::Vector2(0, -1);
	displacementForce = displacementForce * circleRadius;
	agent->setVelocity(MathLibrary::Vector2(randomNumX, randomNumY));

	wanderAngle = MathLibrary::Vector2(randomNumX, randomNumY);

	wanderForce = circleCenter + displacementForce;
	return wanderForce;
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	//If agent isnt equal to null, calculate a new force and apply it.
	if (agent)
	{
		agent->addForce(calculateForce(agent));
		DrawCircleLines(agent->getForward().x * 36, agent->getForward().y * 36, 1, WHITE);
	}
}