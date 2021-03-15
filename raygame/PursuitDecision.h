#pragma once
#include "ABDecisions.h"
class PursuitDecision : public ABDecisions
{
	ABDecisions::ABDecisions;
	void makeDecision(Agent* agent, float deltaTime) override;
};

