#pragma once
#include "BaseObject.h"
#include "Collision.h"
class Sprite2D;
class AnimationSprite;
class Bullet;


class Spaceship :
    public BaseObject
{
protected:
	
	float m_movementSpeed;
	float m_currentShootTime;

	std::shared_ptr<Sprite2D>	m_spaceship;
	std::shared_ptr<Sprite2D>	m_bullet;
	std::shared_ptr<AnimationSprite> m_flame_1;
	std::shared_ptr<AnimationSprite> m_flame_2;
	std::shared_ptr<AnimationSprite> m_flame_3;
	std::shared_ptr<AnimationSprite> m_shield;
		
public:
	Vector2 m_currentPosition;
	int m_currentHitPoint;
	int m_maxHitPoint;
	bool m_isShield;
	float m_intervalShootTime;
	std::shared_ptr<Collision> m_collision;

	Spaceship();
	~Spaceship();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

	void		Move();
	void		Shoot();
	void		MoveLeft(GLfloat deltatime);
	void		MoveRight(GLfloat deltatime);
	void		MoveForward(GLfloat deltatime);
	void		MoveBackward(GLfloat deltatime);
	void		TakeDamge(int damage);

};

