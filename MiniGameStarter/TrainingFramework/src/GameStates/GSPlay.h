#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class AnimationSprite;
class Explosion;
class Spaceship;
class MovingBackground;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	void	SpawnAsteroid(float deltaTime);
	void	SpawnEnemy(float deltaTime);
	void	SpawnBoss();
	void	SpawnBooster(Vector2 position, float rate);
	void	SpawnExplosion(Vector2 position, int type, int size);

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		m_hitpoint;
	std::shared_ptr<Text>		m_attackSpeed;
	std::shared_ptr<Text>		m_attackDamage;
	std::shared_ptr<Text>		m_attackLevel;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Sprite2D>>	m_listUI;
	std::list<std::shared_ptr<MovingBackground>>	m_listBackground;

	std::shared_ptr<Spaceship> m_spaceship;

	float m_currentSpawnAsteroidTime;
	float m_intervalSpawnAsteroidTime;

	float m_currentSpawnEnemyTime;
	float m_intervalSpawnEnemyTime;
	int m_lastSpawnEnemyPositionX;
	int m_scoreWaveCount;

	//std::shared_ptr<Explosion>		m_test;
};

