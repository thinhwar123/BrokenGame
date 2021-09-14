#include "Booster.h"
#include "CMath.h"
#include "DataGlobe.h"
#include "ResourceManagers.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
Booster::Booster()
{
	Init();
}

Booster::Booster(Vector2 startPosition, Vector2 direction, float speed)
{
	m_type = std::rand() % 6;
	char buf[100];


	m_position = startPosition;
	m_rotation = Vector3(0, 0, 0);
	GLint with = 75;
	GLint height = 75;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	snprintf(buf, 100, "m_booster_%d.tga", m_type);
	auto texture = ResourceManagers::GetInstance()->GetTexture(buf);
	m_booster_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_booster_sprite->SetSize(with, height);

	snprintf(buf, 100, "m_booster_%db.tga", m_type);
	texture = ResourceManagers::GetInstance()->GetTexture(buf);
	m_booster_boder_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_booster_boder_sprite->SetSize(with, height);
	
	m_booster_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
	m_booster_sprite->SetSize(with, height);
	m_speed = speed;
	m_collision = std::make_shared<Collision>(with, height, startPosition);
	Init();
}


Booster::~Booster()
{
}

void Booster::Init()
{
}

void Booster::Draw()
{
	m_booster_boder_sprite->Draw();
	m_booster_sprite->Draw();
}

void Booster::Update(GLfloat deltatime)
{
	m_position += m_direction * m_speed * deltatime * 100.0f;
	m_booster_sprite->Set2DPosition(m_position);
	m_booster_boder_sprite->Set2DPosition(m_position);
	//m_rotation += Vector3(0, 0, 1) * deltatime;
	//m_booster_boder_sprite->SetRotation(m_rotation);
	m_collision->SetPosition(m_position);
}

void Booster::Spawn(Vector2 startPosition, Vector2 direction)
{
	m_type = std::rand() % 6;
	char buf[100];
	GLint with = 75;
	GLint height = 75;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	snprintf(buf, 100, "m_booster_%d.tga", m_type);
	auto texture = ResourceManagers::GetInstance()->GetTexture(buf);
	m_booster_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_booster_sprite->SetSize(with, height);

	snprintf(buf, 100, "m_booster_%db.tga", m_type);
	texture = ResourceManagers::GetInstance()->GetTexture(buf);
	m_booster_boder_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_booster_boder_sprite->SetSize(with, height);

	m_position = startPosition;
	m_collision->SetPosition(m_position);
	m_booster_sprite->Set2DPosition(m_position);
	m_direction = direction / sqrt(direction.x * direction.x + direction.y * direction.y);
}