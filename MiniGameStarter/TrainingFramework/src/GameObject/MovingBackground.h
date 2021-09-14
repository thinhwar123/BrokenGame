#pragma once
#include "BaseObject.h"
class Sprite2D;
class MovingBackground :
    public BaseObject
{
public:
    MovingBackground(std::shared_ptr<Texture> texture, int width, int height, Vector2 position, float speed);
    ~MovingBackground();

    void		Init() override;
    void		Draw() override;
    void		Update(GLfloat deltatime) override;

    float m_speed;
    int m_height;
    Vector2 m_position;
    std::shared_ptr<Sprite2D>	m_background_sprite;
};

