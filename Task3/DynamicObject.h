#pragma once
#include "BaseObject.h"
class DynamicObject : public BaseObject {
public:
	DynamicObject(int id, std::string name, Position position);
	void move() override;
};