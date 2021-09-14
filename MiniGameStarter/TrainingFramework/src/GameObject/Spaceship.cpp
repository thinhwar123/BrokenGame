#include "Spaceship.h"
#include <iostream>
#include "GameManager/ResourceManagers.h"
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
#include "Bullet.h"
#include "DataGlobe.h"
Spaceship::Spaceship()
{
	m_isShield = false;
	m_maxHitPoint = 10;
	m_currentHitPoint = 10;
	m_movementSpeed = 4;
	m_currentPosition = Vector2((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	Init();
}

Spaceship::~Spaceship()
{
}

void Spaceship::Init()
{
	m_collision = std::make_shared<Collision>(100, 100, m_currentPosition);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// spaceship
	auto texture = ResourceManagers::GetInstance()->GetTexture("m_spaceship_1.tga");
	m_spaceship = std::make_shared<Sprite2D>(model, shader, texture);
	m_spaceship->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_spaceship->SetSize(100, 100);


	//texture = ResourceManagers::GetInstance()->GetTexture("m_bullet_blaster_small.tga");
	//m_bullet = std::make_shared<Sprite2D>(model, shader, texture);
	//m_bullet->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	//m_bullet->SetSize(100, 100);
	// spaceship flame
	texture = ResourceManagers::GetInstance()->GetTexture("m_spaceship_flame.tga");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");

	m_flame_1 = std::make_shared<AnimationSprite>(model, shader, texture, 7, 0.1f);
	m_flame_1->SetSize(15, 51);

	m_flame_2 = std::make_shared<AnimationSprite>(model, shader, texture, 7, 0.1f);
	m_flame_2->SetSize(15, 51);

	m_flame_3 = std::make_shared<AnimationSprite>(model, shader, texture, 7, 0.1f);
	m_flame_3->SetSize(15, 51);

	texture = ResourceManagers::GetInstance()->GetTexture("m_shield.tga");
	m_shield = std::make_shared<AnimationSprite>(model, shader, texture, 6, 0.1f);
	m_shield->SetSize(150, 150);

	m_currentShootTime = 0;
	m_intervalShootTime = 0.45f;
}

void Spaceship::Draw()
{
	m_flame_1->Draw();
	m_flame_2->Draw();
	m_flame_3->Draw();
	m_spaceship->Draw();
	if (m_isShield)
	{
		m_shield->Draw();
	}

}

void Spaceship::Update(GLfloat deltatime)
{
	//std::cout << m_currentPosition.x << " " << m_currentPosition.y << std::endl;
	Move();
	m_flame_1->Update(deltatime);
	m_flame_2->Update(deltatime);
	m_flame_3->Update(deltatime);
	m_shield->Update(deltatime);
	if (m_currentShootTime > 0)
	{
		m_currentShootTime -= deltatime;
	}
	m_collision->SetPosition(m_currentPosition);
}

void Spaceship::Move()
{
	if (m_currentPosition.x < 75)
	{
		m_currentPosition.x = 75;
	}
	if (m_currentPosition.x > (float)Globals::screenWidth - 75)
	{
		m_currentPosition.x = (float)Globals::screenWidth - 75;
	}
	if (m_currentPosition.y < 75)
	{
		m_currentPosition.y = 75;
	}
	if (m_currentPosition.y > (float)Globals::screenHeight - 75)
	{
		m_currentPosition.y = (float)Globals::screenHeight - 75;
	}
	m_spaceship->Set2DPosition(m_currentPosition);
	m_flame_1->Set2DPosition(m_currentPosition + Vector2(0, 45));
	m_flame_2->Set2DPosition(m_currentPosition + Vector2(33, 50));
	m_flame_3->Set2DPosition(m_currentPosition + Vector2(-33, 50));
	m_shield->Set2DPosition(m_currentPosition + Vector2(0, 10));
}

void Spaceship::Shoot()
{
	if (m_currentShootTime <= 0)
	{
		m_currentShootTime += m_intervalShootTime - DataGlobal::GetInstance()->m_attackSpeed * 0.05;
		for (int i = 0; i < DataGlobal::GetInstance()->m_attackLevel; i++)
		{
			Vector2 shootPosition = m_currentPosition + Vector2(10 * ((DataGlobal::GetInstance()->m_attackLevel - 1) / 2.0f - i), 0);
			if (DataGlobal::GetInstance()->m_bullet_pool.empty())
			{
				auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
				auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");
				auto texture1 = ResourceManagers::GetInstance()->GetTexture("m_bullet_blaster_small.tga");
				auto tempBullet = std::make_shared<Bullet>(model1, shader1, texture1, shootPosition, Vector2(0, -1), 6, 16, 48);

				DataGlobal::GetInstance()->m_bullets.push_back(tempBullet);
			}
			else
			{
				auto tempBullet = DataGlobal::GetInstance()->m_bullet_pool.back();
				DataGlobal::GetInstance()->m_bullet_pool.pop_back();

				tempBullet->Spawn(shootPosition, Vector2(0, -1));
				DataGlobal::GetInstance()->m_bullets.push_back(tempBullet);
			}
		}
	}
}

void Spaceship::MoveLeft(GLfloat deltatime)
{
	m_currentPosition += Vector2(-1, 0) * m_movementSpeed * deltatime * 100;	
}

void Spaceship::MoveRight(GLfloat deltatime)
{
	m_currentPosition += Vector2(1, 0) * m_movementSpeed * deltatime * 100;
}

void Spaceship::MoveForward(GLfloat deltatime)
{
	m_currentPosition += Vector2(0, -1) * m_movementSpeed * deltatime * 100;
}

void Spaceship::MoveBackward(GLfloat deltatime)
{
	m_currentPosition += Vector2(0, 1) * m_movementSpeed * deltatime * 100;
}

void Spaceship::TakeDamge(int damage)
{
	if (m_currentHitPoint > 0)
	{
		if (m_isShield)
		{
			m_isShield = false;
		}
		else
		{
			m_currentHitPoint -= damage;
		}		
	}
}

