#include "WanderBehavior.h"
#include "ComplexEnemy.h"
#include "WanderBehavior.h"
#include "WanderDecision.h"

void WanderDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* ghost = dynamic_cast<ComplexEnemy*>(agent);

	if (!ghost)
	{
		ghost->getWander()->setEnabled(true);
		ghost->getPursuit()->setEnabled(false);
	}
}
