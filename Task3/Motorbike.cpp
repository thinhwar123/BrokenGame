#include "Motorbike.h"
#include <iostream>

Motorbike::Motorbike(int id, std::string name, Position position): DynamicObject(id, name, position)
{
}

void Motorbike::move()
{
	std::cout << "Motorbike Move" << std::endl;
	m_Position.m_PosX += 2;
	m_Position.m_PosY += 2;
}
