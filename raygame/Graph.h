#pragma once
#include "Actor.h"
#include <vector>
#include <deque>

class Node;

class Graph : public Actor
{
public:
	Graph(int width, int height, int nodeSize, int nodeSpacing);
	void draw() override;
	void update(float deltaTime) override;

	void BFS(int startX, int startY, int goalX, int goalY);
	void Dijkstra(int startX, int startY, int goalX, int goalY);
	Node* getNode(int xPos, int yPos);
	std::deque<Node*> sort(std::deque<Node*> list);
	bool checkDeque(std::deque<Node*> deque, Node* node);
	
private:
	void createGraph(int nodeSize, int nodeSpacing);

private:
	int m_height;
	int m_width;
	std::vector<Node*> m_nodes;
};