#pragma once
#include "BaseObject.h"
#include "Sprite2D.h"
#include "Collision.h"
class Bullet :
    public BaseObject
{
public:
    Bullet();
    Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Vector2 startPosition, Vector2 direction, float speed ,GLint with, GLint height);
    ~Bullet();

    void    Init() override;
    void	Draw() override;
    void	Update(GLfloat deltatime) override;
    void    Spawn(Vector2 startPosition, Vector2 direction);
    Vector2 m_position;
    std::shared_ptr<Collision> m_collision;
protected:
    std::shared_ptr<Sprite2D> m_bullet_sprite;
    Vector2 m_direction;

    float m_speed;
};

