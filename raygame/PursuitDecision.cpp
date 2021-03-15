#include "PursuitDecision.h"
#include "ComplexEnemy.h"
#include "WanderBehavior.h"

void PursuitDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		enemy->getPursuit()->setEnabled(true);
		enemy->getWander()->setEnabled(false);
		enemy->getEvade()->setEnabled(false);
	}
}
