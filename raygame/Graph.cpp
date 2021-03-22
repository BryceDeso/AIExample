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

			//If the node at the opposite end hasnt been mark as visited then add to queue
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
	//Create a node pointer that points to the start node
	//Create a node pointer that points to the goal node
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	if (!start || !goal)
	{
		//return an empty list
		return;
	}
	//end if statement

	//Set the start nodes color to be green
	start->color = ColorToInt(BLUE);

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = start;
	//Create an open list
	std::deque<Node*> openList;
	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the g score
		for (int i = 0; i < openList.size(); i++)
		{
			for (int j = openList.size() - 1; j > i; j--)
			{
				if (openList[j] < openList[j - 1])
				{
					Node* temp = openList[j];
					openList[j] = openList[j - 1];
					openList[j - 1] = temp;
				}
			}
		}

		//Set the iterator to be the first item in the open list
		currentNode = openList.front();

		//Check if the iterator is pointing to the goal node
		if (currentNode == goal)
		{
			//Mark the goal as being found by changing its color
			goal->color = ColorToInt(GREEN);
			//Return the new path found
			return;
		}
		//end if statement

		//Pop the first item off the open list
		openList.pop_front();
		//Add the first item to the closed list
		closedList.push_front(currentNode);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = nullptr;

			//Check if the iterator is on the second end of the node
			if (currentNode == currentNode->edges[i]->connectedNode2)
			{
				//Set the edge end pointer to be the first end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			}
			//Otherwise if the iterator is on the first end of the node...
			else
			{
				//set the edge end pointer to be the second end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;
			}
			// end if statement
			
			//Check if node at the end of the edge is in the closed list
			if (currentEdgeEnd == currentNode)
			{
				//Create an float and set it to be the g score of the iterator plus the cost of the edge
				float gScore = currentNode->edges[i]->getCost() + currentEdgeEnd->edges[i]->getCost();

				//Check if the node at the end of the edge is in the open list
				if (currentEdgeEnd)
				{
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);

					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->edges[i]->setCost(gScore);

					//Set the nodes previous to be the iterator
					currentEdgeEnd->setPrevious(currentNode);

					//Add the node to the open list
					openList.push_front(currentEdgeEnd);
				}
				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else if(gScore < currentEdgeEnd->edges[i]->getCost())
				{
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);
					//Set its g score to be the g score calculated earlier
					currentEdgeEnd->edges[i]->setCost(gScore);
					//Set its previous to be the current node
					currentEdgeEnd->setPrevious(currentNode);
				}
				//end if statement
			}
		}
		//end loop
	}

	//end loop
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

//void Graph::sort(Node* list)
//{
//	for (int i = 0; i < m_nodes.size(); i++)
//	{
//		for (int j = m_nodes.size() - 1; j > i; j--)
//		{
//			if ()
//			{
//				Node temp = list[j];
//				list[j] = list[j - 1];
//				list[j - 1] = temp;
//			}
//		}
//	}
//}

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
