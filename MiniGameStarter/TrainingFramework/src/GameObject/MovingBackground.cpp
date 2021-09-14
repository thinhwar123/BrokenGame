#include "MovingBackground.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Sprite2D.h"
#include "Application.h"
#include "ResourceManagers.h"

MovingBackground::MovingBackground(std::shared_ptr<Texture> texture, int width, int height, Vector2 position,float speed)
{
	m_speed = speed;
	m_height = height;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_background_sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_background_sprite->SetSize(width, height);
	m_position = position;

	m_background_sprite->Set2DPosition(m_position);
}

MovingBackground::~MovingBackground()
{
}

void MovingBackground::Init()
{
}

void MovingBackground::Draw()
{
	m_background_sprite->Draw();
}

void MovingBackground::Update(GLfloat deltatime)
{
	m_position += Vector2(0, 1) * m_speed * deltatime * 100.0f;
	if (m_position.y - m_height / 2.0f > (float)Globals::screenHeight)
	{
		m_position -= Vector2(0, (float)Globals::screenHeight  + m_height  );
	}
	m_background_sprite->Set2DPosition(m_position);

}
