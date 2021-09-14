#include "Collision.h"


bool Collision::AABB(std::shared_ptr<Collision> A, std::shared_ptr<Collision> B)
{
	if (A->m_position.x + A->m_with / 2 < B->m_position.x - B->m_with / 2) return false;
	if (A->m_position.x - A->m_with / 2 > B->m_position.x + B->m_with / 2) return false;
	if (A->m_position.y + A->m_height / 2 < B->m_position.y - B->m_height / 2) return false;
	if (A->m_position.y - A->m_height / 2 > B->m_position.y + B->m_height / 2) return false;
	return true;
}

Collision::Collision()
{
}

Collision::Collision(GLint with, GLint height, Vector2 position)
{
	m_with = with;
	m_height = height;
	m_position = position;
}

Collision::~Collision()
{
}

void Collision::SetPosition(Vector2 position)
{
	m_position = position;
}
