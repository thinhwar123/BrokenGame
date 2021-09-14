#include "GSHelp.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "DataGlobe.h"

GSHelp::GSHelp()
{
}

GSHelp::~GSHelp()
{
}

void GSHelp::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("m_background_01_static.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// background	
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(1332, 999);

	// window
	texture = ResourceManagers::GetInstance()->GetTexture("m_help_window.tga");
	m_help_window = std::make_shared<Sprite2D>(model, shader, texture);
	m_help_window->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_help_window->SetSize(1000, 868);

	// sprite
	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_0.tga");
	auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(375, 450);
	sprite->SetSize(75, 75);
	m_listSprite.push_back(sprite);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_1.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(375, 500);
	sprite->SetSize(75, 75);
	m_listSprite.push_back(sprite);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_2.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(375, 550);
	sprite->SetSize(75, 75);
	m_listSprite.push_back(sprite);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_3.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(375, 600);
	sprite->SetSize(75, 75);
	m_listSprite.push_back(sprite);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_4.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(375, 650);
	sprite->SetSize(75, 75);
	m_listSprite.push_back(sprite);

	texture = ResourceManagers::GetInstance()->GetTexture("m_booster_5.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(375, 700);
	sprite->SetSize(75, 75);
	m_listSprite.push_back(sprite);

	// button 
	texture = ResourceManagers::GetInstance()->GetTexture("m_menu_button.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// credit
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("neuropol.ttf");
	char buf[100];

	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "WASD to Move", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(350, 350));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "J to Attack", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(350, 400));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "Heal 10% hipoint", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(430, 455));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "Block damage", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(430, 505));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "Increase attack speed ", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(430, 555));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "Gain extra score", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(430, 605));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "Increase attack damage", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(430, 655));
	m_help_Text.push_back(text);

	text = std::make_shared< Text>(shader, font, "Upgrade bullet", Vector4(1, 1, 1, 1), 1.0f);
	text->Set2DPosition(Vector2(430, 705));
	m_help_Text.push_back(text);

}

void GSHelp::Exit()
{
}

void GSHelp::Pause()
{
}

void GSHelp::Resume()
{
}

void GSHelp::HandleEvents()
{
}

void GSHelp::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSHelp::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSHelp::HandleMouseMoveEvents(int x, int y)
{
}

void GSHelp::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSHelp::Draw()
{
	m_background->Draw();
	m_help_window->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_help_Text)
	{
		it->Draw();
	}
	for (auto it : m_listSprite)
	{
		it->Draw();
	}
}
