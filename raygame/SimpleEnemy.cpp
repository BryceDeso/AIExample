#include "SimpleEnemy.h"
#include "SeekBehavior.h"
#include "WanderBehavior.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Check if target is null. If so return false.

	//Find tge direction vector that represents where the target is realitive to the enemy.

	//Find the dot product of the enemy's forward and the direction vector

	//Find the angle using the dot product

	//Chech if that angle is greater than the enemy's viewing angle(any value you see fit is true)

	//return if the enemy saw the target
	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
	//Check to see if the enemy ran into the player

	//if th enemy has run into the player, deal damge to player

	//if the player's health is less than 0, set the target to nullptr
}

void SimpleEnemy::start()
{
	//Call base start fuintion
	Enemy::start();

	//Set the default state of the enemy


	//initalize memeber variables
}

void SimpleEnemy::update(float deltatime)
{
	//Create a switch statment for the state machine
	//The Switch should transition to the wander state if the target is not in sight
	//You can set the wander force to be whatever value you asee fit but be sure to set seekforce to 0

	//the switch should transition to seek state if the target is in sight
	//You can set the seek force to be whatever you want it to be but be sure to set wander force to 0

	Enemy::update(deltatime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}
