#include "StaticObject.h"
#include <iostream>
StaticObject::StaticObject(int id, std::string name, Position position): BaseObject(id, name, position)
{
}
void StaticObject::move()
{
	std::cout << "Static object can't move"<<std::endl;
}
