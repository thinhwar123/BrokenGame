#include "GSCredit.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"

GSCredit::GSCredit()
{
}

GSCredit::~GSCredit()
{
}

void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("m_menu_background.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// background	
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(500, 1000);

	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// credit
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Pixel.otf");
	m_header = std::make_shared< Text>(shader, font, "xxxxxxxxCREDITxxxxxxxx", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1.5);
	m_header->Set2DPosition(Vector2(20, 200));

	std::shared_ptr<Text> credit = std::make_shared< Text>(shader, font, "GAME DESIGNER : ", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1.2f);
	credit->Set2DPosition(Vector2(50, 300));
	m_credit.push_back(credit);

	credit = std::make_shared< Text>(shader, font, "Pham Hoang Thinh ", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1);
	credit->Set2DPosition(Vector2(50, 350));
	m_credit.push_back(credit);

	credit = std::make_shared< Text>(shader, font, "GAME PROGRAMMER :  ", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1.2f);
	credit->Set2DPosition(Vector2(50, 400));
	m_credit.push_back(credit);

	credit = std::make_shared< Text>(shader, font, "Pham Hoang Thinh ", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1);
	credit->Set2DPosition(Vector2(50, 450));
	m_credit.push_back(credit);

	credit = std::make_shared< Text>(shader, font, "SPECICAL THANK TO : ", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1.2f);
	credit->Set2DPosition(Vector2(50, 500));
	m_credit.push_back(credit);

	credit = std::make_shared< Text>(shader, font, "itcho.io for the art ", Vector4(245 / 255.0f, 174 / 255.0f, 71 / 255.0f, 255 / 255.0f), 1);
	credit->Set2DPosition(Vector2(50, 550));
	m_credit.push_back(credit);
}

void GSCredit::Exit()
{
}

void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}

void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSCredit::Draw()
{
	m_background->Draw();
	m_header->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_credit)
	{
		it->Draw();
	}
}
