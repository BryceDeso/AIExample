#pragma once

class Agent;

///<summery>
///Abstract class for a all decisions.
///<summary
class Decision
{
public:
	virtual void makeDecision(Agent* agent, float deltatime) = 0;
};