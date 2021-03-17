#include "Graph.h"
#include "Node.h"
#include "Edge.h"

Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_height = height;
	m_width = width;

	createGraph(nodeSize, nodeSpacing);
}

void Graph::draw()
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->draw();
	}
}

void Graph::update(float deltaTime)
{
	Actor::update(deltaTime);

	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->update(deltaTime);
	}
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;

	//loops for the amount of nodes in graph.
	for (int i = 0; i < m_width * m_height; i++)
	{
		//Create a new node with the current graph position and size.
		Node* currentNode = new Node(xPos, yPos, nodeSize);

		//Set the local offset for spacing.
		MathLibrary::Vector2 nodeLocalPosition = { xPos * nodeSpacing, yPos * nodeSpacing };
		currentNode->setLocalPosition(nodeLocalPosition);

		//Add the node as a child of the grid and update the list.
		addChild(currentNode);
		m_nodes.push_back(currentNode);
		
		//Connect the node to all nodes in range.
		for (int j = 0; j < m_nodes.size(); j++)
		{
			//find the displacement between the current node being added and the node being evaluated.
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;

			//check if the magnitude of the displacement is farther then the maximum.
			if (displacement.getMagnitude() <= 1.42 && displacement.getMagnitude() > 0)
			{
				//Create new edge that connects two nodes.
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}

		//Increase the graph position on the x.
		xPos++;

		//If the x position is greater than the width reset to 0 and increase the y position.
		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}
