#include "Enemy.h"
#include "DataGlobe.h"
#include "GameManager/ResourceManagers.h"
#include "Application.h"
#include "Spaceship.h"

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hitPoint, std::shared_ptr<Spaceship> spaceship, Vector2 startPosition, Vector2 direction, float speed, GLint with, GLint height)
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
	m_collision = std::make_shared<Collision>(with, height, startPosition);
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_currentShootTime = std::rand() % 200 / 100.0f + 0.5f;
	m_intervalShootTime = 3;
}

void Enemy::Draw()
{
	m_enemy_sprite->Draw();
}

void Enemy::Update(GLfloat deltatime)
{
	m_position += m_direction * m_speed * deltatime * 100;
	m_enemy_sprite->Set2DPosition(m_position);
	m_collision->SetPosition(m_position);

	Shoot();
	m_currentShootTime -= deltatime;
}

void Enemy::Spawn(Vector2 startPosition, Vector2 direction)
{
	m_currentHitPoint = m_maxHitpoint * DataGlobal::GetInstance()->m_levelScale;
	m_position = startPosition;
	m_enemy_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
}

void Enemy::TakeDame(int damage)
{
	if (m_currentHitPoint > 0)
	{
		m_currentHitPoint -= damage;
	}
}

void Enemy::Shoot()
{
	if (m_currentShootTime <= 0 )
	{		
		m_currentShootTime += m_intervalShootTime - DataGlobal::GetInstance()->m_levelScale * 0.3;
		if (m_currentShootTime < 1)
		{
			m_currentShootTime = 1;
		}
		if (DataGlobal::GetInstance()->m_enemy_bullet_pool.empty())
		{
			auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto texture1 = ResourceManagers::GetInstance()->GetTexture("m_single_cluster.tga");
			auto tempBullet = std::make_shared<Bullet>(model1, shader1, texture1, m_position, m_spaceship->m_currentPosition - m_position, 4, 12, 12);

			DataGlobal::GetInstance()->m_enemy_bullets.push_back(tempBullet);
		}
		else
		{
			auto tempBullet = DataGlobal::GetInstance()->m_enemy_bullet_pool.back();
			DataGlobal::GetInstance()->m_enemy_bullet_pool.pop_back();

			tempBullet->Spawn(m_position, m_spaceship->m_currentPosition - m_position);
			DataGlobal::GetInstance()->m_enemy_bullets.push_back(tempBullet);
		}
	}
}

