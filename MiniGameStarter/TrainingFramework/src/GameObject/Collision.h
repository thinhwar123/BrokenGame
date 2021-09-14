#pragma once
#include "utilities.h" 
class Collision
{
public:
	static bool AABB(std::shared_ptr<Collision> A, std::shared_ptr<Collision> B);
	Collision();
	Collision(GLint with, GLint height, Vector2 position);
	~Collision();

	void SetPosition(Vector2 position);

	GLint m_with;
	GLint m_height;
	Vector2 m_position;

};
