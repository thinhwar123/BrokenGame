#include "BaseObject.h"
#include <iostream>
#include "Position.h"
BaseObject::BaseObject()
{
}

BaseObject::BaseObject(int id, std::string name, Position position)
{
	m_ID = id;
	m_Name = name;
	m_Position = position;
}

BaseObject::~BaseObject()
{

}

std::string BaseObject::getName()
{
	return m_Name;
}

int BaseObject::getid()
{
	return m_ID;
}

void BaseObject::move()
{
}

void BaseObject::printPosition()
{
	std::cout << "Position x:" << m_Position.m_PosX << std::endl;
	std::cout << "Position y:" << m_Position.m_PosY << std::endl;
}
