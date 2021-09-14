#pragma once
#include "BaseObject.h"
#include "Sprite2D.h"
#include "Collision.h"
class Asteroid :
    public BaseObject, Collision
{
public:
    Asteroid();
    Asteroid(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hitPoint, Vector2 startPosition, Vector2 direction, float speed, GLint with, GLint height);
    ~Asteroid();

    void    Init() override;
    void	Draw() override;
    void	Update(GLfloat deltatime) override;
    void    Spawn(Vector2 startPosition, Vector2 direction);
    Vector2 m_position;
    std::shared_ptr<Collision> m_collision;
    std::shared_ptr<Sprite2D> m_asteroid_sprite;
    Vector2 m_direction;
    float m_speed;
    int m_maxHitpoint;
    int m_currentHitPoint;

    void TakeDame(int damage);
};

