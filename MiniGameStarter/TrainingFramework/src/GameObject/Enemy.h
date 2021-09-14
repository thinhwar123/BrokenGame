#pragma once
#include "BaseObject.h"
#include "Sprite2D.h"
#include "Collision.h"
#include "Spaceship.h"
class Enemy :
    public BaseObject
{
public:
    Enemy();
    Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hitPoint, std::shared_ptr<Spaceship> spaceship, Vector2 startPosition, Vector2 direction, float speed, GLint with, GLint height);
    ~Enemy();

    void    Init() override;
    void	Draw() override;
    void	Update(GLfloat deltatime) override;
    void    Spawn(Vector2 startPosition, Vector2 direction);
    Vector2 m_position;
    std::shared_ptr<Spaceship> m_spaceship;
    std::shared_ptr<Collision> m_collision;
    std::shared_ptr<Sprite2D> m_enemy_sprite;
    Vector2 m_direction;
    float m_speed;
    int m_maxHitpoint;
    int m_currentHitPoint;

    float m_currentShootTime;
    float m_intervalShootTime;

    void TakeDame(int damage);
    void Shoot();
};

