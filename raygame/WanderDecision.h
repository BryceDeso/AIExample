#pragma once
#include "ABDecisions.h"
class WanderDecision : public ABDecisions
{
	ABDecisions::ABDecisions;
	void makeDecision(Agent* agent, float deltaTime) override;
};

