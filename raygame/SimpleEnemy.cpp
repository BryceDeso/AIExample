#include "SimpleEnemy.h"
#include "SeekBehavior.h"
#include "WanderBehavior.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Check if target is null. If so return false.
	if (getTarget() == nullptr)
	{
		return false;
	}

	//Find the direction vector that represents where the target is realitive to the enemy.
	MathLibrary::Vector2 targetDirection = getTarget()->getWorldPosition() - getWorldPosition();

	//Find the dot product of the enemy's forward and the direction vector
	MathLibrary::Vector2 dotProduct;
	dotProduct.dotProduct(getForward(), targetDirection);

	//Find the angle using the dot product
	//Check if that angle is greater than the enemy's viewing angle(any value you see fit) is true.
	MathLibrary::Vector2  angleFound;
	if (angleFound.findAngle(dotProduct, getForward()) > 1)
	{
		return true;
	}

	//return if the enemy saw the target
	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
	//Check to see if the enemy ran into the player
	//if the enemy has run into the player, deal damge to player
	if (checkCollision(other) == true)
	{
		dynamic_cast<Character*>(other)->takeDamage(10);
		//if the player's health is less than 0, set the target to nullptr
		if (dynamic_cast<Character*>(other)->getHealth() <= 0)
		{
			this->setTarget(nullptr);
		}
	}
}

void SimpleEnemy::start()
{
	//Call base start fuintion
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = WANDER;

	//initalize memeber variables
	m_seek = getBehavior<SeekBehavior>();

	m_wander = getBehavior<WanderBehavior>();

	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltatime)
{
	//Create a switch statment for the state machine

	switch (m_currentState)
	{
	case WANDER:
		//The Switch should transition to the wander state if the target is not in sight
		//You can set the wander force to be whatever value as you see fit but be sure to set seekforce to 0
		if (checkTargetInSight() == false)
		{
			m_wander->setForceScale(3);
			m_seek->setForceScale(0);
			m_seek->setTarget(m_seek->getTarget());
		}
		break;
	case SEEK:
		if (checkTargetInSight() == true)
		{
			//the switch should transition to seek state if the target is in sight
			//You can set the seek force to be whatever you want it to be but be sure to set wander force to 0
			m_seek->setForceScale(2);
		}
		break;

	default:
		m_wander->setForceScale(3);
		break;
	}

	Enemy::update(deltatime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}