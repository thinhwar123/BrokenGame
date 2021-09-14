#include "GSEndGame.h"

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

GSEndGame::GSEndGame()
{
}

GSEndGame::~GSEndGame()
{
}

void GSEndGame::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("m_background_02_static.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// background	
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(1332, 999);

	// window
	texture = ResourceManagers::GetInstance()->GetTexture("m_endgame_window.tga");
	m_endgame_window = std::make_shared<Sprite2D>(model, shader, texture);
	m_endgame_window->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_endgame_window->SetSize(1000, 868);

	// button 
	texture = ResourceManagers::GetInstance()->GetTexture("m_restart_button.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2 + 250, 800);
	button->SetSize(125, 125);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("m_menu_button.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth / 2 - 250, 800);
	button->SetSize(125, 125);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);

	// credit
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("neuropol.ttf");
	char buf[100];
	snprintf(buf, 100, "Total Score: %d", DataGlobal::GetInstance()->m_score);

	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, buf, Vector4(1, 1, 1, 1), 1.5f);
	text->Set2DPosition(Vector2(400, 350));
	m_endgame_text.push_back(text);

	snprintf(buf, 100, "Spaceship Kill: %d", DataGlobal::GetInstance()->m_enemyKill);
	text = std::make_shared< Text>(shader, font, buf, Vector4(1, 1, 1, 1), 1.5f);
	text->Set2DPosition(Vector2(400, 425));
	m_endgame_text.push_back(text);

	snprintf(buf, 100, "Asteroid Kill: %d", DataGlobal::GetInstance()->m_asteroidKill);
	text = std::make_shared< Text>(shader, font, buf, Vector4(1, 1, 1, 1), 1.5f);
	text->Set2DPosition(Vector2(400, 500));
	m_endgame_text.push_back(text);

	snprintf(buf, 100, "Boss Kill: %d", DataGlobal::GetInstance()->m_bossKill);
	text = std::make_shared< Text>(shader, font, buf, Vector4(1, 1, 1, 1), 1.5f);
	text->Set2DPosition(Vector2(400, 575));
	m_endgame_text.push_back(text);

	snprintf(buf, 100, "Total Booster Upgraded: %d", DataGlobal::GetInstance()->m_boosterUpgrage);
	text = std::make_shared< Text>(shader, font, buf, Vector4(1, 1, 1, 1), 1.5f);
	text->Set2DPosition(Vector2(400, 650));
	m_endgame_text.push_back(text);

	if (DataGlobal::GetInstance()->m_score > DataGlobal::GetInstance()->m_highscore)
	{
		snprintf(buf, 100, "NEW HIGH SCORE: %d", DataGlobal::GetInstance()->m_score);
		text = std::make_shared< Text>(shader, font, buf, TextColor::GREEN, 1.5f);
		text->Set2DPosition(Vector2(400, 725));
		m_endgame_text.push_back(text);

		DataGlobal::GetInstance()->SaveScore(DataGlobal::GetInstance()->m_score);
	}
	else
	{
		snprintf(buf, 100, "You Best Score: %d", DataGlobal::GetInstance()->m_highscore);
		text = std::make_shared< Text>(shader, font, buf, TextColor::GREEN, 1.5f);
		text->Set2DPosition(Vector2(400, 725));
		m_endgame_text.push_back(text);
	}

}

void GSEndGame::Exit()
{
}

void GSEndGame::Pause()
{
}

void GSEndGame::Resume()
{
}

void GSEndGame::HandleEvents()
{
}

void GSEndGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSEndGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSEndGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSEndGame::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSEndGame::Draw()
{
	m_background->Draw();
	m_endgame_window->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_endgame_text)
	{
		it->Draw();
	}
}
