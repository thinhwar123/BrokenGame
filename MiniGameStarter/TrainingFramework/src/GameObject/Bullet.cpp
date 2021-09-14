#include "Bullet.h"
#include "CMath.h"
#include "DataGlobe.h"
Bullet::Bullet()
{
	Init();
}

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Vector2 startPosition, Vector2 direction, float speed, GLint with, GLint height)
{
	
	m_bullet_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_position = startPosition;
	m_bullet_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
	m_bullet_sprite->SetSize(with, height);
	m_speed = speed;
	m_collision = std::make_shared<Collision>(with, height, startPosition);
	Init();
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Draw()
{
	m_bullet_sprite->Draw();
}

void Bullet::Update(GLfloat deltatime)
{
	m_position += m_direction * m_speed * deltatime * 100.0f;
	m_bullet_sprite->Set2DPosition(m_position);
	m_collision->SetPosition(m_position);
}

void Bullet::Spawn(Vector2 startPosition, Vector2 direction)
{
	m_position = startPosition;
	m_collision->SetPosition(m_position);
	m_bullet_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
}
