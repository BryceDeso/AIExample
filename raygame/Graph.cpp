#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <raylib.h>
#include <deque>

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

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{
	//Get refernece to start and end nodes
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	//if the start or end is null return
	if (!start || !goal)
	{
		return;
	}

	//Set color to start  and mark as visited
	start->color = ColorToInt(GREEN);
	start->visited = true;

	//set the iterator to be the start node
	Node* currentNode = start;

	//Create a queue to store the nodes
	std::deque<Node*> queue;
	//ad the the start node to the queue
	queue.push_front(start);

	//While queue isnt empty, search for goal
	while (!queue.empty())
	{
		//Set the current node ot be the first item in the queue
		currentNode = queue[0];
		//remove the first item from the queue
		queue.pop_front();

		//Check if the iterator is the goal node
		if (currentNode == goal)
		{
			//Set the current node color to be yellow to mark it as found
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		//If the node wasnt the goal loop through its edges to get its neighbors
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a pointer to store the node at the other end of the edge
			Node* currentEdgeEnd = nullptr;

			//Set the pointer to be the opposite end of the edge
			if (currentNode == currentNode->edges[i]->connectedNode2)
			{
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			}
			else
			{
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;
			}

			//If the node at the opposite end hasnt been visited mark as visited then add to queue
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_back(currentEdgeEnd);
			}
		}
	}
}

void Graph::Dijkstra(int startX, int startY, int goalX, int goalY)
{
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	if (!start || !goal)
	{
		return;
	}

	start->color = ColorToInt(GREEN);

	Node* currentNode = start;
	std::deque<Node*> openList;
	Node* closedList;

	openList.push_front(start);
	
	while (!openList.empty())
	{
		for (int i = 0; i < openList.size(); i++)
		{
			openList[i]->edges[i]->getCost();
		}
	}
}


Node* Graph::getNode(int xPos, int yPos)
{
	if (xPos < 0 || xPos > m_width || yPos < 0 || yPos > m_height)
	{
		return nullptr;
	}
	
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
		{
			return m_nodes[i];
		}
	}

	return nullptr;
}

void Graph::addNodeToList(Node* node)
{

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
