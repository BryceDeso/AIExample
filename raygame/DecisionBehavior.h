#pragma once
#include "Behavior.h"
#include "Decision.h"

class DecisionBehavior : public Behavior
{
public:
	DecisionBehavior(Decision* root) { m_root = root; }
	void update(Agent* agent, float deltaTime) override;

private:
	Decision* m_root;
};

