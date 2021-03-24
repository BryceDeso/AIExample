#pragma once
#include "Actor.h"
#include <vector>

class Edge;

class Node : public Actor
{
public:
	Node(int x, int y, int nodeSize);
	std::vector<Edge*> edges;
	MathLibrary::Vector2 graphPosition;

	int color = 0xFFFFFFFF;
	int size = 1;

	bool visited;
	void draw() override;
	void update(float deltaTime) override;

	Node* m_previous;
	Node* getPrevious() { return m_previous; }
	void setPrevious(Node* previous) { m_previous = previous; }

	float m_gScore;
	float getGScore() { return m_gScore; }
	void setGScore(float gscore) { m_gScore = gscore; }
};

