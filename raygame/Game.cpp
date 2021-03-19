#include "Game.h"
#include "raylib.h"
#include "Player.h"
#include "Agent.h"
#include "SeekBehavior.h"
#include "FleeBehavior.h"
#include "WanderBehavior.h"
#include "PursuitBehavior.h"
#include "EvadeBehavior.h"
#include "ArriveBehavior.h"
#include "DecisionBehavior.h"
#include "PursuitDecision.h"
#include "ComplexEnemy.h"
#include "SimpleEnemy.h"
#include "Graph.h"

bool Game::m_gameOver = false;
Scene** Game::m_scenes = new Scene*;
int Game::m_sceneCount = 0;
int Game::m_currentSceneIndex = 0;
int Game::m_screenWidth = 1924;
int Game::m_screenHeight = 960;


Game::Game()
{
	m_gameOver = false;
	m_scenes = new Scene*;
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
}

void Game::start()
{
	InitWindow(m_screenWidth, m_screenHeight, "raylib [core] example - basic window");
	m_camera->offset = { (float)m_screenWidth / 2, (float)(m_screenHeight / 2) };
	m_camera->target = { (float)m_screenWidth / 2, (float)(m_screenHeight / 2) };
	m_camera->zoom = 1;

	//Initalize player and enemies
	Player* player = new Player(10, 10, 5, "Images/player.png", 10, 10);
	Agent* enemy = new Agent(5, 5, 1, "Images/enemy.png", 1, 1);
	SimpleEnemy* simpleEnemy = new SimpleEnemy(32, 10, 1, "Images/enemy.png", player);
	ComplexEnemy* complexEnemy = new ComplexEnemy(32, 15, 1, "Images/enemy.png", player, 1, 10);

	//STEERING BEHAVIORS BEGIN

	//Creates new steeriong behavior then add it to enemy
	SeekBehavior* seek = new SeekBehavior(player, 10);
	FleeBehavior* flee = new FleeBehavior(player, 1);
	WanderBehavior* wander = new WanderBehavior(0.1);
	PursuitBehavior* pursuit = new PursuitBehavior(player, 10);
	EvadeBehavior* evade = new EvadeBehavior(player, 0.1f);
	PursuitDecision* pursuitDecision = new PursuitDecision();
	DecisionBehavior* decisionBehavior = new DecisionBehavior(pursuitDecision);

	complexEnemy->addBehavior(decisionBehavior);

	simpleEnemy->addBehavior(seek);
	simpleEnemy->addBehavior(wander);

	//enemy->addBehavior(flee);
	//enemy->addBehavior(seek);
	//enemy->addBehavior(wander);
	//enemy->addBehavior(pursuit);
	enemy->addBehavior(evade);
	//enemy->addBehavior(arrive);

	//Adds player and enemy to scene while creating a new scene
	Scene* sceneBehavior = new Scene();
	sceneBehavior->addActor(player);
	//sceneBehavior->addActor(enemy);
	//sceneBehavior->addActor(simpleEnemy);
	sceneBehavior->addActor(complexEnemy);
	addScene(sceneBehavior);

	//STEERING BEHAVIORS END

	//PATHFINDING BEGIN

	Graph* graph = new Graph(30, 20, 10, 1);
	graph->setWorldPostion(MathLibrary::Vector2(10, 2));

	graph->BFS(0, 0, 13, 10);

	Scene* pathFinding = new Scene();
	pathFinding->addActor(graph);
	addScene(pathFinding);

	//PATHFINDING END

	SetTargetFPS(60);
}

void Game::update(float deltaTime)
{
	getCurrentScene()->update(deltaTime);
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(BLACK);

	getCurrentScene()->draw();

	EndMode2D();
	EndDrawing();
}

void Game::end()
{
	CloseWindow();
}

MathLibrary::Matrix3* Game::getWorld()
{
	return getCurrentScene()->getWorld();
}

void Game::run()
{
	start();

	while (!m_gameOver && !RAYLIB_H::WindowShouldClose())
	{
		float deltaTime = RAYLIB_H::GetFrameTime();
		update(deltaTime);
		draw();
	}

	end();
}

Scene* Game::getScene(int index)
{
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Game::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Game::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Game::addScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return -1;

	//Create a new temporary array that one size larger than the original
	Scene** tempArray = new Scene*[m_sceneCount + 1];

	//Copy values from old array into new array
	for (int i = 0; i < m_sceneCount; i++)
	{
		tempArray[i] = m_scenes[i];
	}

	//Store the current index
	int index = m_sceneCount;

	//Sets the scene at the new index to be the scene passed in
	tempArray[index] = scene;

	//Set the old array to the tmeporary array
	m_scenes = tempArray;
	m_sceneCount++;

	return index;
}

bool Game::removeScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return false;

	bool sceneRemoved = false;

	//Create a new temporary array that is one less than our original array
	Scene** tempArray = new Scene*[m_sceneCount - 1];

	//Copy all scenes except the scene we don't want into the new array
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
		{
			sceneRemoved = true;
		}
	}

	//If the scene was successfully removed set the old array to be the new array
	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}
		

	return sceneRemoved;
}

void Game::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_sceneCount)
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Game::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Game::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Game::destroy(Actor* actor)
{
	getCurrentScene()->removeActor(actor);
	if (actor->getParent())
		actor->getParent()->removeChild(actor);
	actor->end();
	delete actor;
}

void Game::setGameOver(bool value)
{
	Game::m_gameOver = value;
}
