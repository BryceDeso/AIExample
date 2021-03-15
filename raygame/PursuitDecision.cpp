#include "PursuitDecision.h"
#include "ComplexEnemy.h"

void PursuitDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		enemy->getPursuit();
		enemy->getWander();
		enemy->getEvade();
	}
}
