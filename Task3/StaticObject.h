#pragma once
#include "BaseObject.h"
class StaticObject : public BaseObject {
public:
	StaticObject(int id, std::string name, Position position);
	void move() override;
};