#include "ComplexEnemy.h"
#include "WanderBehavior.h"
#include "PursuitBehavior.h"
#include <Vector2.h>

void ComplexEnemy::start()
{
	Enemy::start();

	//intalize behaviors
	WanderBehavior* wander = new WanderBehavior(1);
	PursuitBehavior* pursue = new PursuitBehavior(getTarget(), 10);

	addBehavior(wander);
	addBehavior(pursue);

	m_wanderBehavior = getBehavior<WanderBehavior>();
	m_pursuitBehavior = getBehavior<PursuitBehavior>();


	//Set target to the given from the base class.
	setTarget(Enemy::getTarget());
}

void ComplexEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursuitBehavior->setTarget(target);
}

void ComplexEnemy::onCollision(Actor* other)
{
	Enemy::onCollision(other);

	Player* player = dynamic_cast<Player*>(other);

	//If actor is player damage it.
	if (player)
	{
		player->takeDamage(getDamage());
		//If player health is less than or equal to 0, set target to nullptr.
		if (player->getHealth() <= 0)
		{
			setTarget(nullptr);
		}
	}
}

//bool ComplexEnemy::checkTargetInSight(float angle)
//{
//	//Checks if the target has a value before continuing
//	if (this->getTarget() == nullptr)
//	{
//		return false;
//	}
//
//	//Find the vector representing the distance between the actor and its target
//	MathLibrary::Vector2 direction = this->getWorldPosition - this->getTarget()->getWorldPosition();
//	//Get the magnitude of the distance vector
//	float distance = direction.getMagnitude();
//	//Use the inverse cosine to find the angle of the dot product in radians
//	angle = (float)Math.Acos(Vector2.DotProduct(Forward, direction.Normalized));
//
//	//Return true if the angle and distance are in range
//	if (angle <= maxAngle && distance <= maxDistance)
//	{
//		return true;
//	}
//
//	return false;
//}
