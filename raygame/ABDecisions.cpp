#include "ABDecisions.h"

ABDecisions::ABDecisions(Decision* leftDecision, Decision* rightDecision)
{
	m_leftChild = leftDecision;
	m_rightChild = rightDecision;
}

void ABDecisions::makeDecision(Agent* agent, float deltaTime)
{
	//Call checkCondition funtion for this decision
	if (checkCondition(agent, deltaTime))
	{
		//If the funtion returns true and the left child isnt null, move to left node.
		if (m_leftChild)
		{
			m_leftChild->makeDecision(agent, deltaTime);
		}
	}
	else
	{
		//If the funtion returns true and the right child isnt null, move to right node.
		if (m_rightChild)
		{
			m_rightChild->makeDecision(agent, deltaTime);
		}
	}
}
