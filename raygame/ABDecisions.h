#pragma once
#include "Decision.h"

///<summery>
///A decision that has two children attached to it.
///<summary
class ABDecisions : public Decision
{
public:
	ABDecisions(Decision* leftDecision = nullptr, Decision* rightDecision = nullptr);

	///<summery>
	///Checks the condition and transitions to a different decision based on the return value
	///<summary
	virtual void makeDecision(Agent* agent, float deltaTime) override;

	///<summery>
	///Checks if a certain condition has been met and return the result
	///<summary
	virtual bool checkCondition(Agent* agent, float deltaTime) { return false; }

private:
	Decision* m_leftChild;
	Decision* m_rightChild;
};