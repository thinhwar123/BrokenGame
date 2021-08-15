#include "Car.h"
#include <iostream>

Car::Car(int id, std::string name, Position position): DynamicObject(id, name, position)
{
}

void Car::move()
{
	std::cout << "Car Move"<< std::endl;
	m_Position.m_PosX += 5;
	m_Position.m_PosY += 5;
}
