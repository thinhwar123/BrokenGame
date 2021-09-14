#pragma once
#include "GameStateBase.h"
class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class GSHelp :
    public GameStateBase
{
public:
	GSHelp();
	~GSHelp();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_help_window;
	std::list<std::shared_ptr<Text>> m_help_Text;
	std::list<std::shared_ptr<Sprite2D>>	m_listSprite;
	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

