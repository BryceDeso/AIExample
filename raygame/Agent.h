#pragma once
#include "Actor.h"
#include <vector>

class Behavior;

class Agent : public Actor
{
public:
	Agent();
    ~Agent();

    /// <param name="x">Position on the x axis</param>
   /// <param name="y">Position on the y axis</param>
   /// <param name="icon">The symbol that will appear when drawn</param>
    Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce);

    void update(float deltaTime) override;

    float getMaxForce() { return m_maxForce; }
    void setMaxForce(float maxforce) { m_maxForce = maxforce; }

    //Add the given force to the total force
    void addForce(MathLibrary::Vector2 force);
    void addBehavior(Behavior* behavior);

    ///<summary>
    ///Returns the first behavior that matches the given type.
    ///If no behavior matches the given type, returns null.
    ///</summary>
    template<typename BehaviorType>
    BehaviorType* getBehavior();

private:
	MathLibrary::Vector2 m_force;
	float m_maxForce;

	std::vector<Behavior*> m_behaviors;
};

template<typename BehaviorType>
inline BehaviorType* Agent::getBehavior()
{
    //Iterates thorugh list of behaviors
    for (int i = 0; i < m_behaviors.size(); i++)
    {
        //Attempts to cast behavior at the current index as the given type.
        BehaviorType* behavior = dynamic_cast<BehaviorType*>(m_behaviors[i]);

        //if the cast is successful return the behavior that was found
        if (behavior)
        {
            return behavior;
        }
    }
    //if no behavior was found that match the type then return nullptr
    return nullptr;
}
