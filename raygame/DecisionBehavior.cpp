#include "DecisionBehavior.h"

void DecisionBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
	{
		m_root->makeDecision(agent, deltaTime);
	}
}