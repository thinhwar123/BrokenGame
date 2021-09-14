#include "Explosion.h"
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



Explosion::Explosion(Vector2 position, int type, int size)
{
	m_isFinish = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

	auto texture = ResourceManagers::GetInstance()->GetTexture(type == 0 ? "m_explosion_0.tga": "m_explosion_1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");

	m_anim = std::make_shared<AnimationSprite>(model, shader, texture, 9, 0.05f);
	m_anim->SetSize(size, size);
	m_anim->Set2DPosition(position);
}

Explosion::~Explosion()
{
}

void Explosion::Init()
{

}

void Explosion::Draw()
{
	m_anim->Draw();
}

void Explosion::Update(GLfloat deltatime)
{
	m_anim->Update(deltatime);
	if (m_anim->m_currentFrame == m_anim->m_numFrames - 1)
	{
		m_isFinish = true;
	}
}

void Explosion::Spawn(Vector2 position, int type, int size)
{
	m_isFinish = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture(type == 0 ? "m_explosion_0.tga" : "m_explosion_1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");

	m_anim = std::make_shared<AnimationSprite>(model, shader, texture, 9, 0.05f);
	m_anim->SetSize(size, size);
	m_anim->Set2DPosition(position);
}
