#include "Asteroid.h"
#include "DataGlobe.h"
Asteroid::Asteroid()
{
	Init();
}

Asteroid::Asteroid(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hitPoint, Vector2 startPosition, Vector2 direction, float speed, GLint with, GLint height)
{
	m_asteroid_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_position = startPosition;
	m_maxHitpoint = hitPoint;
	m_currentHitPoint = m_maxHitpoint * DataGlobal::GetInstance()->m_levelScale;
	m_asteroid_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
	m_asteroid_sprite->SetSize(with, height);
	m_speed = speed;
	m_collision = std::make_shared<Collision>(with, height, startPosition);
	Init();
}


Asteroid::~Asteroid()
{
}

void Asteroid::Init()
{
}

void Asteroid::Draw()
{
	m_asteroid_sprite->Draw();
}

void Asteroid::Update(GLfloat deltatime)
{
	m_position += m_direction * m_speed * deltatime * 100;
	m_asteroid_sprite->Set2DPosition(m_position);
	m_collision->SetPosition(m_position);
}

void Asteroid::Spawn(Vector2 startPosition, Vector2 direction)
{
	m_currentHitPoint = m_maxHitpoint * DataGlobal::GetInstance()->m_levelScale;
	m_position = startPosition;
	m_asteroid_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
}

void Asteroid::TakeDame(int damage)
{
	if (m_currentHitPoint > 0)
	{
		m_currentHitPoint -= damage;
	}
}
