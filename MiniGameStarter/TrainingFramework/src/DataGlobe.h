#pragma once
#include "Singleton.h"
#include "utilities.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Boss.h"
#include "Booster.h"
#include "Explosion.h"

class DataGlobal : public CSingleton<DataGlobal>
{
public:
	DataGlobal();
	~DataGlobal();
	int m_score;
	int m_attackDame;
	int m_attackSpeed;
	int m_attackLevel;
	int m_highscore;

	int m_levelScale;
	int m_enemyKill;
	int m_asteroidKill;
	int m_bossKill;
	int m_boosterUpgrage;
	std::list<std::shared_ptr<Bullet>> m_bullet_pool;
	std::vector<std::shared_ptr<Bullet>> m_bullets;

	std::list<std::shared_ptr<Asteroid>> m_asteroid_pool;
	std::vector<std::shared_ptr<Asteroid>> m_asteroids;

	std::list<std::shared_ptr<Enemy>> m_enemy_pool;
	std::vector<std::shared_ptr<Enemy>> m_enemys;

	std::list<std::shared_ptr<Boss>> m_boss_pool;
	std::vector<std::shared_ptr<Boss>> m_boss;

	std::list<std::shared_ptr<Bullet>> m_enemy_bullet_pool;
	std::vector<std::shared_ptr<Bullet>> m_enemy_bullets;

	std::list<std::shared_ptr<Booster>> m_booster_pool;
	std::vector<std::shared_ptr<Booster>> m_boosters;

	std::list<std::shared_ptr<Explosion>> m_explosion_pool;
	std::vector<std::shared_ptr<Explosion>> m_explosions;

	void LoadScore();
	void SaveScore(int score);
};

