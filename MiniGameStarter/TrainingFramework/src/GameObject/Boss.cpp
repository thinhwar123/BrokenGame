#include "Boss.h"
#include "DataGlobe.h"
#include "GameManager/ResourceManagers.h"
#include "Application.h"
#include "Spaceship.h"
Boss::Boss()
{
	Init();
}

Boss::Boss(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hitPoint, std::shared_ptr<Spaceship> spaceship, Vector2 startPosition, Vector2 direction, float speed, GLint with, GLint height)
{
	m_spaceship = spaceship;
	m_enemy_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_position = startPosition;
	m_maxHitpoint = hitPoint;
	m_currentHitPoint = m_maxHitpoint * DataGlobal::GetInstance()->m_levelScale;
	m_enemy_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
	m_enemy_sprite->SetSize(with, height);
	m_speed = speed;
	m_collision = std::make_shared<Collision>(with - 50, height - 100, startPosition);
	Init();
}

Boss::~Boss()
{
}

void Boss::Init()
{
	m_currentShootTime = std::rand() % 200 / 100.0f + 0.5f;
	m_intervalShootTime = 1.0f;
}

void Boss::Draw()
{
	m_enemy_sprite->Draw();
}

void Boss::Update(GLfloat deltatime)
{
	if (m_position.y < 200)
	{
		m_position += m_direction * m_speed * deltatime * 100;
		m_enemy_sprite->Set2DPosition(m_position);
		m_collision->SetPosition(m_position);
	}
	else 
	{
		if (m_direction.y == 1)
		{
			m_direction = Vector2(1, 0);
		}
		
		if (m_position.x < 100)
		{
			m_direction = Vector2(1, 0);
		}
		else if (m_position.x > Globals::screenWidth - 100)
		{
			m_direction = Vector2(-1, 0);
		}
		m_position += m_direction * m_speed * deltatime * 100;
		m_enemy_sprite->Set2DPosition(m_position);
		m_collision->SetPosition(m_position);
	}
	Shoot();
	m_currentShootTime -= deltatime;
}

void Boss::Spawn(Vector2 startPosition, Vector2 direction)
{
	m_currentHitPoint = m_maxHitpoint * DataGlobal::GetInstance()->m_levelScale;
	m_position = startPosition;
	m_enemy_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
}

void Boss::TakeDame(int damage)
{
	if (m_currentHitPoint > 0)
	{
		m_currentHitPoint -= damage;
	}
}

void Boss::Shoot()
{
	if (m_currentShootTime <= 0)
	{
		m_currentShootTime += m_intervalShootTime;
		for (int i = 0; i < 3; i++)
		{
			Vector2 shootPosition = m_position + Vector2((i - 1) * 80, 0);
			if (DataGlobal::GetInstance()->m_enemy_bullet_pool.empty())
			{
				auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
				auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");
				auto texture1 = ResourceManagers::GetInstance()->GetTexture("m_single_cluster.tga");
				auto tempBullet = std::make_shared<Bullet>(model1, shader1, texture1, shootPosition, m_spaceship->m_currentPosition - m_position, 4, 12, 12);

				DataGlobal::GetInstance()->m_enemy_bullets.push_back(tempBullet);
			}
			else
			{
				auto tempBullet = DataGlobal::GetInstance()->m_enemy_bullet_pool.back();
				DataGlobal::GetInstance()->m_enemy_bullet_pool.pop_back();

				tempBullet->Spawn(shootPosition, m_spaceship->m_currentPosition - m_position);
				DataGlobal::GetInstance()->m_enemy_bullets.push_back(tempBullet);
			}
		}

	}
}