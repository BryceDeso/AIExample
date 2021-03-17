#include "Node.h"
#include "raylib.h"
#include "Edge.h"

Node::Node(int x, int y, int nodeSize)
{
	graphPosition.x = x;
	graphPosition.y = y;
	size = nodeSize;
}

void Node::draw()
{
	//Draws circle that represents the node.
	DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, size, GetColor(color));
	//Draws all edges connected to this node.
	for (int i = 0; i < edges.size(); i++)
	{
		//If node is first connected node, will prevent the edge from drawing next node.
		if (edges[i]->connectedNode1->graphPosition == graphPosition)
		{
			edges[i]->draw();
		}
	}
}

void Node::update(float deltaTime)
{
	Actor::update(deltaTime);
	for (int i = 0; i < edges.size(); i++)
	{
		//If node is first connected node, will prevent the edge from drawing next node.
		if (edges[i]->connectedNode1->graphPosition == graphPosition)
		{
			edges[i]->update(deltaTime);
		}
	}
}
