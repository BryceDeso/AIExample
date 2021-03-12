#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"
#include "raylib.h"

WanderBehavior::WanderBehavior()
{
	m_target = nullptr;
	m_wanderForce = 1;
}

WanderBehavior::WanderBehavior(float maxForce)
{
	m_target = nullptr;
	m_wanderForce = maxForce;
}

MathLibrary::Vector2 WanderBehavior::calculateForce(Agent* agent)
{
	//Initalize floats
	float circleDistance= 3;
	float circleRadius = 6;
	float wanderAngle = 20;

	//Initalize vector2s
	MathLibrary::Vector2 circleCenter;
	MathLibrary::Vector2 circleDisplacement;
	MathLibrary::Vector2 direction;
	MathLibrary::Vector2 desiredVelocity;
	MathLibrary::Vector2 steeringForce;

	//Get the circle's center by getting the agent's forward then scaling it by the desired distance to put the circle.
	circleCenter = agent->getForward() * circleDistance;
	//Offset the angle to make sure to get a diffrent angle everytime.
	wanderAngle += (rand() * wanderAngle) - (wanderAngle * .5f);
	//Get a random direction for the agent to move in.
	direction = MathLibrary::Vector2(cos(wanderAngle), sin(wanderAngle));
	//Get the circle's displacement by adding the circle's center by direction multiplied by the circles radius.
	circleDisplacement = circleCenter + (direction * circleRadius);

	return circleDisplacement;
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