#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "AnimationSprite.h"
#include "Text.h"
#include "GameButton.h"
#include "Application.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "DataGlobe.h"
#include "Explosion.h"
#include "MovingBackground.h"
#include "SoundEffect.h"


void DespawnBullet(int index);
void DespawnAsteroid(int index);
void DespawnEnemy(int index);
void DespawnEnemyBullet(int index);
void DespawnBoss(int index);
void DespawnBooster(int index);
void DespawnExplosion(int index);

GSPlay::GSPlay()
{
	
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	DataGlobal::GetInstance()->m_bullets.clear();
	DataGlobal::GetInstance()->m_asteroids.clear();
	DataGlobal::GetInstance()->m_enemys.clear();
	DataGlobal::GetInstance()->m_enemy_pool.clear();
	DataGlobal::GetInstance()->m_boss.clear();
	DataGlobal::GetInstance()->m_boss_pool.clear();
	DataGlobal::GetInstance()->m_enemy_bullets.clear();
	DataGlobal::GetInstance()->m_boosters.clear();
	DataGlobal::GetInstance()->m_explosions.clear();

	DataGlobal::GetInstance()->m_score = 0;
	DataGlobal::GetInstance()->m_enemyKill = 0;
	DataGlobal::GetInstance()->m_asteroidKill = 0;
	DataGlobal::GetInstance()->m_bossKill = 0;
	DataGlobal::GetInstance()->m_boosterUpgrage = 0;

	DataGlobal::GetInstance()->m_attackDame = 1;
	DataGlobal::GetInstance()->m_attackSpeed = 1;
	DataGlobal::GetInstance()->m_attackLevel = 1;
	DataGlobal::GetInstance()->m_levelScale = 1;
	m_scoreWaveCount = 0;
	m_keyPressed = 0;
	

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	auto texture = ResourceManagers::GetInstance()->GetTexture("m_gameplay_bg_0.tga");
	int width = 1332;
	int height = 999;
	auto bg = std::make_shared<MovingBackground>(texture, width, height, Vector2(width / 2.0f, height / 2.0f), 0);
	m_listBackground.push_back(bg);

	texture = ResourceManagers::GetInstance()->GetTexture("m_gameplay_bg_1.tga");
	width = 1332;
	height = 999;
	bg = std::make_shared<MovingBackground>(texture, width, height, Vector2(width / 2.0f, height / 2.0f), 0.5);
	m_listBackground.push_back(bg);

	texture = ResourceManagers::GetInstance()->GetTexture("m_gameplay_bg_1.tga");
	width = 1332;
	height = 999;
	bg = std::make_shared<MovingBackground>(texture, width, height, Vector2(width / 2.0f, -height / 2.0f), 0.5);
	m_listBackground.push_back(bg);

	texture = ResourceManagers::GetInstance()->GetTexture("m_gameplay_bg_2.tga");
	width = 450;
	height = 450;
	bg = std::make_shared<MovingBackground>(texture, width, height, Vector2(333, height / 2.0f), 0.1);
	m_listBackground.push_back(bg);

	texture = ResourceManagers::GetInstance()->GetTexture("m_gameplay_bg_3.tga");
	width = 500;
	height = 500;
	bg = std::make_shared<MovingBackground>(texture, width, height, Vector2(1000, -height / 2.0f), 0.1);
	m_listBackground.push_back(bg);

	texture = ResourceManagers::GetInstance()->GetTexture("m_gameplay_bg_4.tga");
	width = 1332;
	height = 999;
	bg = std::make_shared<MovingBackground>(texture, width, height, Vector2(width / 2.0f, height / 2.0f), 0);
	m_listBackground.push_back(bg);


	// spaceship
	m_spaceship = std::make_shared<Spaceship>();

	//// button 
	texture = ResourceManagers::GetInstance()->GetTexture("m_menu_button.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// UI
	texture = ResourceManagers::GetInstance()->GetTexture("m_HUI_bar.tga");
	std::shared_ptr<Sprite2D>  clone = std::make_shared<Sprite2D>(model, shader, texture);
	clone->Set2DPosition(422 / 2, 170 /2);
	clone->SetSize(422 , 170 );
	m_listUI.push_back(clone);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_4.tga");
	clone = std::make_shared<Sprite2D>(model, shader, texture);
	clone->Set2DPosition(160, 150);
	clone->SetSize(50, 50);
	m_listUI.push_back(clone);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_2.tga");
	clone = std::make_shared<Sprite2D>(model, shader, texture);
	clone->Set2DPosition(220, 150);
	clone->SetSize(50, 50);
	m_listUI.push_back(clone);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_5.tga");
	clone = std::make_shared<Sprite2D>(model, shader, texture);
	clone->Set2DPosition(280, 150);
	clone->SetSize(50, 50);
	m_listUI.push_back(clone);

	auto se = std::make_shared<SoundEffect>();
	se->Play(1);

	// Declare some variables
	//SoLoud::Soloud soloud; // Engine core
	//SoLoud::Wav sample;    // One sample

	//soloud.init();

	//sample.load("sss.wav"); 
	//sample.setVolume(1);
	//soloud.play(sample);





	m_currentSpawnAsteroidTime = 0;
	m_intervalSpawnAsteroidTime = 0.25f;

	m_currentSpawnEnemyTime = 0;
	m_intervalSpawnEnemyTime = 2;
	m_lastSpawnEnemyPositionX = 0;


}

void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 'A':
			m_keyPressed |= KEY_MOVE_LEFT;
			break;
		case 'D':
			m_keyPressed |= KEY_MOVE_RIGHT;
			break;
		case 'S':
			m_keyPressed |= KEY_MOVE_BACKWORD;
			break;
		case 'W':
			m_keyPressed |= KEY_MOVE_FORWORD;
			break;
		case 'J':
			m_keyPressed |= KEY_SHOOT;
			break;
		default:
			break;
		}
	}
	else {
		switch (key)
		{
		case 'A':
			m_keyPressed ^= KEY_MOVE_LEFT;
			break;
		case 'D':
			m_keyPressed ^= KEY_MOVE_RIGHT;
			break;
		case 'S':
			m_keyPressed ^= KEY_MOVE_BACKWORD;
			break;
		case 'W':
			m_keyPressed ^= KEY_MOVE_FORWORD;
			break;
		case 'J':
			m_keyPressed ^= KEY_SHOOT;
			break;
		default:
			break;
		}
	}

}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	// Player Input
	{
		if (m_keyPressed & KEY_MOVE_LEFT)
		{
			m_spaceship->MoveLeft(deltaTime);
		}
		if (m_keyPressed & KEY_MOVE_RIGHT)
		{
			m_spaceship->MoveRight(deltaTime);
		}
		if (m_keyPressed & KEY_MOVE_BACKWORD)
		{
			m_spaceship->MoveBackward(deltaTime);
		}
		if (m_keyPressed & KEY_MOVE_FORWORD)
		{
			m_spaceship->MoveForward(deltaTime);
		}
		if (m_keyPressed & KEY_SHOOT)
		{
			m_spaceship->Shoot();
		}
	}
	
	// Update Object 
	{
		
		//m_test->Update(deltaTime);
		for (auto bg : m_listBackground)
		{
			bg->Update(deltaTime);
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_bullets.size(); i++)
		{
			auto bullet = DataGlobal::GetInstance()->m_bullets[i];
			bullet->Update(deltaTime);
			if (bullet->m_position.y < -100)
			{
				DespawnBullet(i);
			}
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_enemy_bullets.size(); i++)
		{
			auto bullet = DataGlobal::GetInstance()->m_enemy_bullets[i];
			bullet->Update(deltaTime);
			if (bullet->m_position.y > Globals::screenHeight + 100 || bullet->m_position.y < - 100)
			{
				DespawnEnemyBullet(i);
			}
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_asteroids.size(); i++)
		{
			auto asteroid = DataGlobal::GetInstance()->m_asteroids[i];
			asteroid->Update(deltaTime);
			if (asteroid->m_position.y > Globals::screenHeight + 100)
			{
				DespawnAsteroid(i);
			}
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_boosters.size(); i++)
		{
			auto booster = DataGlobal::GetInstance()->m_boosters[i];
			booster->Update(deltaTime);
			if (booster->m_position.y > Globals::screenHeight + 100)
			{
				DespawnBooster(i);
			}
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_enemys.size(); i++)
		{
			auto enemy = DataGlobal::GetInstance()->m_enemys[i];
			enemy->Update(deltaTime);
			if (enemy->m_position.y > Globals::screenHeight - 100)
			{
				DespawnEnemy(i);
			}
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_boss.size(); i++)
		{
			auto boss = DataGlobal::GetInstance()->m_boss[i];
			boss->Update(deltaTime);
		}
		for (int i = 0; i < DataGlobal::GetInstance()->m_explosions.size(); i++)
		{
			auto explosion = DataGlobal::GetInstance()->m_explosions[i];
			explosion->Update(deltaTime);
			if (explosion->m_isFinish)
			{
				DespawnExplosion(i);
			}
		}
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		m_spaceship->Update(deltaTime);
		if (m_spaceship->m_currentHitPoint <= 0)
		{
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_ENDGAME);
		}

		auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("neuropol.ttf");
		char buf[100];
		snprintf(buf, 100, "%d", DataGlobal::GetInstance()->m_score);
		m_score = std::make_shared<Text>(shader, font, buf, TextColor::WHITE, 2.0);
		m_score->Set2DPosition(Vector2(175, 90));

		snprintf(buf, 100, "%d", DataGlobal::GetInstance()->m_attackDame);
		m_attackDamage = std::make_shared<Text>(shader, font, buf, TextColor::YELLOW, 1.0);
		m_attackDamage->Set2DPosition(Vector2(180, 155));

		snprintf(buf, 100, "%d", DataGlobal::GetInstance()->m_attackSpeed);
		m_attackSpeed = std::make_shared<Text>(shader, font, buf, TextColor::YELLOW, 1.0);
		m_attackSpeed->Set2DPosition(Vector2(240, 155));

		snprintf(buf, 100, "%d", DataGlobal::GetInstance()->m_attackLevel);
		m_attackLevel = std::make_shared<Text>(shader, font, buf, TextColor::YELLOW, 1.0);
		m_attackLevel->Set2DPosition(Vector2(300, 155));

		snprintf(buf, 100, "%d%c", m_spaceship->m_currentHitPoint * 100 / m_spaceship->m_maxHitPoint, '%');
		m_hitpoint = std::make_shared<Text>(shader, font, buf, TextColor::WHITE, 1.0);
		m_hitpoint->Set2DPosition(Vector2(50, 90));
	}

	//Spawn Object
	{
		int waveScore = (DataGlobal::GetInstance()->m_score - m_scoreWaveCount);
		if (waveScore < 20 * DataGlobal::GetInstance()->m_levelScale)
		{
			SpawnEnemy(deltaTime);
			
		}
		else if (waveScore < 40 * DataGlobal::GetInstance()->m_levelScale)
		{
			SpawnAsteroid(deltaTime);
		}
		else if (DataGlobal::GetInstance()->m_enemys.empty() && DataGlobal::GetInstance()->m_asteroids.empty() && DataGlobal::GetInstance()->m_boss.empty())
		{
			SpawnBoss();
		}
	
	}

	//Check Collision
	{
		for (int i = 0; i < DataGlobal::GetInstance()->m_bullets.size(); i++)
		{
			for (int j = 0; j < DataGlobal::GetInstance()->m_asteroids.size(); j++)
			{
				if (Collision::AABB(DataGlobal::GetInstance()->m_bullets[i]->m_collision, DataGlobal::GetInstance()->m_asteroids[j]->m_collision))
				{
					SpawnExplosion(DataGlobal::GetInstance()->m_bullets[i]->m_position, 0, 50);
					DespawnBullet(i);
					i--;

					DataGlobal::GetInstance()->m_asteroids[j]->TakeDame(DataGlobal::GetInstance()->m_attackDame);
					if (DataGlobal::GetInstance()->m_asteroids[j]->m_currentHitPoint <= 0)
					{
						DataGlobal::GetInstance()->m_asteroidKill++;
						SpawnExplosion(DataGlobal::GetInstance()->m_asteroids[j]->m_position, 1, DataGlobal::GetInstance()->m_asteroids[j]->m_collision->m_height);
						SpawnBooster(DataGlobal::GetInstance()->m_asteroids[j]->m_position, 0.5f);
						DespawnAsteroid(j);
						DataGlobal::GetInstance()->m_score += 1 * DataGlobal::GetInstance()->m_levelScale;
					}
					break;
				}
			}

		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_bullets.size(); i++)
		{
			for (int j = 0; j < DataGlobal::GetInstance()->m_enemys.size(); j++)
			{
				if (Collision::AABB(DataGlobal::GetInstance()->m_bullets[i]->m_collision, DataGlobal::GetInstance()->m_enemys[j]->m_collision))
				{
					SpawnExplosion(DataGlobal::GetInstance()->m_bullets[i]->m_position, 0, 50);
					DespawnBullet(i);
					i--;

					DataGlobal::GetInstance()->m_enemys[j]->TakeDame(DataGlobal::GetInstance()->m_attackDame);
					if (DataGlobal::GetInstance()->m_enemys[j]->m_currentHitPoint <= 0)
					{
						DataGlobal::GetInstance()->m_enemyKill++;
						SpawnExplosion(DataGlobal::GetInstance()->m_enemys[j]->m_position, 1, 100);
						SpawnBooster(DataGlobal::GetInstance()->m_enemys[j]->m_position, 0.5f);
						DespawnEnemy(j);
						DataGlobal::GetInstance()->m_score += 1 * DataGlobal::GetInstance()->m_levelScale;
					}
					break;
				}
			}

		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_bullets.size(); i++)
		{
			for (int j = 0; j < DataGlobal::GetInstance()->m_boss.size(); j++)
			{
				if (Collision::AABB(DataGlobal::GetInstance()->m_bullets[i]->m_collision, DataGlobal::GetInstance()->m_boss[j]->m_collision))
				{
					SpawnExplosion(DataGlobal::GetInstance()->m_bullets[i]->m_position, 0, 50);
					DespawnBullet(i);
					i--;


					DataGlobal::GetInstance()->m_boss[j]->TakeDame(DataGlobal::GetInstance()->m_attackDame);
					if (DataGlobal::GetInstance()->m_boss[j]->m_currentHitPoint <= 0)
					{
						DataGlobal::GetInstance()->m_bossKill++;
						SpawnExplosion(DataGlobal::GetInstance()->m_boss[j]->m_position, 1, 200);
						SpawnBooster(DataGlobal::GetInstance()->m_boss[j]->m_position, 1.0f);
						DespawnBoss(j);
						DataGlobal::GetInstance()->m_score += 10 * DataGlobal::GetInstance()->m_levelScale;
						DataGlobal::GetInstance()->m_levelScale += 2 ;
						m_scoreWaveCount = DataGlobal::GetInstance()->m_score;
					}
					break;
				}
			}

		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_asteroids.size(); i++)
		{
			if (Collision::AABB(m_spaceship->m_collision, DataGlobal::GetInstance()->m_asteroids[i]->m_collision))
			{
				m_spaceship->TakeDamge(2);
				DespawnAsteroid(i);
				break;
			}
		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_enemys.size(); i++)
		{
			if (Collision::AABB(m_spaceship->m_collision, DataGlobal::GetInstance()->m_enemys[i]->m_collision))
			{
				m_spaceship->TakeDamge(1);
				DespawnEnemy(i);
				break;
			}
		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_boss.size(); i++)
		{
			if (Collision::AABB(m_spaceship->m_collision, DataGlobal::GetInstance()->m_boss[i]->m_collision))
			{
				m_spaceship->TakeDamge(100);
				DespawnBoss(i);
				break;
			}
		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_enemy_bullets.size(); i++)
		{
			if (Collision::AABB(m_spaceship->m_collision, DataGlobal::GetInstance()->m_enemy_bullets[i]->m_collision))
			{
				m_spaceship->TakeDamge(1);
				DespawnEnemyBullet(i);
				break;
			}
		}

		for (int i = 0; i < DataGlobal::GetInstance()->m_boosters.size(); i++)
		{
			if (Collision::AABB(m_spaceship->m_collision, DataGlobal::GetInstance()->m_boosters[i]->m_collision))
			{
				DataGlobal::GetInstance()->m_boosterUpgrage++;
				switch (DataGlobal::GetInstance()->m_boosters[i]->m_type)
				{
				case 0:
					m_spaceship->m_currentHitPoint++;
					if (m_spaceship->m_currentHitPoint > m_spaceship->m_maxHitPoint)
					{
						m_spaceship->m_currentHitPoint = m_spaceship->m_maxHitPoint;
					}
					break;
				case 1:
					m_spaceship->m_isShield = true;
					break;
				case 2:
					DataGlobal::GetInstance()->m_attackSpeed++;
					if (DataGlobal::GetInstance()->m_attackSpeed > 5)
					{
						DataGlobal::GetInstance()->m_attackSpeed = 5;
					}
					break;
				case 3:
					DataGlobal::GetInstance()->m_score += 2* DataGlobal::GetInstance()->m_levelScale;
					break;
				case 4:
					DataGlobal::GetInstance()->m_attackDame++;
					if (DataGlobal::GetInstance()->m_attackDame > 5)
					{
						DataGlobal::GetInstance()->m_attackDame = 5;
					}
					break;
				case 5:
					DataGlobal::GetInstance()->m_attackLevel++;
					if (DataGlobal::GetInstance()->m_attackLevel > 5)
					{
						DataGlobal::GetInstance()->m_attackLevel = 5;
					}
					break;
				}
				DespawnBooster(i);
				break;
			}
		}
	}

}

void GSPlay::Draw()
{
	//m_background->Draw();
	for (auto bg : m_listBackground)
	{
		bg->Draw();
	}
	for (auto bullet : DataGlobal::GetInstance()->m_enemy_bullets)
	{
		bullet->Draw();
	}
	for (auto bullet : DataGlobal::GetInstance()->m_bullets)
	{
		bullet->Draw();
	}
	for (auto asteroid : DataGlobal::GetInstance()->m_asteroids)
	{
		asteroid->Draw();
	}
	for (auto enemy : DataGlobal::GetInstance()->m_enemys)
	{
		enemy->Draw();
	}
	for (auto boss : DataGlobal::GetInstance()->m_boss)
	{
		boss->Draw();
	}
	for (auto booster : DataGlobal::GetInstance()->m_boosters)
	{
		booster->Draw();
	}
	for (auto it : DataGlobal::GetInstance()->m_explosions)
	{
		it->Draw();
	}
	for (auto it : m_listUI)
	{
		it->Draw();
	}
	m_spaceship->Draw();

	m_score->Draw();
	m_attackDamage->Draw();
	m_attackSpeed->Draw();
	m_attackLevel->Draw();
	m_hitpoint->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_test->Draw();
}

void GSPlay::SpawnAsteroid(float deltaTime)
{
	if (m_currentSpawnAsteroidTime <= 0)
	{
		float randomPositionX = std::rand() % (int)(Globals::screenWidth * 1.5f);
		int randomTexture = std::rand() % 10;
		float randomSpeed = std::rand() % 200 / 100.0f + 0.5f;
		m_currentSpawnAsteroidTime += m_intervalSpawnAsteroidTime;
		if (DataGlobal::GetInstance()->m_asteroid_pool.empty())
		{
			auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");
			int scale = 4;
			std::shared_ptr<Asteroid> tempAsteroid;
			std::shared_ptr<Texture> texture1;
			switch (randomTexture)
			{
			case 0:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_00.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 2, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 11 * scale, 11 * scale);
				break;
			case 1:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_01.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 6, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 60 * scale, 50 * scale);
				break;
			case 2:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_02.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 5, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 52 * scale, 43 * scale);
				break;
			case 3:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_03.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 5, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 50 * scale, 36 * scale);
				break;
			case 4:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_04.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 4, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 35 * scale, 30 * scale);
				break;
			case 5:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_05.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 5, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 45 * scale, 20 * scale);
				break;
			case 6:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_06.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 4, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 32 * scale, 24 * scale);
				break;
			case 7:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_07.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 4, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 30 * scale, 25 * scale);
				break;
			case 8:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_08.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 3, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 24 * scale, 24 * scale);
				break;
			case 9:
				texture1 = ResourceManagers::GetInstance()->GetTexture("m_asteroid_09.tga");
				tempAsteroid = std::make_shared<Asteroid>(model1, shader1, texture1, 2, Vector2(randomPositionX, -100), Vector2(-1, 1), randomSpeed, 17 * scale, 18 * scale);
				break;
			default:
				break;
			}

			DataGlobal::GetInstance()->m_asteroids.push_back(tempAsteroid);
		}
		else
		{
			auto tempAsteroid = DataGlobal::GetInstance()->m_asteroid_pool.back();
			DataGlobal::GetInstance()->m_asteroid_pool.pop_back();

			tempAsteroid->Spawn(Vector2(randomPositionX, -100), Vector2(-1, 1));
			DataGlobal::GetInstance()->m_asteroids.push_back(tempAsteroid);
		}
	}
	m_currentSpawnAsteroidTime -= deltaTime;
}

void GSPlay::SpawnEnemy(float deltaTime)
{

	if (m_currentSpawnEnemyTime <= 0)
	{		

		float randomPositionX = std::rand() % (int)(Globals::screenWidth);
		while (std::abs(randomPositionX - m_lastSpawnEnemyPositionX) < 200) {
			float randomPositionX = std::rand() % (int)(Globals::screenWidth);
			m_lastSpawnEnemyPositionX = randomPositionX;
		}
		//int randomTexture = std::rand() % 10;
		float randomSpeed = std::rand() % 100 / 100.0f + 0.5f;
		m_currentSpawnEnemyTime += m_intervalSpawnEnemyTime;
		if (DataGlobal::GetInstance()->m_enemy_pool.empty())
		{
			auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");
			
			auto texture1 = ResourceManagers::GetInstance()->GetTexture("m_enemy_unit_01.tga");
			auto tempEnemy = std::make_shared<Enemy>(model1, shader1, texture1, 3 , m_spaceship, Vector2(randomPositionX, -100), Vector2(0, 1), randomSpeed, 116, 116);

			DataGlobal::GetInstance()->m_enemys.push_back(tempEnemy);
		}
		else
		{
			auto tempEnemy = DataGlobal::GetInstance()->m_enemy_pool.back();
			DataGlobal::GetInstance()->m_enemy_pool.pop_back();

			tempEnemy->Spawn(Vector2(randomPositionX, -100), Vector2(0, 1));
			DataGlobal::GetInstance()->m_enemys.push_back(tempEnemy);
		}
	}
	m_currentSpawnEnemyTime -= deltaTime;
}

void GSPlay::SpawnBoss()
{
	if (DataGlobal::GetInstance()->m_boss_pool.empty())
	{
		auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");

		auto texture1 = ResourceManagers::GetInstance()->GetTexture("m_boss_unit.tga");
		auto tempEnemy = std::make_shared<Boss>(model1, shader1, texture1, 30, m_spaceship, Vector2((float)Globals::screenWidth / 2, -200), Vector2(0, 1), 2, 350, 350);

		DataGlobal::GetInstance()->m_boss.push_back(tempEnemy);
	}
	else
	{
		auto tempEnemy = DataGlobal::GetInstance()->m_boss_pool.back();
		DataGlobal::GetInstance()->m_boss_pool.pop_back();

		tempEnemy->Spawn(Vector2((float)Globals::screenWidth / 2, -200), Vector2(0, 1));
		DataGlobal::GetInstance()->m_boss.push_back(tempEnemy);
	}
}

void GSPlay::SpawnBooster(Vector2 position, float rate)
{
	float random = std::rand() % 10 / 10.0f;
	if (random < rate)
	{
		if (DataGlobal::GetInstance()->m_booster_pool.empty())
		{
			auto tempBooster = std::make_shared<Booster>(position, Vector2(0, 1), 1);
			DataGlobal::GetInstance()->m_boosters.push_back(tempBooster);
		}
		else
		{
			auto tempEnemy = DataGlobal::GetInstance()->m_booster_pool.back();
			DataGlobal::GetInstance()->m_booster_pool.pop_back();

			tempEnemy->Spawn(position, Vector2(0, 1));
			DataGlobal::GetInstance()->m_boosters.push_back(tempEnemy);
		}
	}
}

void GSPlay::SpawnExplosion(Vector2 position, int type, int size)
{	
	auto model = ResourceManagers::GetInstance()->GetModel("AnimationSprite.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("m_shield.tga");
	if (DataGlobal::GetInstance()->m_explosion_pool.empty())
	{
		
		auto tempExplosion = std::make_shared<Explosion>(position, type, size);
		DataGlobal::GetInstance()->m_explosions.push_back(tempExplosion);
	}
	else
	{
		auto tempExplosion = DataGlobal::GetInstance()->m_explosion_pool.back();
		DataGlobal::GetInstance()->m_explosion_pool.pop_back();

		tempExplosion->Spawn(position, type, size);
		DataGlobal::GetInstance()->m_explosions.push_back(tempExplosion);
	}
	std::cout << DataGlobal::GetInstance()->m_explosions.size();
}

void DespawnBullet(int index) {
	auto bullet = DataGlobal::GetInstance()->m_bullets[index];
	DataGlobal::GetInstance()->m_bullets.erase(DataGlobal::GetInstance()->m_bullets.begin() + index);
	DataGlobal::GetInstance()->m_bullet_pool.push_back(bullet);

}

void DespawnAsteroid(int index) {
	auto asteroid = DataGlobal::GetInstance()->m_asteroids[index];
	DataGlobal::GetInstance()->m_asteroids.erase(DataGlobal::GetInstance()->m_asteroids.begin() + index);
	DataGlobal::GetInstance()->m_asteroid_pool.push_back(asteroid);
}

void DespawnEnemy(int index) {
	auto enemy = DataGlobal::GetInstance()->m_enemys[index];
	DataGlobal::GetInstance()->m_enemys.erase(DataGlobal::GetInstance()->m_enemys.begin() + index);
	DataGlobal::GetInstance()->m_enemy_pool.push_back(enemy);
}

void DespawnEnemyBullet(int index) {

	auto enemyBullet = DataGlobal::GetInstance()->m_enemy_bullets[index];
	DataGlobal::GetInstance()->m_enemy_bullets.erase(DataGlobal::GetInstance()->m_enemy_bullets.begin() + index);
	DataGlobal::GetInstance()->m_enemy_bullet_pool.push_back(enemyBullet);
}

void DespawnBoss(int index) {

	auto boss = DataGlobal::GetInstance()->m_boss[index];
	DataGlobal::GetInstance()->m_boss.erase(DataGlobal::GetInstance()->m_boss.begin() + index);
	DataGlobal::GetInstance()->m_boss_pool.push_back(boss);
}

void DespawnBooster(int index) {
	auto booster = DataGlobal::GetInstance()->m_boosters[index];
	DataGlobal::GetInstance()->m_boosters.erase(DataGlobal::GetInstance()->m_boosters.begin() + index);
	DataGlobal::GetInstance()->m_booster_pool.push_back(booster);
}

void DespawnExplosion(int index) {
	auto explosion = DataGlobal::GetInstance()->m_explosions[index];
	DataGlobal::GetInstance()->m_explosions.erase(DataGlobal::GetInstance()->m_explosions.begin() + index);
	DataGlobal::GetInstance()->m_explosion_pool.push_back(explosion);
}
