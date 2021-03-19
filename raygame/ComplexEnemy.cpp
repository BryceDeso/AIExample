#include "ComplexEnemy.h"
#include "WanderBehavior.h"
#include "PursuitBehavior.h"
#include "EvadeBehavior.h"

void ComplexEnemy::start()
{
	Enemy::start();

	//intalize behaviors
	EvadeBehavior* evade = new EvadeBehavior(getTarget(), 10);
	WanderBehavior* wander = new WanderBehavior(1);
	PursuitBehavior* pursue = new PursuitBehavior(getTarget(), 10);

	addBehavior(evade);
	addBehavior(wander);
	addBehavior(pursue);

	m_wanderBehavior = getBehavior<WanderBehavior>();
	m_pursuitBehavior = getBehavior<PursuitBehavior>();
	m_evadeBehavior = getBehavior<EvadeBehavior>();


	//Set targte to the given from the base class.
	setTarget(Enemy::getTarget());
}

void ComplexEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursuitBehavior->setTarget(target);
	m_evadeBehavior->setTarget(target);
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
