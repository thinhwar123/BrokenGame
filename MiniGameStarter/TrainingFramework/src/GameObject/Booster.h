#pragma once
#include "BaseObject.h"
#include "Sprite2D.h"
#include "Collision.h"
class Booster :
    public BaseObject
{
public:
    Booster();
    Booster(Vector2 startPosition, Vector2 direction, float speed);
    ~Booster();

    void    Init() override;
    void	Draw() override;
    void	Update(GLfloat deltatime) override;
    void    Spawn(Vector2 startPosition, Vector2 direction);
    Vector2 m_position;
    std::shared_ptr<Collision> m_collision;
    int m_type;
protected:
    std::shared_ptr<Sprite2D> m_booster_sprite;
    std::shared_ptr<Sprite2D> m_booster_boder_sprite;
    Vector2 m_direction;
    Vector3 m_rotation;
    float m_speed;

};

